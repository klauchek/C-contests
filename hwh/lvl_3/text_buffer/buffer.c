#include "buffer.h"

struct buffer_t {
    char *strs_arr;
    unsigned size;
    unsigned capacity; 
};

struct buffer_t *make_buffer(struct buffer_t *buffer, unsigned num_of_strs) {

    buffer = (struct buffer_t *)calloc(1, sizeof(struct buffer_t));
    assert(buffer);
    buffer->capacity = START_CAPACITY;

    buffer->strs_arr = (char *)calloc(buffer->capacity, sizeof(char));
    assert(buffer->strs_arr);

    unsigned counter = 0; 

    char sym = getchar();
    
    while((sym = getchar()) != EOF) {
    
        if(buffer->size == buffer->capacity / 2)
            buffer_resize(buffer);
        if (sym == '\n')
            buffer->strs_arr[buffer->size] = '\0';
        else    
            buffer->strs_arr[buffer->size] = sym;
        ++buffer->size;
    }
    ++counter;
    
    return buffer;
}

char *get_text_buffer(const struct buffer_t *buffer) {
    assert(buffer);
    return buffer->strs_arr;
}

unsigned get_buffer_size(const struct buffer_t *buffer) {
    assert(buffer);
    return buffer->size;
}

char *make_word(const char *str) {
    int len = 0;
    char *word = NULL;
    assert(str);

    len = strlen(str);
    word = (char *)calloc(len + 1, sizeof(char));
    assert(word);
    memmove(word, str, len);

    return word;
}

void buffer_resize(struct buffer_t *buffer) {
    assert(buffer);

    buffer->capacity *= 2;
    buffer->strs_arr = realloc(buffer->strs_arr, buffer->capacity * sizeof(char));
    for(int i = buffer->size; i < buffer->capacity; ++i)
        buffer->strs_arr[i] = 0;
}

void buffer_dtor(struct buffer_t *buffer) {
    assert(buffer);

    free(buffer->strs_arr);
    free(buffer);
}
