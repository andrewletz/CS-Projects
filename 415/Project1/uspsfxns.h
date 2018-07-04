#ifndef _USPSFXNS_H_INCLUDED_
#define _USPSFXNS_H_INCLUDED_
/*
	CIS 415 Project 1 uspsfxns.h
	Author: Andrew Letz
	Duck ID: aletz
	Apart from:
	- Followed instruction from Roscoe Casita in labs
	, this is my own work
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "p1fxns.h"
#include "pcontrol.h" /* LL structure, functions and Pctrl wrapper */

#define BUFSIZE 1024
#define SUCCESS 0
#define ERROR 1
#define UNUSED __attribute__((unused)) /* compiler-dependent */

/* do_nanosleep - written by Roscoe Casita */
void do_nanosleep(int nseconds); /* helper sleep function.*/

/* 
	getWordCount -
	returns the number of blank separated words in buf
*/
int getWordCount(char buf[]);

/*
	parseCommand - returns an array of strings of form {CMDNAME, ARG1, ARG2, ..., NULL}
	from buf (should be a single line with a command & args)
	returns NULL if could not allocate or if no command was read from the line
*/
char **parseCommand(char buf[]);

/*
	readin - reads lines from fd using buf as a buffer
	adds resulting pcb structs into pcontrol
	returns void
*/
void readin(int fd, char buf[], Pctrl *pcontrol);

/* 
	getQuantum - takes a string and returns the quantum value
	if it is of form --quantum=x
	returns 0 if invalid
*/
int getQuantum(char* arg);

#endif /* _USPSFXNS_H_INCLUDED_ */

