/******** Assignment 3, Name: Sagi Bitton
		  Id:205620859					********/
#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef struct Node StudentNode;
struct Node {
	int id;
	float mid_grade;
	float final_grade;
	StudentNode* left_child;
	StudentNode* right_child;
	StudentNode* parent;
};

typedef struct BST {
	 StudentNode* root;
};
void HelperReport(StudentNode* student);
void ReportStatistics(BST* tree);
int getNumOfFails(BST* tree);
int StudentStatistics(StudentNode* student);
void insert(BST* tree, int ID);
void reportGrades(BST* tree);
void printStudent(StudentNode* student);
int binSearch(StudentNode* student, int id);
int Search(BST* tree, int id);
void updateMidtermGrade(BST* tree, int ID, int newGrade);
void updateExamGrade(BST* tree, int ID, int newGrade);
int getFinalGrade(BST* tree, int ID);
double getAverageGrade(BST* tree);
int avg_helper(StudentNode* student);
int Count(BST* tree);
int HelperCount(StudentNode* student);
