#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "text_buffer/buffer.h"

typedef unsigned (*hash_func)(const char *);

struct data_t;
struct answer_t;
struct node_t;
struct hashtable_t;

struct hashtable_t *hashtable_ctor(unsigned sz, hash_func hashFunc);
char *get_concat_str(struct hashtable_t *h, unsigned idx1, unsigned idx2, char *text_buffer);
int compare (int idx_1, int idx_2, int idx_3, int idx_4, const char *buf);
struct answer_t *get_answer(struct hashtable_t *h, struct node_t *cur, char *buffer, unsigned *quads_in_bkt);
void hashtable_fill(struct hashtable_t *h, struct buffer_t *buffer);
struct node_t *add_node(struct data_t *new_data);
void hashtable_insert(struct hashtable_t *h, struct data_t *new_data, char *text_buffer);
//int hashtable_find(struct hashtable_t *h, unsigned key, const char *str);
void hashtable_resize(struct hashtable_t *h, char *text_buffer);
int quads_count(struct hashtable_t *h, struct buffer_t *buffer);
void list_dtor(struct node_t *node);
void hashtable_dtor(struct hashtable_t *h);
void dump_table (struct hashtable_t *table);

#endif //__HASH_TABLE_H__