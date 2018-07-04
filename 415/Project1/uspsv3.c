/*
	CIS 415 Project 1 USPS v3
	Author: Andrew Letz
	Duck ID: aletz
	Apart from:
	- Followed instruction from Roscoe Casita in labs
	- Used segments of code from Lab 4 "sigtest.c", Lab 5 "sigstop.c"
	, this is my own work
*/

#include "p1fxns.h"
#include "pcontrol.h" /* LL structure, functions and Pctrl wrapper */
#include "uspsfxns.h" /* helper functions */

Pctrl *processes; /* global processes container */
Pctrl *exited; /* for freeing up exited processes at the end */
Pcb *running; /* currently running pcb for RR scheduler */

volatile int run = 0; /* for signalling to child processes to execvp */

/*
	sigusr1 - sets run to 0. meant for use by child processes
	returns void
	credit: Roscoe Casita
*/
void sigusr1(UNUSED int signal) {
	run = 1;
}

/*
	sigalrm - stop the currently running process and set the alarm
	so the loop in main will find the next process to run
	returns void
*/
void sigalrm(UNUSED int signal) {
	sigset_t signal_set; 
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &signal_set, NULL);  /* block child exit signal */

	kill(running->pid, SIGSTOP);

	/* printf("----------SIGALRM BEGIN----------\n");
	printf("%s\t being stopped\n", running->cmd); */
	Pcb *nextPcb = running->next; /* save this pointer here in case we need to free running */

	if (running->exited == 1) { /* process is done, clean up and remove from LL */
		/* printf("%s\t is exited, cleaning up\n", running->cmd); */
		pctrl_remove(processes, running);
		running->next = NULL; /* reset next pointer so we dont add it to exited with a random pointer */
		pctrl_add(exited, running);
		/* printf("%s\t process count now %i\n", running->cmd, processes->count); */
		running = NULL;
	/* printf("\n"); */
	}

	running = nextPcb;
	if (running == NULL) running = processes->pcb; /* reset to start of list */
	if (running == NULL) return; /* if it is null again, there are no more processes */

	/* printf("%s\t is now the running running process\n", running->cmd); */

	if (running->execd == 0) { /* first time executing, use SIGUSR1 */
		/* printf("%s\t first time exec, sending SIGUSR1\n", running->cmd); */
		running->execd = 1;
		kill(running->pid, SIGUSR1);
	} else { /* resume process */
		/* printf("%s\t scheduled normally, sending SIGCONT\n", running->cmd); */
		kill(running->pid, SIGCONT);
	}

	/* printf("-----------SIGALRM END-----------\n");
	printf("\n"); */
	sigprocmask(SIG_UNBLOCK, &signal_set, NULL);  /* reenable child exit signal */
}

/* some CHLD_handler code from Chapter 5 of "Elegant C Programming" */ 
static void CHLD_handler(UNUSED int sig) {
	sigset_t signal_set; 
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigprocmask(SIG_BLOCK, &signal_set, NULL);  /* block sig timer signal */

    pid_t pid;
    int status;

    /* Wait for all dead processes. */
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            running->exited = 1; /* the process will be cleaned up next time its found */
        }
    }

	sigprocmask(SIG_UNBLOCK, &signal_set, NULL);  /* reenable sig timer signal */
}

