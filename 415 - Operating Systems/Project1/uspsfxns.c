/*
	CIS 415 Project 1 uspsfxns.c
	Author: Andrew Letz
	Duck ID: aletz
	Apart from:
	- Followed instruction from Roscoe Casita in labs
	, this is my own work
*/

#include "uspsfxns.h"

/* do_nanosleep - written by Roscoe Casita */
void do_nanosleep(int nseconds) /* helper sleep function.*/
{
	struct timespec time, time2;
	time.tv_sec = 0;
	time.tv_nsec = nseconds;
	time2.tv_sec =0;
	time2.tv_nsec = 0;
	nanosleep( &time, &time2);
}

/* 
	getWordCount -
	returns the number of blank separated words in buf
*/
int getWordCount(char buf[]) {
	char localbuf[BUFSIZE];
	int count = 0;
	int i = p1getword(buf, 0, localbuf);
	while (i != -1) {
		count++;
		i = p1getword(buf, i, localbuf);
	}
	return count;

}

/*
	parseCommand - returns an array of strings of form {CMDNAME, ARG1, ARG2, ..., NULL}
	from buf (should be a single line with a command & args)
	returns NULL if could not allocate or if no command was read from the line
*/
char **parseCommand(char buf[]) {
	int count = getWordCount(buf) + 1;
	char **retArray = (char **)malloc(sizeof(char *) * count);
	char localbuf[BUFSIZE]; /* used for copying the words one at a time */

	if (retArray != NULL) {
		int bufIndex = 0; /* index into the buffer for next word */
		int i; /* i is for keeping track of 2d retArray position */

		bufIndex = p1getword(buf, bufIndex, localbuf);
		for (i = 0; bufIndex != -1; i++) {
			retArray[i] = p1strdup(localbuf);
			bufIndex = p1getword(buf, bufIndex, localbuf);
		}

		retArray[count - 1] = NULL; /* set final arg to NULL */
		
	} else {
		free(retArray);
		retArray = NULL;
	}
	if (retArray[0] == NULL) {
		free(retArray);
		retArray = NULL;
	}
	return retArray;
}

/*
	readin - reads lines from fd using buf as a buffer
	adds resulting pcb structs into pcontrol
	returns void
*/
void readin(int fd, char buf[], Pctrl *pcontrol) {
	int bytes;

	while ((bytes = p1getline(fd, buf, BUFSIZE)) != 0) {
		int i;
		for (i = 0; i <= bytes; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
			}
		}
		char **args = parseCommand(buf);
		if (args != NULL) {
			Pcb *newPcb = (Pcb *)malloc(sizeof(Pcb));
			newPcb->next = NULL;
			newPcb->cmd = p1strdup(args[0]);
			newPcb->args = args;
			newPcb->exited = 0;
			newPcb->execd = 0;
			pctrl_add(pcontrol, newPcb);
		}
	}
}

/* 
	getQuantum - takes a string and returns the quantum value
	if it is of form --quantum=x
	returns 0 if invalid
*/
int getQuantum(char* arg) {
	int equalsIdx = p1strchr(arg, '=') + 1;
	int arglen = p1strlen(arg);
	char *qstr = (char *)malloc((arglen - equalsIdx) + 1);
	int i, j;
	for (j = 0, i = equalsIdx; i < arglen; i++, j++)
		qstr[j] = arg[i];
	qstr[j] = '\0';
	int qint = p1atoi(qstr);
	free(qstr);
	return qint;
}
