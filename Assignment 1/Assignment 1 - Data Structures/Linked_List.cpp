/******** Assignment 1, Name: Sagi Bitton
		  Id:205620859					********/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//define node struct
typedef struct List list;
struct List {
	int data;
	list* next;
};


//function that create new node
list* BuildNode(int num1)
{
	list* node = (list*)malloc(sizeof(list));
	node->data = num1;
	node->next = NULL;
	return node;
}

//function that create Linked_List using BuildNode functions(create one by one)
list* BuildList()
{
	list* head = NULL, * temp = head;
	int num;
	printf("Enter numbers for list, -1 for end: \n");
	scanf("%d ", &num);
	while (num != -1)
	{
		if (head == NULL)
		{
			head = BuildNode(num);
			temp = head;
		}
		else
		{
			temp->next = BuildNode(num);
			temp = temp->next;
		}
		scanf("%d", &num);
	}
	return head;
}

//function that return Link Listed length 
int Length(list* head) //function that gets linked_list and return number of elements in it
{
	int count = 0;
	list* temp = head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
//function that prints Linked List
void PrintList(list* head)
{
	list* temp = head;
	printf("\nThe list is: ");
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//function that insert one node into Linked List by order
void sortedInsert(list** head_ref) 
{
	//first ask for new node input from user.
	list* new_nod = (list*)malloc(sizeof(list));
	int temp;
	printf("Please enter new data into new node\n");
	scanf("%d", &temp);
	new_nod->data = temp;
	new_nod->next = NULL;

	list* current;
	/* Special case for the head end */
	if (*head_ref == NULL || (*head_ref)->data >= new_nod->data) {
		new_nod->next = *head_ref;
		*head_ref = new_nod;
	}
	else {
		/* Locate the node before the point of insertion */
		current = *head_ref;
		while (current->next != NULL && current->next->data < new_nod->data) {
			current = current->next;
		}
		new_nod->next = current->next;
		current->next = new_nod;
	}
}

// Checks whether the value x is present in linked list //
void search(list* head, int x)
{
	int index = 1;
	list* current = head;  // Initialize current 
	while (current != NULL)
	{
		if (current->data == x)
		{
			printf("Element found under index number: ");
			printf("%d", index);
			return;
		}
		current = current->next;
		index++;//increase i in order to see which index was found
	}
	printf("Node is not exist in Link Listed");
}

//Function to reverse the linked list //

void reverse(list** head_ref)
{
	list* prev = NULL;
	list* current = *head_ref;
	list* next = NULL;
	while (current != NULL) {
		// Store next
		next = current->next;

		// Reverse current node's pointer
		current->next = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

// function to recursively find the sum of 
// nodes of the given linked list 
void sumOfNodes(list* head, int* sum)
{
	// if head = NULL 
	if (!head)
		return;

	// recursively reverse the remaining nodes 
	sumOfNodes(head->next, sum);

	// accumulate sum 
	*sum = *sum + head->data;
}

// utility function to find the sum of  nodes 
int sumOfNodesUtil(list* head)
{
	int sum = 0;
	// find the sum of  nodes 
	sumOfNodes(head, &sum);
	// required sum 
	return sum;
}



// Function to find the product of 
// nodes of the given linked list 
int productOfNodes(list* head)
{
	int index = 1;
	// Pointer to traverse the list 
	list* ptr = head;
	int product = 1; // Variable to store product 

	// Traverse the list and 
	// calculate the product 
	while (ptr != NULL) 
	{
		if (index % 2 == 0)//condition to check whether index in even or not
		{
			product *= ptr->data;
			ptr = ptr->next;
			index++;
		}
		else
		{
			ptr = ptr->next; //anyway we need to forward nodes
			index++; //increase index
		}
	}
	// Return the product 
	return product;
}


void fun(list* start)
{

	if (start == NULL)
		return;
	printf("%d ", start->data);

	if (start->next != nullptr)
		fun(start->next->next);
	printf("%d ", start->data);

}