int main(int argc, char *argv[]) {
	char buf[BUFSIZE]; /* BUFSIZE = 1024 */
	int status = SUCCESS; /* SUCCESS = 0, ERROR = 1 */
	int filearg; /* used in case 3 of switch */
	int fd; /* used when a filename is provided */

	processes = pctrl_create(); /* allocate global processes struct */
	if (processes == NULL) return ERROR;
	exited = pctrl_create(); /* allocate global exited struct */
	if (exited == NULL) return ERROR;

	char *p; /* code for env variable taken from project 1 handout */
	int quantum = -1;
	if ((p = getenv("USPS_QUANTUM_MSEC")) != NULL)
		quantum = atoi(p);

	/* the almighty input switch-case */
	switch (argc) {
		case 1: /* form [./uspsv1], read stdin */
			if (quantum == -1) {
				p1putstr(2, "Quantum is not defined. Exiting\n");
				status = ERROR;
			} else {
				readin(0, buf, processes);
			}
			break;

		case 2: /* form [./uspsv1 --quantum=n] or [./uspsv1 filename] */
			if (p1strneq(argv[1], "--quantum=", 10)) { /* form [./uspsv1 --quantum=n] */
				quantum = getQuantum(argv[1]);
				if (quantum == 0) {
					p1putstr(2, "Invalid quantum. Exiting\n");
					status = ERROR;
				} else {
					readin(0, buf, processes);
				}

			} else { /* form [./uspsv1 filename] */
				if (quantum == -1) {
					p1putstr(2, "Quantum is not defined. Exiting\n");
					status = ERROR;
				} else {
					fd = open(argv[1], 0);
					if (fd != -1) {
						readin(fd, buf, processes);
					} else {
						p1putstr(2, "Invalid file. Exiting\n");
						status = ERROR;
					}
				}
			}	
			break;

		case 3: /* form [uspsv1 --quantum=n filename] */	
			if (p1strneq(argv[1], "--quantum=", 10)) { /* quantum is arg1 */
				quantum = getQuantum(argv[1]);
				filearg = 2;
			} else if (p1strneq(argv[2], "--quantum=", 10)) { /* quantum is arg2 */
				quantum = getQuantum(argv[2]);
				filearg = 1;
			} else {
				p1putstr(2, "Invalid arguments. Exiting\n");
				status = ERROR;
				break;
			}
			if (quantum == 0) {
				p1putstr(2, "Invalid quantum. Exiting\n");
				status = ERROR;
			} else {
				fd = open(argv[filearg], 0);
				if (fd != -1) {
					readin(fd, buf, processes);
				} else {
					p1putstr(2, "Invalid file. Exiting\n");
					status = ERROR;
				}
			}
			break;

		default: /* invalid arguments */
			p1putstr(2, "Invalid arguments. Exiting\n");
			status = ERROR;
			break;
    }

	if (signal(SIGUSR1, sigusr1) == SIG_ERR) return ERROR; /* subscribe to SIGUSR1 */
	if (signal(SIGCHLD, CHLD_handler) == SIG_ERR) return ERROR; /* subscribe to SIGCHLD */
	if (signal(SIGALRM, sigalrm) == SIG_ERR) return ERROR; /* subscribe to SIGALRM */
		
	/* have all processes wait on SIGUSR1 */
	Pcb *process = processes->pcb;
	if (process != NULL) {
		while (process != NULL) {
			run = 0; /* set to be sure before fork */

			process->pid = fork();
			if (process->pid == 0) {
				while (run == 0) { /* waiting on SIGUSR1 before execvp */
					do_nanosleep(1);
				}
				UNUSED int err = execvp(process->cmd, process->args);
				/*p1putstr(1, "Failed to execvp: ");
				p1putstr(1, process->cmd);	printing this way gets jumbled, might as
				p1putstr(1, "\r\n");		well not include it			*/
				pctrl_free(processes); /* need to free memory if child couldn't execvp */
				pctrl_free(exited);
				_exit(1);
			}
			process = process->next;
		}
	}

	running = processes->pcb; /* set running pointer to start of list */
	if (running == NULL) return ERROR;

	
	struct itimerval new_value; /* set up itimer for SIGALRMs */
	new_value.it_interval.tv_sec = quantum / 1000;
	new_value.it_interval.tv_usec = (quantum * 1000) % 1000000;
	new_value.it_value.tv_sec = quantum / 1000;
	new_value.it_value.tv_usec =(quantum * 1000) % 1000000;
	if (setitimer(ITIMER_REAL, &new_value, 0) == -1) return ERROR;

	/* start the first process so it doesn't get skipped on first iteration */
	/* printf("\n--------BEGIN FIRST PROCESS--------\n"); */
	kill(running->pid, SIGUSR1);
	running->execd = 1;

	/* wait for all processes to terminate */
	while (processes->count > 0) {
		do_nanosleep(1);
	}

	/* printf("Process count 0: exiting program\n"); */

	pctrl_free(processes); /* free all memory associated with processes */
	pctrl_free(exited); /* free all memory associated with exited processes
							(this does most of the freeing) */

    return status;
}
