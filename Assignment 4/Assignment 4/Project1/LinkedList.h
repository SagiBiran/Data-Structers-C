#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;

struct LinkedList {
	char* data; 
	LinkedList* next;
};

void PrintList(LinkedList*);
LinkedList* BuildNode(char*);
LinkedList* FreeList(LinkedList* head);
int isInList(LinkedList* head, char* str);
LinkedList* addToStart(LinkedList*, char*);
LinkedList* DeleteElement1(LinkedList*, char*);


