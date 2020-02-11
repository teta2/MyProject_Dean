#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "Record.h"
#include "Functions.h"



#pragma warning(disable : 4996)
/// Most of my comments were issued while I was trying to do my code...

using namespace std;
struct record* head = NULL;

void AddRecord(struct record* newptr)
{
	/// when there are no records in the linked list
	if (head == NULL)
	{
		head = newptr;
		return;
	}

	/// Add to the linked list
	struct record* temp = head;
	head = newptr;
	newptr->next = temp;
}

void sort(char* argv[], int size)
{
	char minstring[255], temp[255];
	for (int i = 2; i < size - 1; ++i)
	{
		int min = i;
		strcpy(minstring, argv[i]);
		for (int j = i + 1; j < size; ++j)
		{
			if (strcmp(minstring, argv[j]) > 0)
			{
				min = j;
				strcpy(minstring, argv[j]);
			}
		}

		/// Swap 
		strcpy(temp, argv[i]);
		strcpy(argv[i], argv[min]);
		strcpy(argv[min], temp);
	}
}
// This function enabled me to check my code...(It is not really part of my code/Program)
void Print()
{
	cout << "\nThe LL now is :" << endl;
	struct record* temp = head;
	while (temp != NULL)
	{
		cout << temp->id << ": " << temp->course << "=> ";
		temp = temp->next;
	}
}


int main(int argc, char* argv[])
{
	
	cout << "Number of command line arguments = " << (argc - 2) << endl;

	if (argc < 3)
	{
		cout << "\nYou need at least 2 command line arguments.";
		return 0;
	}

	if (strcmp(argv[1], "-i"))
	{
		cout << "\nInvalid command. Please use -i <file1> <file2>" << endl;
		return 0;
	}

	///Sort the argv[] array by course names 
	sort(argv, argc);

	/// Number of records in the linked list
	int count = 0;

	for (int i = 2; i < argc; ++i)
	{
		cout << "Reading file " << argv[i] << endl;
		ifstream in(argv[i]);

		if (!in)
		{
			cout << "Cannot open input file " << argv[i] << ".\n";
			return 1;
		}


		char course[255], prof[255];
		FILE* fp = fopen(argv[i], "r");
		int line = 0;

		char fname[255], lname[255], dat[20], id[20];
		float gpa;

		ifstream input(argv[i]);
		string l;

		/// Read the first two lines in the file. They have the course name and the Professor's name.
		getline(input, l);
		strcpy(course, l.c_str());
		/// cout<<"Course: "<<course<<endl;

		getline(input, l);
		strcpy(prof, l.c_str());
		///cout<<"Professor: "<<prof<<endl;

		struct record* recordptr = NULL;

		while (getline(input, l))   ///for each line in the file
		{
			///cout << "Reading line " << l << endl;
			int n = l.length();
			char* char_array = new char[n + 1];
			strcpy(char_array, l.c_str());
			char* p = strtok(char_array, " ");
			int i = 0;

			/// Create a new record using dynamic memory allocation. Tokenize the line, and take the parts one by one. The first part is the first name, the second part is the last name, the third the student ID, then the gpa, and then the date 
			recordptr = new record();
			++count;
			while (p)
			{
				switch (i)
				{
				case 0: strcpy(recordptr->fname, p); break;
				case 1: strcpy(recordptr->lname, p); break;
				case 2: strcpy(recordptr->id, p); break;
				case 3: recordptr->gpa = atof(p); break;
				case 4: strcpy(recordptr->dat, p); break;
				}
				p = strtok(NULL, " ");
				++i;
			}

			strcpy(recordptr->course, course);
			strcpy(recordptr->prof, prof);
			recordptr->next = NULL;

			/// Add that record to the linked list of records.
			AddRecord(recordptr);
			delete[] char_array;
		}

		fclose(fp);
	}

	/* All files have been read. Now, traverse the linked list node by node, and for each record, add the information to the student's file */

	struct record* temp = head;
	while (temp != NULL)
	{
		///cout << "\nPrinting to file " << temp->id << ": " << temp->course << endl;
		ifstream f(temp->id);
		if (!f.good())
		{
			/// file does not exist
			///cout << "\nfile doesnt exist" << endl;
			FILE* fp2 = fopen(temp->id, "w");
			fprintf(fp2, "%s %s\nID: %s\n", temp->fname, temp->lname, temp->id);
			fclose(fp2);
		}

		/// Write the details of the course to the student's file.
		FILE* fp = fopen(temp->id, "a");
		fprintf(fp, "%s %s %f %s\n", temp->prof, temp->course, temp->gpa, temp->dat);
		fclose(fp);
		temp = temp->next;
	}

	// Now, delete the linked list to avoid memory leaks
	struct record* p;
	temp = head;
	while (temp != NULL)
	{
		p = temp;
		temp = temp->next;
		delete p;
	}
	
	return 0;

}