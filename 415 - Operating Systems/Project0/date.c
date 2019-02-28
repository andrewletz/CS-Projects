/*
CIS 415 Project 0
Author: Andrew Letz
Duck ID: aletz
This is my own work.
*/
#include "date.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct d_data {
	int day;
	int month;
	int year;	
} D_Data;

static const Date *d_duplicate(const Date *d) {
	Date *dup = (Date *)malloc(sizeof(Date)); // allocate dupd

	if (dup != NULL) {
		D_Data *dupd = (D_Data *)malloc(sizeof(D_Data)); // dupd's data
		if (dupd != NULL) {
			*dup = *d;
			D_Data *dd = (D_Data *)d->self; // points to d's data
			memcpy(dupd, dd, sizeof(D_Data));
			dup->self = dupd; // set dup's data to dupd	
		} else {
			free(dup);
			free(dupd);
			dup = NULL;	
		}
	} else {
		free(dup);
	}
	
	return dup;
}

static int d_compare(const Date *date1, const Date *date2) {
	D_Data *d1Data = (D_Data *)date1->self;
	D_Data *d2Data = (D_Data *)date2->self;
	int yearDiff = d1Data->year - d2Data->year;
	if (yearDiff != 0) {
		return yearDiff;
	} else {
		int monthDiff = d1Data->month - d2Data->month;
		if (monthDiff != 0) {
			return monthDiff;
		} else {
			int dayDiff = d1Data->day - d2Data->day;
			if (dayDiff != 0) {
				return dayDiff;
			}
		}
	}
	return 0;
}

static void d_destroy(const Date *d) {
	free(d->self);
	free((void *)d); // need to use void pointer to free const var
}

static Date template = {
	NULL, d_duplicate, d_compare, d_destroy
};

const Date *Date_create(char *datestr) {
	Date *d = (Date *)malloc(sizeof(Date));

	if (d != NULL) {
		D_Data *dd = (D_Data *)malloc(sizeof(D_Data));
		
		if (dd != NULL) {
			int day, month, year;
			sscanf(datestr, "%d/%d/%d", &day, &month, &year);
			if (day > 31 || day < 1 || month < 1 || month > 12)
				d = NULL;
			if (d != NULL) {
				dd->day = day;
				dd->month = month;	
				dd->year = year;
				*d = template;
				d->self = dd;	
			} else {
				free(d);
				free(dd);
			}

		} else {
			free(dd);
			free(d);
			d = NULL;
		}	
	} else {
		free(d);
		d = NULL;
	}
	return d;
}

