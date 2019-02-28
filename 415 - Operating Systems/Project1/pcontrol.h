#ifndef _PCONTROL_H_INCLUDED_
#define _PCONTROL_H_INCLUDED_

/*
	CIS 415 Project 1 pcontrol.h
	Author: Andrew Letz
	Duck ID: aletz
	Apart from
	- Followed instruction from Roscoe Casita in labs
	, this is my own work
*/

#include <stdlib.h>
#include <stdio.h> /* remove me when done using printf for testing */
#include <unistd.h>
#include "p1fxns.h"

typedef struct pcb { /* process control block */
	struct pcb *next; /* pointer to next pcb */
	char *cmd;
	char **args;
	pid_t pid; /* pid */

	/* only used in uspsv3 & 4 */
	int execd; /* whether it has execvp'd yet */
	int exited; /* whether it has exited */
} Pcb;

typedef struct p_controller { /* process controller */
	Pcb *pcb; /* tail of linked list of pcbs */
	int count; /* number of processes under this pcontroller */
} Pctrl;

/*
	pctrl_add - attempts to add inpcb to a Pctrl struct.
	returns 0 if succesful, 1 otherwise.
*/
int pctrl_add(Pctrl *inpctrl, Pcb *inpcb);

/*
	pctrl_remove - attempts to remove inpcb from a Pctrl struct.
	returns 0 if succesful, 1 otherwise.
*/
int pctrl_remove(Pctrl *inpctrl, Pcb *inpcb);


/* 
	pctrl_freeArgs - frees the memory associated with a char** created by parseCommand
	returns void
*/
void pctrl_freeArgs(char **args);

/* 
	pctrl_free - frees all memory associated with a Pctrl struc
	returns void
*/
void pctrl_free(Pctrl *inpctrl);

/*
	pctrl_create - attempts to create a new Pctrl.
	returns a pointer to newly initialized Pctrl if sucessful,
	NULL otherwise
*/
Pctrl *pctrl_create();

#endif /* _PCONTROL_H_INCLUDED_ */

