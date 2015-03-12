#include <stdio.h>

#include "globals.h"
#include "hash.h"

main() {
	hashTable *table = hash_init(INIT_SIZE);

	hash_add(table, "a", 3);
	hash_add(table, "ab", 4);
	hash_add(table, "b", 8);
	hash_add(table, "ac", 5);

	printf("ab=%d\n",hash_get(table, "ab"));
	printf("b=%d\n",hash_get(table, "b"));

	hash_remove(table, "ab");

	printf("ab=%d\n",hash_get(table, "ab"));
	//hash_delete(table);
}
