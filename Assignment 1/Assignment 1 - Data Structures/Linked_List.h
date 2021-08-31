/******** Assignment 1, Name: Sagi Bitton
		  Id:205620859					********/


#pragma once
typedef struct List list;
struct List {
	int data;
	list* next;
};

list* BuildList();
void PrintList(list*);
list* BuildNode(int);
int Length(list* head);
void sortedInsert(list** head_ref);
void search(list* head, int x);
void reverse(list** head_ref);
int sumOfNodesUtil(list* head);
void sumOfNodes(list* head, int* sum);
int productOfNodes(list* head);
void fun(list* start);
//void productOfEvenIndexNodes(list* head, int* sum);
//int profuctOfNodesUtil(list* head);