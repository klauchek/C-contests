#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define START_SIZE 128
#define HASH_THRESHOLD 0.75

typedef unsigned (*hash_func)(const char *);

struct node_t;
struct hashtable_t;

struct hashtable_t *hashtable_ctor(unsigned sz, double threshold_coef, hash_func hashFunc);
char* make_buffer(unsigned buf_len);
char* make_word(const char *str);
void hashtable_fill(struct hashtable_t *h, unsigned buf_len);
struct node_t *add_node(const char *value);
void hashtable_insert(struct hashtable_t *h, const char *value);
int hashtable_find(struct hashtable_t *h, unsigned key, const char *str);
void hashtable_resize(struct hashtable_t *h);
void freq_count(struct hashtable_t *h, unsigned w_buf_len);
void list_dtor(struct node_t *node);
void hashtable_dtor(struct hashtable_t *h);

#endif //__HASH_TABLE_H__