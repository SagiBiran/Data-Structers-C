#include "HashTable.h"
#include "LinkedList.h"

//hash function will get input and return constant 3
int constantStringHashFunction(char* str)

{
	return 3;
}

//hash function will get input and return sum of char (ascii represent)

int accumulateStringHashFunction(char* str)
{
    int i, sum;
    for (sum = 0, i = 0; i < strlen(str); i++)
        sum += str[i];
    return sum;
}

//hash function get input and return sum of cham with ascii and short mathematic calculation.
int improvedHashFunction(char* str)

{
    int i, sum ,temp_size=strlen(str)-1;
    for (sum = 0, i = 0; i < strlen(str); i++)
    {
        sum += str[i] * pow(2,temp_size);
        temp_size--;
    }
    return sum;
}


//function gets size and hashfunction and create hashtable object
HashTable* initTable(int tableSize, int hashFunction)
{
	HashTable* htable = (HashTable*)malloc(sizeof(HashTable));
	if (htable == NULL)
	{
		printf("Unable to allocate memory,program quit...");
		return NULL;
	}
	htable->tableSize = tableSize;
	htable->hashFunction = hashFunction;

	htable->hashTable = (HashTableElement*)malloc(sizeof(HashTableElement) * tableSize);
	if (htable->hashTable == NULL)
	{
		printf("error,memory allocation...");
		return NULL;
	}
	for (int i = 0; i < tableSize; i++)
	{
		htable->hashTable->key = i;
		htable->hashTable[i].chain = (LinkedList*)malloc(sizeof(LinkedList));
		if (htable->hashTable[i].chain == NULL)
		{
			printf("error,memory allocation...");
			return NULL;
		}
		htable->hashTable[i].chain = NULL;
	}
	return htable;

}

//function gets hashtable and word and return his index calculated by hash function
int hash(char* str, HashTable* ht)
{
	int hFuncValue;
	switch (ht->hashFunction)
	{
	case 1:
		hFuncValue = abs(constantStringHashFunction(str));
		break;
	case 2:
		hFuncValue = abs(accumulateStringHashFunction(str));
		break;
	case 3:
		hFuncValue = abs(improvedHashFunction(str));
		break;
	}
	int index = hFuncValue % ht->tableSize;
	return index;
}


//function gets hashtable and word and insert this word into the table depend on hashfunction value 
int insert(HashTable* ht, char* str)
{
	if (!str||search(ht,str))
		return 0;
	int current_index = hash(str, ht);
	ht->hashTable[current_index].chain = addToStart(ht->hashTable[current_index].chain, str);
	return 1;
}

//function gets hashtable and word and remove this word from table, fix the linked list as 
//it should be and return head of linked list
int deleteElement(HashTable* ht, char* str)
{
	if (!str || search(ht, str))
		return 0;
	int current_index = hash(str, ht);
	ht->hashTable[current_index].chain = DeleteElement1(ht->hashTable[current_index].chain, str);
	return 1;
}

//function gets hashtable and word. function will search whether this word
//located in the table, if yes, return 1 otherwise return 0
int search(HashTable* ht, char* str)
{
	if (!str)
		return 0;
	int current_index = hash(str, ht);
	if (isInList(ht->hashTable[current_index].chain, str))
		return 1;
	return 0;
}