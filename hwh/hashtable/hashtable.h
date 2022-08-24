#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define START_HT_SIZE 128
#define START_BUF_CAPACITY 128
#define HASH_THRESHOLD 0.75

typedef unsigned (*hash_func)(void *);
typedef void (*data_dtor)(void *);

struct node_t {
    void *data;
    struct node_t *next;
};

struct hashtable_t;

struct hashtable_t *hashtable_ctor(unsigned sz, double threshold_coef, hash_func hashFunc, data_dtor dataDtor);
struct node_t *add_node(void *new_data);
void hashtable_insert(struct hashtable_t *h, void *new_data);
void hashtable_resize(struct hashtable_t *h);
int hashtable_count(struct hashtable_t *h, void *data, int (*data_comp)(void *, void *));
void list_dtor(struct hashtable_t *h);
void hashtable_dtor(struct hashtable_t *h);

unsigned hashatble_get_size(struct hashtable_t *h);
unsigned hashtable_get_key(struct hashtable_t *h, void *data);
struct node_t **hashtable_get_arr(struct hashtable_t *h);

#endif //__HASH_TABLE_H__