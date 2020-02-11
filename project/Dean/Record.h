#ifndef RECORD_H
#define RECORD_H

typedef struct record
{
	char course[255];
	char prof[255];
	char fname[255];
	char lname[255];
	char dat[20];
	char id[20];
	float gpa;
	struct record* next;
}record;


#endif 
