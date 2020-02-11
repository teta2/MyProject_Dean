
#ifndef FUNCTIONS_H
#define FUNCTIONS_H


/**
* This function adds a record/protocol to a singly linked list. An item is added for each record/protocol.
* @param newptr is a pointer to the first item of our singly linked list.
*/
void AddRecord(struct record* newptr);
/**
* Standard selection: This is a sort algorithm to sort the argv[] array.
* Ignore the first 2 elements of the array.
* Protocols are sorted in ascending order depending on the course name they represent.
* @param argv[] array of character pointers
* @param size is the size of the number of files input
*/
void sort(char* argv[], int size);
/**
* This function puts items of our linked list.
* @param head is a pointer to the head of the list.
*/
void Put_list(struct record* head);


#endif