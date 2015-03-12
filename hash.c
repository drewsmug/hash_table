#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "globals.h"
#include "hash.h"

hashTable *hash_init(int size)
{

	hashTable *hash = malloc(sizeof(hashTable));
	if(!hash) return NULL;

	element **table = malloc(sizeof(element*) * size);
	if(!table) return NULL;

	hash->table = table;
	hash->size = size;
	hash->num_elements = 0;

	int c;
	for(c = 0; c < size; c++)
	{
		hash->table[c] = NULL;
	}


	return hash;
}

int hash_delete(hashTable *hash)
{
	int c;
	int hash_size = hash->size;

	/* free() each element */
	for(c = 0; c < hash_size; c++)
	{
		if(hash->table[c])
		{
			element *tail = hash->table[c];
			element *curr = tail->next;
			for(curr; curr; curr = curr->next)
			{
				free(tail);
				hash->num_elements--;
				tail = curr;
			}
			free(tail);
			hash->num_elements--;
		}
	}

	if(hash->num_elements != 0)
	{
		printf("Didn't free every element. hash_size = %d\n",hash->num_elements);
		return FAILURE;
	}

	/* free() **table - the array of pointers */
	free(hash->table);

	/* free() hash */
	free(hash);

	return SUCCESS;
}

static int hash_key(hashTable *hash, char *key)
{
	return (key[0] - '0') % hash->size;
}

hashTable *double_hash_table_size(hashTable *hash)
{
	int new_hash_size = hash->size;
	if (new_hash_size >= 13)
		new_hash_size = 26;
	else
		new_hash_size <<= 1;

	hashTable *new_hash_table = hash_init(new_hash_size);

	int c;
	for(c = 0; c < hash->size ; c++)
	{
		if(hash->table[c])
		{
			element *curr = hash->table[c];
			for(curr; curr; curr = curr->next)
			{
				hash_add(new_hash_table, curr->key, curr->value);
			}
		}
	}

	hash_delete(hash);

	return new_hash_table;
}

int hash_add(hashTable *hash, char *key, int value)
{
	/* This element already exist */
	if(hash_get(hash, key) != FAILURE)
		return FAILURE;


	/* If half full double table size */
	if(hash->size < 26 && hash->num_elements >= (hash->size >> 1))
		hash = double_hash_table_size(hash);

	hash->num_elements++;
	int index = hash_key(hash, key);

	element *new_element = malloc(sizeof(element));
	new_element->key = key;
	new_element->value = value;
	new_element->next = NULL;

	if(!hash->table[index])
	{
		hash->table[index] = new_element;
	}
	else
	{
		element *curr = hash->table[index];
		for(curr; curr; curr = curr->next)
		{
			if(!curr->next)
				break;
		}
		curr->next = new_element;
	}

	return SUCCESS;
}

int hash_get(hashTable *hash, char *key)
{
	int found = FAILURE;
	int index = hash_key(hash, key);

	element *curr = hash->table[index];

	for(curr; curr; curr = curr->next)
	{
		if(!strncmp(curr->key, key, 100))
		{
			found = SUCCESS;
			break;
		}
	}
	return found == SUCCESS ? curr->value : FAILURE;
}

int hash_remove(hashTable *hash, char *key)
{
	if(hash_get(hash, key) == FAILURE)
		return FAILURE;

	int index = hash_key(hash, key);
	element *tail = hash->table[index];
	element *curr = tail->next;

	for(curr; curr; curr = curr->next)
	{
		if(!strncmp(tail->key, key, 100))
		{
			break;
		}
	}

	printf("curr=%s tail=%s\n",curr->key,tail->key);

	return SUCCESS;
}
