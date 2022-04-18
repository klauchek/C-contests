#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

//#define WORDLEN 100
#define H_SIZE 500000

struct node_t {
    char *data;
    struct node_t *next;
};

struct hashtable_t {
    struct node_t **arr;
    unsigned size;
};

//-------------------------
struct hashtable_t *hashtable_ctor(unsigned buf_len);
const char* make_buffer(unsigned buf_len);
const char* make_word(char *str);
void hashtable_fill(struct hashtable_t *h, unsigned buf_len);
struct node_t *add_node(const char *value);
void hashtable_insert(struct hashtable_t *h, unsigned key, const char *value);
int hashtable_find(struct hashtable_t *h, unsigned key, const char *str);
void freq_count(struct hashtable_t *h, unsigned w_buf_len);
void list_dtor(struct node_t *node);
void hashtable_dtor(struct hashtable_t *h);
unsigned hash(const char *str);
//----------------------------------------

struct hashtable_t *hashtable_ctor(unsigned buf_len) {
    struct hashtable_t *h = (struct hashtable_t *)calloc(1, sizeof(struct hashtable_t));
    assert(h);
    h->arr = (struct node_t **)calloc(H_SIZE, sizeof(struct node_t *));
    h->size = H_SIZE;

    return h;
}

const char* make_buffer(unsigned buf_len) {
    int res = 0;
    char *buffer = (char *)calloc(buf_len + 1, sizeof(char));
    assert(buffer);
    scanf("\n");
    for(int i = 0; i < buf_len; ++i) {
        assert(res = scanf("%c", buffer + i) == 1);
        if(buffer[i] == ' ')
            buffer[i] = '\0';
    }  
    buffer[buf_len] = '\0';

    return buffer;
}

const char* make_word(char *str) {
    int len = 0;
    char *word = NULL;
    assert(str);

    len = strlen(str);
    word = (char *)calloc(len + 1, sizeof(char));
    for(int i = 0; i < len; ++i)
        word[i] = str[i];
    word[len] = '\0';

    return word;
}

void hashtable_insert(struct hashtable_t *h, unsigned key, const char *value) {
    assert(h);
    assert(value);
    if(!h->arr[key])
        h->arr[key] = add_node(value);
    else {
        struct node_t *cur = h->arr[key];
        struct node_t *next = cur->next;
        while(next) {
            cur = next;
            next = cur->next;
        }
        cur->next = add_node(value);
    }  
}

void hashtable_fill(struct hashtable_t *h, unsigned buf_len) {
    char c = 0;
    unsigned key = 0;
    char *word = NULL;
    char *buf = NULL;

    buf = make_buffer(buf_len);
    
    for(int i = 0; i < buf_len; ++i)
    {
        if(isalpha(buf[i])) {
            word = make_word(buf + i);
            i += strlen(word);
            key = hash(word) % h->size;
            hashtable_insert(h, key, word);
            free(word);
        }
    }
}


struct node_t *add_node(const char *value) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    int len = strlen(value) + 1;
    char *str = (char *)calloc(len, sizeof(char));
    memmove(str, value, len);
    new_node->next = NULL;
    new_node->data = str;

    return new_node;
}


int hashtable_find(struct hashtable_t *h, unsigned key, const char *str) {
    unsigned freq = 0;
    assert(h);
    assert(str);

    if(!h->arr[key])
        return 0;
    else {
        struct node_t *cur = h->arr[key];
        struct node_t *next = cur->next;
        while(next) {
            if(strcmp(cur->data, str) == 0)
                ++freq;
            cur = next;
            next = cur->next;
        }
        if(strcmp(cur->data, str) == 0)
                ++freq;
        else
            return 0;
    }
    return freq;
}


void freq_count(struct hashtable_t *h, unsigned w_buf_len) {
    char c = 0;
    unsigned key = 0;
    unsigned freq = 0;
    char *word = NULL;
    char *words_buf = NULL;
    assert(h);

    words_buf = make_buffer(w_buf_len);
    for(int i = 0; i < w_buf_len; ++i)
    {
        if(isalpha(words_buf[i])) {
            word = make_word(words_buf + i);
            i += strlen(word);
            key = hash(word) % h->size;
            freq = hashtable_find(h, key, word);
            printf("%d ", freq); 
            free(word);
        }
    }
}

void list_dtor(struct node_t *node) {
    struct node_t *cur = node;
    struct node_t *prev = NULL;
    while(cur->next) {
        prev = cur;
        cur = cur->next;

        free(prev->data);
        free(prev);
    }
    free(cur->data);
    free(cur);
}

void hashtable_dtor(struct hashtable_t *h) {
    assert(h);
    for(int i = 0; i < h->size; ++i) {
        if(h->arr[i] == NULL)
            continue;
        else
            list_dtor(h->arr[i]);
    }
    free(h->arr);
    free(h);
}

unsigned hash(const char *str) {
    unsigned hash = 5381;
    int c = 0;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}


int main() {
    unsigned words_amount = 0;
    unsigned buf_len = 0;
    unsigned w_buf_len = 0;
    struct hashtable_t *hashtable;

    assert(scanf("%d %d", &words_amount, &buf_len) == 2);
    hashtable = hashtable_ctor(buf_len);
    
    hashtable_fill(hashtable, buf_len);
    assert(scanf("%d", &w_buf_len) == 1);

    freq_count(hashtable, w_buf_len);
    hashtable_dtor(hashtable);
    
    return 0;
}
