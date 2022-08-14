#ifndef __BUFFER__H__
#define __BUFFER__H__

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

struct buffer_t;

#define START_CAPACITY 128

struct buffer_t *make_buffer(struct buffer_t *buffer, unsigned num_of_strs);
char *get_text_buffer(const struct buffer_t *buffer);
unsigned get_buffer_size(const struct buffer_t *buffer);
void buffer_resize(struct buffer_t *buffer);
void buffer_dtor(struct buffer_t *buffer);
char *make_word(const char *str);

#endif