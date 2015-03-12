#ifndef HASH
#define HASH

#include "globals.h"

#define INIT_SIZE 12

typedef struct element element;

struct element{
	char *key;
	int value;
	element *next;
};

typedef struct {
	int size;
	int num_elements;
	element **table;
}hashTable;

hashTable *hash_init();
int hash_delete(hashTable *hash); /* delete hash table */
int hash_add(hashTable *hash, char *key, int value);
int hash_get(hashTable *hash, char *key);
int hash_remove(hashTable *hash, char *key); /* remove element from hash table */
int hash_contains(hashTable *table, char *key); /* Can probably be implemented as part of the get */

#endif
