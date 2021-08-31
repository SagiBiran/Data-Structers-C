/******** Assignment 2, Name: Sagi Bitton
		  Id:205620859					********/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"BinaryTree.h"

int main()
{
	srand(time(NULL));
	node* root;
	int H;
	root = randomTree();
	H = height(root);
	printf("\n\nHeight of tree is %d\n", H);
	printf("\nLevels of Bynary Tree:\n");
	PrintLevelOrder(root);
	printf("\nPreorder Traversal tree\n");
	pre_order_traversal(root);
	printLeaves(root);
	//deleteTree(root);
	//printf("\nTree deleted\n");
	printf("%d", isEmpty(root));
	int key = 0;
	if (contains(root, key))
		printf("1");
	else
		printf("0");
	printf("%d", countNodes(root));
	int sum = sumOfKeys(root);
	printf("sum of all elements is: %d", sum);
	levelStatistics(root, 2);
	if (isPerfect(root))
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}