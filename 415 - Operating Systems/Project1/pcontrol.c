/*
	CIS 415 Project 1 pcontrol.c
	Author: Andrew Letz
	Duck ID: aletz
	Apart from
	- Followed instruction from Roscoe Casita in labs
	, this is my own work
*/

#include "pcontrol.h"

/*
	pctrl_add - attempts to add inpcb to a Pctrl struct.
	returns 0 if succesful, 1 otherwise.
*/
int pctrl_add(Pctrl *inpctrl, Pcb *inpcb) {
	if (inpctrl == NULL) {
		p1putstr(2, "Error in pctrl_add: invalid Pctrl\n");
		return 1;
	}
	if (inpcb == NULL) {
		p1putstr(2, "Error in pctrl_add: invalid Pcb\n");
		return 1;
	}
	if (inpctrl->pcb == NULL) { /* first element added to inpctrl */
		inpctrl->pcb = inpcb;
		inpctrl->count = 1;
	} else { /* add to end of pcb */
		Pcb *prev;
		Pcb *temp = inpctrl->pcb;
		while (temp != NULL) {
			prev = temp;
			temp = temp->next;
		}
		/* we should have the final LL item inside temp now */
		prev->next = inpcb;
		inpctrl->count++;
	}
	return 0;
}

/*
	pctrl_remove - attempts to remove inpcb from a Pctrl struct.
	returns 0 if succesful, 1 otherwise.
*/
int pctrl_remove(Pctrl *inpctrl, Pcb *inpcb) {
	if (inpctrl == NULL) {
		p1putstr(2, "Error in pctrl_remove: invalid Pctrl\n");
		return 1;
	}
	if (inpcb == NULL) {
		p1putstr(2, "Error in pctrl_remove: invalid Pcb\n");
		return 1;
	}
	if (inpctrl->pcb == NULL) {
		p1putstr(2, "Error in pctrl_remove: nothing to remove\n");
		return 1;
	}

	Pcb *temp = inpctrl->pcb;
	if (inpctrl->count == 1) { /* case with only 1 item in pctrl */
		if (temp->pid == inpcb->pid) {
			inpctrl->pcb = NULL;
			inpctrl->count = 0;
			return 0;
		} else {
			p1putstr(2, "Error in pctrl_remove: inpcb not found (1 item)\n");
			return 1;
		}
	} else { /* several pcbs in the pctrl */

		/* head is the pcb we need to remove */
		if (temp->pid == inpcb->pid) {
			inpctrl->pcb = temp->next;
			inpctrl->count--;
			return 0;
		}
		
		/* pcb we want to remove is somewhere else */
		Pcb *prev;
		while (temp->pid != inpcb->pid && temp != NULL) {
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL) { /* not found */
			p1putstr(2, "Error in pctrl_remove: inpcb not found (several items)\n");
			return 1;
		} else {
			prev->next = temp->next;
			inpctrl->count--;
			return 0;
		}
			
	}
	
	return 1;
	
}

/* 
	pctrl_freeArgs - frees the memory associated with a char** created by parseCommand
	returns void
*/
void pctrl_freeArgs(char **args) {
	int i;
	for (i = 0; args[i] != NULL; i++) {
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
}

/* 
	pctrl_free - frees all memory associated with a Pctrl struc
	returns void
*/
void pctrl_free(Pctrl *inpctrl) {
	Pcb *curr = inpctrl->pcb;
	Pcb *temp;
	while (curr != NULL) {
		temp = curr->next;
		pctrl_freeArgs(curr->args);
		free(curr->cmd);
		free(curr);
		curr = temp;
	}
	free(inpctrl);
	inpctrl = NULL;
}

/*
	pctrl_create - attempts to create a new Pctrl.
	returns a pointer to newly initialized Pctrl if sucessful,
	NULL otherwise
*/
Pctrl *pctrl_create() {
	Pctrl *p = (Pctrl *)malloc(sizeof(Pctrl));
	if (p != NULL) {
		p->pcb = NULL;
		p->count = 0;
	} else {
		free(p);
		p = NULL;
	}
	return p;
}
