#
# CIS 415 Project 1 Makefile
# Author: Andrew Letz
# Duck ID: aletz
#
CFLAGS= -W -Wall -g
PROGS= uspsv1 uspsv2 uspsv3 uspsv4
OBJECTS= p1fxns.o pcontrol.o uspsfxns.o

all: $(PROGS)

uspsv1: uspsv1.c p1fxns.o pcontrol.o uspsfxns.o
	cc -o uspsv1 $(CFLAGS)  $^

uspsv2: uspsv2.c p1fxns.o pcontrol.o uspsfxns.o
	cc -o uspsv2 $(CFLAGS) $^

uspsv3: uspsv3.c p1fxns.o pcontrol.o uspsfxns.o
	cc -o uspsv3 $(CFLAGS) $^

uspsv4: uspsv4.c p1fxns.o pcontrol.o uspsfxns.o
	cc -o uspsv4 $(CFLAGS) $^

p1fxns.o: p1fxns.h p1fxns.c
pcontrol.o: pcontrol.h pcontrol.c
uspsfxns.o: uspsfxns.h uspsfxns.c

clean:
	rm -f *~ $(OBJECTS) $(PROGS)
