#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define WORDLEN 20

struct node_t;
struct hashtable_t;


struct hashtable_t *hashtable_ctor(unsigned m);
void hashtable_insert(struct hashtable_t *h, unsigned key, const char *value);
const char *hashtable_find(struct hashtable_t *h, unsigned key);
void hashtable_dtor(struct hashtable_t *h);
unsigned hash(const char *str);

#endif //__HASH_TABLE_H__