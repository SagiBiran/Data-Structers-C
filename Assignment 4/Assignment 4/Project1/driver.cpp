/*
Assignment 4
Actors: Sagi Bitton, Id : 205620859 && Yarden Hayut, Id: 205432693
Collage : Be'er Sheva

*/



#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"
#include "HashTable.h"
#include <stdio.h>
#include <ctype.h>
#define max_size 1000
#define n 20

int parseWordsToTable(char* path, HashTable* ht);
SpellingSuggestion* spellingCheck(char* text);
int cnt_space(char* input);
int catchword(char(*buffer)[n][n], int* size, char* word, HashTable* ht);
void printSpellingSuggestions(SpellingSuggestion* SpellingS);
SpellingSuggestion* help_func(int* size, int wsize, HashTable* ht, SpellingSuggestion* spell, char(*buffer)[n]);

int main()
{
	char text[] = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* spellingSuggestions = spellingCheck(text);
	printSpellingSuggestions(spellingSuggestions);
	return 0;
}


//function will get path for file with given words and insert it into hashtable
int parseWordsToTable(char* path, HashTable* ht)
{
	char* temp=(char*)malloc(80*sizeof(char));
	if (path == NULL)
	{
		printf("Can't open input file in.txt!\n");
		return 0;
	}
	FILE* fin;
	fin = fopen(path, "r");
	if (fin == NULL)
	{
		printf("Can't open input file in.txt!\n");
		return 0;
	}
	while (fscanf(fin, "%s", temp) != EOF)
	{
		insert(ht, temp);
	}
	fclose(fin);
	return 1;
}

//this function will get input, lunch other function and return list of wrong words
//and list of lists for suggestions words to offer the user/
SpellingSuggestion* spellingCheck(char* text)
{
	if (!text || *text == '\0')
		return NULL;
	HashTable* ht = initTable(max_size, 3);
	char path[] = "C:/dictionary.txt"; 
	parseWordsToTable(path, ht);
	char buffer[20][20] = {'\0'};
	int* o_size = (int*)malloc(sizeof(int));
	*o_size = strlen(text);
	int wrongwords = catchword(&buffer, o_size,text,ht);
	//if we reached here then each word in given input in found in dictonary hence 
	if (wrongwords==0)
		return NULL;
	else
	{
		SpellingSuggestion* spellchecker = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion) * wrongwords);
		return help_func(o_size, wrongwords, ht, spellchecker, buffer);
	}
}

//helper function the gets input and return amount of words seperated by spaces.
int cnt_space(char* input)
{
	int i = 0, counter = 0;
	// input sentence 
	//char buf[50] = "Geeks for Geeks";
	char ch = (input)[0];

	// counting spaces 
	while (ch != '\0') {
		ch = (input)[i];
		if (isspace(ch))
			counter++;

		i++;
	}

	// returning number of spaces 
	return (counter);
}

//helper function, gets list of unordered words, two sizes and table,
//return amount of words that doesn't exist in the table,and list with ordered words
//seperated by spaces.
int catchword(char(*buffer) [n][n],int* size,char* word, HashTable* ht)
{
	int i, j = 0, ctr = 0,counter=0;
	for (i = 0; i <= *size; i++)
	{
		// if space or NULL found, assign NULL into newString[ctr]
		if (word[i] == ' ' || word[i] == '\0')
		{
			(*buffer)[ctr][j] = '\0';
			ctr++;  //for next word
			j = 0;    //for next word, init index to 0
		}
		else
		{
			(*buffer)[ctr][j] = word[i];
			j++;
		}

	}
	for (i = 0; i < ctr; i++)
	{
		if (!isWordInDictionary(ht, (*buffer)[i]))
			counter++;
	}
	*size = ctr;
	return counter;
}

//function will get SpellingSuggerstion object, will run from head of list untill end
//and print wrong word,and list of suggestion words for this wrong input
void printSpellingSuggestions(SpellingSuggestion* SpellingS)
{
	while (SpellingS != NULL)
	{
	printf("The word %s was misspelled. Did you mean: \n", SpellingS->originalWord);
	PrintList(SpellingS->suggestions);
	SpellingS->next = SpellingS->next;
	SpellingS->next = SpellingS->next;
	}
}

//another helper function to spellingCheck function, will get two sizes, htabe, spelling suggerstion object and list of words,
//this function will build a spellingsuggestion object fixed as it should be and return that head of object.
SpellingSuggestion* help_func(int* size, int wsize , HashTable* ht, SpellingSuggestion* spell, char(*buffer)[n])
{
	SpellingSuggestion* spellchecker = spell;
	for (int i = 0; i < *size; i++)
	{
		if (!isWordInDictionary(ht, buffer[i]))
		{
			spellchecker->originalWord = (char*)malloc(strlen(buffer[i]) + 1);
			strcpy(spellchecker->originalWord, buffer[i]);
			if (getWordSuggestions(ht, buffer[i]) == NULL)
				spellchecker->suggestions = NULL;
			spellchecker->suggestions = getWordSuggestions(ht, buffer[i]);
			printf("The word %s was misspelled. Did you mean: \n", buffer[i]);
			PrintList(spellchecker->suggestions);
			spellchecker->next = spellchecker->next;
		}
		else
			continue;
	}
	spellchecker->next = NULL;
	return spell->next;
}