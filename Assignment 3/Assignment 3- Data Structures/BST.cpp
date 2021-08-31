/******** Assignment 3, Name: Sagi Bitton
		  Id:205620859					********/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "BST.h"

//global variables in order to track over 
//grades for students and make statistics
int Fail = 0;
int Good = 0;
int Very_Good = 0;
int Excellent = 0;

//funciton purpose is to add new student into BST.
//If student has already exist in BST then funciton will 
//not do nothing
void insert(BST* tree, int ID)
{
	//Extreme testing to check whether student
	//is already exist in BST
	if (Search(tree, ID))
		return;

	StudentNode* new_student = (StudentNode*)malloc(sizeof(StudentNode));
	new_student->id = ID;
	new_student->mid_grade = 0;
	new_student->final_grade = 0;
	new_student->left_child = NULL;
	new_student->right_child = NULL;
	new_student->parent = NULL;
	StudentNode* Y = NULL;
	StudentNode* X = tree->root;

	while (X != NULL)
	{
		Y = X;
		if (new_student->id < X->id)
			X = X->left_child;
		else
			X = X->right_child;
	}
	new_student->parent = Y; //Update parent for new node

	if (Y == NULL) //Extreme test to check that tree wasn't empty
		tree->root = new_student;
	else if (Y->id > ID)
		Y->left_child = new_student;
	else
		Y->right_child = new_student;
}

//helper function for reportGrades function
//will help to print all students information
void printStudent(StudentNode* student)
{
	if (student == NULL)
		return;
	printf("(");
	printStudent(student->left_child);
	float temp_grade = (student->final_grade) * 0.7 + (student->mid_grade) * 0.3;
	temp_grade =  (float)((int)(temp_grade + 0.5));
	printf("Student id: %d \t MiddleExam Grade: %.2f \t FinalExamGrade: %.2f \t FinalGrade: %.f", student->id,student->mid_grade, student->final_grade,temp_grade);
	printStudent(student->right_child);
	printf(")");
}

//function will print student information
//will use helper function upward
void reportGrades(BST* tree)
{
	printStudent(tree->root);
	printf("\n");

}

// helper function to find node (student) in BST
int binSearch(StudentNode* student, int id)
{
	if (student == NULL)
		return 0;
	if (student->id == id)
		return 1;
	if (id <= student->id)
		return binSearch(student->left_child, id);
	else
		return binSearch(student->right_child, id);
}

//main function to search for student in BST
int Search(BST* tree, int id)
{
	int flag = binSearch(tree->root, id);
	return flag;
}
void updateMidtermGrade(BST* tree, int ID, int newGrade)
{
//if we enter this if then id for student as found and we
//will give to user the option to enter score for midtermGrade
	if (Search(tree, ID))
	{
		StudentNode* X = tree->root;
		//while loop to find exact student
		while (X->id != ID)
		{
			if (ID < X->id)
				X = X->left_child;
			else if (ID > X->id)
				X = X->right_child;
		}
		X->mid_grade = newGrade; //update grade to mid_grade.
	}
	//if we reached here, then id is not exist in BST
	else
		return;
}

void updateExamGrade(BST* tree, int ID, int newGrade)
{
	//if we enter this if then id for student as found and we
	//will give to user the option to enter score for midtermGrade
	if (Search(tree, ID))
	{
		StudentNode* X = tree->root;
		//while loop to find exact student
		while (X->id != ID)
		{
			if (ID < X->id)
				X = X->left_child;
			else if (ID > X->id)
				X = X->right_child;
		}
		X->final_grade = newGrade; //update grade to mid_grade.
	}
	//if we reached here, then id is not exist in BST
	else
		return;
}



int getFinalGrade(BST* tree, int ID)
{
	//if we enter this if then id for student as found and we
//will give to user the option to enter score for midtermGrade
	if (Search(tree, ID))
	{
		StudentNode* X = tree->root;
		//while loop to find exact student
		while (X->id != ID)
		{
			if (ID < X->id)
				X = X->left_child;
			else if (ID > X->id)
				X = X->right_child;
		}
		float temp_grade = (X->final_grade) * 0.7 + (X->mid_grade) * 0.3;
		return (float)((int)(temp_grade + 0.5)); //this statement inorder to return round up / round down
												 // final grade
	}
	//if we reached here, then id is not exist in BST
	else
		return 0;
}

double getAverageGrade(BST* tree)
{

	return avg_helper(tree->root);
	//printf("\n");

	
}

int avg_helper(StudentNode* student)
{
		int A;
		if (student == NULL)
			return 0;
		A=(( student->final_grade*0.3 + student->mid_grade * 0.7) + avg_helper(student->left_child) + avg_helper(student->right_child))/(HelperCount(student));
		return A + 0.5 * HelperCount(student);

}

//function that return number of student in
//given BST 
int Count(BST* tree)
{
	return HelperCount(tree->root);
}

int HelperCount(StudentNode* student)
{
	int c = 1;             //Node itself should be counted
	if (student == NULL)
		return 0;
	else
	{
		c += HelperCount(student->left_child);
		c += HelperCount(student->right_child);
		return c;
	}
}


int getNumOfFails(BST* tree)
{
	return (StudentStatistics(tree->root));
}

//Heler Function. function get information about student grades
//will return how many students failed the course + make statistics
//over students and map them : good,very good,excellent
int StudentStatistics(StudentNode* student)
{
	if (student == NULL)
		return 0;
	StudentStatistics(student->left_child);
	float temp_grade = (student->final_grade) * 0.7 + (student->mid_grade) * 0.3;
	temp_grade = (float)((int)(temp_grade + 0.5));
	if (temp_grade < 56)
		Fail++;
	StudentStatistics(student->right_child);
	return Fail;
}

//helper report statistics
void HelperReport(StudentNode* student)
{
	if (student == NULL)
		return;
	HelperReport(student->left_child);
	float temp_grade = (student->final_grade) * 0.7 + (student->mid_grade) * 0.3;
	temp_grade = (float)((int)(temp_grade + 0.5));
	if (temp_grade >= 56 && temp_grade <= 75)
		Good++;
	else if (temp_grade >= 76 && temp_grade <= 94)
		Very_Good++;
	else if(temp_grade>=95 && temp_grade<=100)
		Excellent++;
	HelperReport(student->right_child);
}


void ReportStatistics(BST* tree)
{
	//first we need to lunch foo
	HelperReport(tree->root);
	printf("\t  Degree    Final Grade");
	printf("\n");
	printf("Good      (56-75)   \t %d \t", Good);
	printf("\n");
	printf("Very Good (76-94)  \t %d   \t", Very_Good);
	printf("\n");
	printf("Excellent (95-100) \t %d  \t", Excellent);
	printf("\n");
}