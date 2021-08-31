#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"
#include "HashTable.h"
#include <stdio.h>

//function will get htable and word and check whether this word exist in table or not
int isWordInDictionary(HashTable* dictionaryTable, char* word)
{
	if (search(dictionaryTable, word))
		return 1;
	return 0;
}


//-----------------------------------------------------------------------------------------------------------------\\
// for the whole functions downward each function get hashtable and word,each function check whether this word exist 
//in table or not if the word isn't exist there, then function will offer list of words that may be inside
//the table,later on, each function operate some manipulation and return list the contain
//few words that may be inside the table

//function will take each word, and break it into collection of words contaion letters from original words
//but seperated by spaces
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word)
{
	//add tests later....

	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;
	int len = strlen(word);
	char buffer1[250] = {"\0"};
	char* temp = (char*)malloc(strlen(word));
	char buffer3[250] = {"\0"};
	strcpy(temp, word+1);
	for (int i = 0; i<len-1; i++)
	{
		strncat(buffer1, word, 1);
		if (isWordInDictionary(dictionaryTable, buffer1) && isWordInDictionary(dictionaryTable, temp))
		{
			strcat(strcpy(buffer3, buffer1), " ");
			strcat(buffer3, temp);
			node=addToStart(node, buffer3);
		}
		word++;
		temp++;
	}
	return node;
}

//function will take each letter in original word and change by queue each word to letter that in range from a-z
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word)
{
	//add test later....
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;
	int len = strlen(word);
	char* temp = (char*)malloc(strlen(word));
	strcpy(temp, word);
	for (int i = 0; i < len; i++)
	{
		for (int j = 97; j < 127; j++)
		{
			temp[i]=j;
			if (strcmp(temp, word) == 0)
				continue;
			if (isWordInDictionary(dictionaryTable, temp))
				node = addToStart(node, temp);
		}
		temp[i] = word[i];
	}
	return node;
}

//function will take each letter in original word and remove by queue each letter to check whether after this change
//the word is exist in table
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word)
{
	//add test later....
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;
	int len = strlen(word);
	char* temp = (char*)malloc(strlen(word));
	char* right = (char*)malloc(strlen(word));
	strcpy(right, word+1);
	char left[250]={'\0'};
	strcpy(temp, word + 1);
	//check heads.
	if (isWordInDictionary(dictionaryTable, temp))
		node = addToStart(node, temp);
	for (int i = 1; i < len; i++)
	{
		strncat(left, word, 1);
		strcpy(right, right + 1);
		strcpy(temp, left);
		strcat(temp, right);
		if (isWordInDictionary(dictionaryTable, temp))
			node = addToStart(node, temp);
		word++;
	}
	return node;

}

//function will take each letter in original word and change by queue each word to letter that in range from a-z
//the difference between this function and replacecharactercheck is that this function will add every letter by queue
//in each space in original word
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;
	int len = strlen(word);
	char* s_word = (char*)malloc(strlen(word)+1);
	char* e_word = (char*)malloc(strlen(word)+1);
	char* temp_word = (char*)malloc(strlen(word)+1);
	temp_word = NULL;
	strcpy(s_word + 1, word);
	strcpy(e_word, word);
	for (int j = 97; j < 127; j++)
	{
		s_word[0] = j;
		e_word[len] = j;
		e_word[len+1] = '\0';
		if (isWordInDictionary(dictionaryTable, s_word))
			node = addToStart(node, s_word);
		if (isWordInDictionary(dictionaryTable,e_word))
			node = addToStart(node, e_word);
	}

	char left[250] = { '\0' };
	char* right = (char*)malloc(strlen(word));
	//strcpy(temp, word + 1);
	for (int i = 0; i < len-1; i++)
	{
		strncat(left, word, 1);
		strcpy(right, word + 1);
		temp_word=left;
		strcat(temp_word + (i + 1), " ");
		strcat(temp_word+(i+2), right);
		for (int j = 97; j < 127; j++)
		{
			temp_word[i + 1] = j;
			if (isWordInDictionary(dictionaryTable, temp_word))
				node = addToStart(node, temp_word);
			temp_word[i + 1] = { '\0' };
		}
		word++;
	}
	return node;

}

//function will take original word, will replace each pair of closed letter and check whether
//new word is exist in table or not.
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;
	int len = strlen(word);
	char* temp_word = (char*)malloc(strlen(word)+1);
	char temp[1];
	strcpy(temp_word,word);
	for (int i = 0; i < len-1; i++)
	{
		temp[0] = temp_word[i + 1];
		temp_word[i + 1] = temp_word[i];
		temp_word[i] = temp[0];
		if (isWordInDictionary(dictionaryTable, temp_word))
			node = addToStart(node, temp_word);
		strcpy(temp_word, word);
	}
	return node;
}
//-----------------------------------------------------------------------------------------------------------------\\

//function will get table and word, will lunch whole function upwards and in the end return
//list with all suggestion words after filted by these functions/
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word)
{
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node = NULL;	
	LinkedList* templist = (LinkedList*)malloc(sizeof(LinkedList));
	node = (addSpaceCheck(dictionaryTable, word));
	templist = replaceCharacterCheck(dictionaryTable, word);
	node = Checker(node,  templist, word);
	templist = NULL;
	templist = deleteCharacterCheck(dictionaryTable,word);
	node = Checker(node,  templist, word);
	templist = NULL;
	templist = addCharacterCheck(dictionaryTable,word);
	node = Checker(node,  templist, word);
	templist = NULL;
	templist = switchAdjacentCharacterCheck(dictionaryTable,word);
	node = Checker(node,  templist, word);
	
	return node;
}

//helper function gor getWordSuggestion function.
LinkedList* Checker(LinkedList* node, LinkedList* templist, char* word)
{
	LinkedList* temp_node = (LinkedList*)malloc(sizeof(LinkedList));
	temp_node = node;
	if (isInList(templist, word))
		DeleteElement1(templist, word);
	while (templist!=NULL)
	{
		while (temp_node != NULL)
		{
			if (strcmp(templist->data, temp_node->data) == 0)
			{
				DeleteElement1(templist, temp_node->data);
				break;
			}
			else
				temp_node = temp_node->next;
		}
			temp_node = node;
			node=addToStart(node, templist->data);
			templist = templist->next;
	}
	return node;
}