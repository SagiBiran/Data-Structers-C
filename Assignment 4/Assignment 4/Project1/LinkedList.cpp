#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "LinkedList.h"
#include "HashTable.h"
#include "WordSpellingChecker.h"

//funciton will create a newnnode from Linklist struct
//will implement member field inside the struct aswell
LinkedList* BuildNode(char* temp_str)
{
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node->data =(char*)malloc(strlen(temp_str) + 1);
	strcpy(node->data,temp_str);
	node->data[strlen(temp_str) + 1] = '\0';
	node->next = NULL;
	return node;
}

//funciton will get head of linklist and print whole linkedlist
void PrintList(LinkedList* head)
{
	LinkedList* temp = head;
	//printf("\nThe list is: ");
	while (temp != NULL)
	{
		printf("%s ", temp->data);
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
}

//funciton will head of linkedlist and word,will search whether
//this word is exist in this linkedlist
int isInList(LinkedList* head, char* str)
{
	LinkedList* current = head;  // Initialize current 
	while (current != NULL)
	{
		if (strcmp(current->data, str) == 0)
			return 1;
		current = current->next;
	}
	return 0;
}

//function will free allocated memory that used in specific linkedlist
LinkedList* FreeList(LinkedList* head)
{
	/* deref head_ref to get the real head */
	LinkedList* current = head;
	LinkedList* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	/* deref head_ref to affect the real head back
	   in the caller. */
	head = NULL;
	return head;
}

//function will get head of linkedlist and word, that function will
//create a new node, assign the field for name with the words given
//in the function and return linkedlist
LinkedList* addToStart(LinkedList* head, char* str)
{
	LinkedList* temp_element = BuildNode(str);
	if (head != NULL)
		temp_element->next = head;
	return temp_element;
}

//function will get head of linkedlist and word,will search for the
//node that included the str , delete the node and return head of linkedlist
LinkedList* DeleteElement1(LinkedList* head, char* str)
{
	if (head == NULL)
		return head;
	//if we found in the head of the linkedlist
	if (strcmp(head->data, str)==0)
	{
		LinkedList* next = head->next;
		free(head);
		return next;
	}
	LinkedList* temp_head = head;
	while (temp_head->next != NULL)
	{
		if (strcmp(temp_head->next->data, str)==0)
		{
			LinkedList* next = temp_head->next;
			temp_head->next = temp_head->next->next;
			free(temp_head->next);
			break;
		}
		temp_head = temp_head->next;
	}
	return head;
}
