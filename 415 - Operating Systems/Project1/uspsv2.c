/*
	CIS 415 Project 1 USPS v2
	Author: Andrew Letz
	Duck ID: aletz
	Apart from:
	- Followed instruction from Roscoe Casita in labs
	- Used segments of code from Lab 4 "sigtest.c"
	, this is my own work
*/

#include "p1fxns.h"
#include "pcontrol.h" /* LL structure, functions and Pctrl wrapper */
#include "uspsfxns.h" /* helper functions */

Pctrl *processes; /* global processes container */
volatile int run = 0; /* for signalling to child processes to execvp */

/*
	sigusr1 - sets run to 0. meant for use by child processes
	returns void
	credit: Roscoe Casita
*/
void sigusr1(UNUSED int signal) {
	run = 1;
}

int main(int argc, char *argv[]) {
	char buf[BUFSIZE]; /* BUFSIZE = 1024 */
	int status = SUCCESS; /* SUCCESS = 0, ERROR = 1 */
	int filearg; /* used in case 3 of switch */
	int fd; /* used when a filename is provided */

	processes = pctrl_create(); /* allocate global processes struct */
	if (processes == NULL) return ERROR;

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
				exit(0);
			}
			process = process->next;
		}
	}

	process = processes->pcb; /* send a SIGUSR1 to each process to wake them up */
	if (process != NULL) {
		while (process != NULL) {
			kill(process->pid, SIGUSR1);
			process = process->next;
		}
	}

	process = processes->pcb; /* send a SIGSTOP to each process to suspend them */
	if (process != NULL) {
		while (process != NULL) {
			kill(process->pid, SIGSTOP);
			process = process->next;
		}
	}

	process = processes->pcb; /* send a SIGCONT to each process to resume them */
	if (process != NULL) {
		while (process != NULL) {
			kill(process->pid, SIGCONT);
			process = process->next;
		}
	}
	
	process = processes->pcb; /* wait for each process to finish */
	if (process != NULL) {
		while (process != NULL) {
			int status;
			waitpid(process->pid, &status, 0);
			process = process->next;
		}
	}

	pctrl_free(processes); /* free all memory associated with processes */

    return status;
}
