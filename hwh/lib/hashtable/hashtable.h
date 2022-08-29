#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef unsigned (*hash_func)(void *);
typedef void (*data_dtor)(void *);

struct node_t {
    void *data;
    struct node_t *next;
};

struct hashtable_t;

struct hashtable_t *hashtable_ctor(unsigned sz, double threshold_coef, hash_func hashFunc, data_dtor dataDtor);
void hashtable_insert(struct hashtable_t *h, void *new_data);
int hashtable_count(struct hashtable_t *h, void *data, int (*data_comp)(void *, void *));
struct node_t *hashtable_find(struct hashtable_t *h, unsigned key);
void hashtable_dtor(struct hashtable_t *h);

unsigned hashatble_get_size(const struct hashtable_t *h);
unsigned hashtable_get_key(struct hashtable_t *h, void *data);

#endif //__HASH_TABLE_H__