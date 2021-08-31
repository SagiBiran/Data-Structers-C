/******** Assignment 2, Name: Sagi Bitton
		  Id:205620859					********/

#pragma once
#ifndef _BINARY_TREE
#define _BINARY_TREE
typedef struct Node node;
struct Node {
	int data;
	node* left;
	node* right;
};

void levelStatistics(node* root, int level);
void printNodesAtLevel(node* root, int currentLevel, int level);
int findADepth(node* node);
bool isPerfectRec(struct Node* root, int d, int level = 0);
int isPerfect(node* root);
int sumOfKeys(node* root);
int countNodes(node* root);
int contains(node* node, int key);
void printLeaves(node* root);
int isEmpty(node* root);
node* NewNode(int);
node* randomInsertInto(node*, int);
node* randomTree();
void deleteTree(node*);
int height(node*);
void PrintGivenLevel(node*, int);
void PrintLevelOrder(node*);
void pre_order_traversal(node*);
#endif
