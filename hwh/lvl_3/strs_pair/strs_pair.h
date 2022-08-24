#ifndef __PAIR_H__
#define __PAIR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct pair_t;

struct pair_t *pair_ctor(char *str_1, char *str_2);
int compare(void *first, void *second);
void pair_dtor(void *data);
char *get_concat_str(char *first, char *second);
void print_quad(void *first, void *second);
unsigned hash_2sts_function(char *str_1, char *str_2);
unsigned hash_pair_function(void *strs_pair);

#endif //__PAIR_H__