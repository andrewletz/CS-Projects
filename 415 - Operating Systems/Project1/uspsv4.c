/*
	CIS 415 Project 1 USPS v4
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

void clearNewline(char buf[], int bytes) {
	int i;
	for (i = 0; i <= bytes; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
		}
	}
}

/*
	printProc - prints the proc file system info associated with Pcb *running
	returns void
*/
void printProc() {
	int fd;
	int bytes;
	int i;
	char buf[BUFSIZE];

	char *procString = "/proc/";

	char pid[7]; /* hopefully you dont have PIDs larger than 9,999,999 */
	p1itoa((int)running->pid, pid);
	char proc[p1strlen(procString) + p1strlen(pid) + 1];

	/* setting up and printing top PID dashed line */
	p1putstr(1, "\n");
	char *init_start_str = "|------------------------ PID ";
	char init_start[p1strlen(init_start_str) + p1strlen(pid) + 1];
	p1strcpy(init_start, init_start_str);
	p1strcat(init_start, pid);
	char *init_end = " ------------------------|";
	p1putstr(1, init_start);
	p1putstr(1, init_end);
	p1putstr(1, "\n");

	/* base filepath str */
	p1strcpy(proc, procString); 
	p1strcat(proc, pid); /* we should have "/proc/PID" now */

	/* getting proc/cmdline info */
	p1putstr(1, "cmdline: ");
	char cmdpath[p1strlen(proc) + 8]; /* space for "/cmdline" */
	p1strcpy(cmdpath, proc);
	p1strcat(cmdpath, "/cmdline");
	fd = open(cmdpath, O_RDONLY);

	bytes = p1getline(fd, buf, BUFSIZE);
	for (i = 0; i < bytes; i++) {
		if (buf[i] == '\0')
			buf[i] = ' ';
	}
	p1putstr(1, buf);
	//clearNewline(buf, bytes);
	p1putstr(1, "\n");

	/* getting proc/stat info */
	char word[BUFSIZE];

	char statpath[p1strlen(proc) + 5]; /* space for "/stat" */
	p1strcpy(statpath, proc);
	p1strcat(statpath, "/stat");
	fd = open(statpath, O_RDONLY);

	bytes = p1getline(fd, buf, BUFSIZE);
	clearNewline(buf, bytes);

	int wordIdx;
	wordIdx = p1getword(buf, 0, word);
	p1putstr(1, "PID: ");
	p1putstr(1, word);

	for (i = 0; i < 2; i++) /* go up to (3) in stat */
		wordIdx = p1getword(buf, wordIdx, word);
	p1putstr(1, "   State: ");
	p1putstr(1, word);

	for (i = 0; i < 8; i++) /* go up to (10) in stat */
		wordIdx = p1getword(buf, wordIdx, word);
	p1putstr(1, "   Minor faults: ");
	p1putstr(1, word);

	for (i = 0; i < 29; i++) /* go up to (39) in stat */
		wordIdx = p1getword(buf, wordIdx, word);
	p1putstr(1, "   Processor: ");
	p1putstr(1, word);


	p1putstr(1, "\n");

	/* getting proc/status info for size*/
	char statuspath[p1strlen(proc) + 7]; /* space for "/status" */
	p1strcpy(statuspath, proc);
	p1strcat(statuspath, "/status");
	fd = open(statuspath, O_RDONLY);

	bytes = p1getline(fd, buf, BUFSIZE);
	while (p1strneq("VmPeak", buf, 6) == 0 && bytes != 0 && bytes != 1023) {
		bytes = p1getline(fd, buf, BUFSIZE);
	}
	clearNewline(buf, bytes);
	p1putstr(1, "(peak) ");
	p1putstr(1, buf);
	p1putstr(1, " | ");
	p1putstr(1, "(curr) ");
	bytes = p1getline(fd, buf, BUFSIZE);
	p1putstr(1, buf);

	/* getting proc/io info */
	p1putstr(1, "IO: ");
	char iopath[p1strlen(proc) + 3]; /* space for "/io" */
	p1strcpy(iopath, proc);
	p1strcat(iopath, "/io");
	fd = open(iopath, O_RDONLY);

	bytes = p1getline(fd, buf, BUFSIZE);
	while (p1strneq("syscr", buf, 5) == 0 && bytes != 0 && bytes != 1023) {
		bytes = p1getline(fd, buf, BUFSIZE);
	}
	clearNewline(buf, bytes);
	p1putstr(1, "(read sys calls) ");
	p1putstr(1, buf);
	p1putstr(1, " | ");
	bytes = p1getline(fd, buf, BUFSIZE);
	p1putstr(1, "(wrote sys calls) ");
	p1putstr(1, buf);

	/* setting up and printing bottom PID dashed line, resizing accordingly to top */
	int numDash = p1strlen(init_start) + p1strlen(init_end); 
	char end_str[numDash + 1];
	for (i = 0; i < numDash - 1; i++)
		end_str[i] = '-';
	end_str[0] = '|';
	end_str[numDash - 1] = '|';
	end_str[numDash] = '\0';
	p1putstr(1, end_str);
	p1putstr(1, "\r\n\n");
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
	} else {
		printProc();
	}
	/* printf("\n"); */

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
