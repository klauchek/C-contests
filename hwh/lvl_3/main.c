#include "../hashtable/hashtable.h"
#include "strs_pair/strs_pair.h"
#include <limits.h>


//------------------------- READING INPUT ----------------------------//
struct buffer_t {
    char *strs_arr;
    unsigned size;
    unsigned capacity; 
};

void buffer_resize(struct buffer_t *buffer) {
    assert(buffer);

    buffer->capacity *= 2;
    buffer->strs_arr = realloc(buffer->strs_arr, buffer->capacity * sizeof(char));
    for(int i = buffer->size; i < buffer->capacity; ++i)
        buffer->strs_arr[i] = 0;
}

struct buffer_t *make_buffer(struct buffer_t *buffer, unsigned num_of_strs) {

    buffer = (struct buffer_t *)calloc(1, sizeof(struct buffer_t));
    assert(buffer);
    buffer->capacity = START_BUF_CAPACITY;

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

void buffer_dtor(struct buffer_t *buffer) {
    assert(buffer);

    free(buffer->strs_arr);
    free(buffer);
}

//------------------------- COUNTING QUADS ----------------------------//


void hashtable_fill(struct hashtable_t *h, struct buffer_t *buffer) {
    char c = 0;
    unsigned key = 0;
    char *word1 = NULL;
    char *word2 = NULL;
    
    unsigned buf_len = buffer->size;
    char *text_buffer = buffer->strs_arr;

    for (int i = 0; i < buf_len; ++i) {
        if(isalpha(text_buffer[i])) {
            for (int j = 0; j < buf_len; ++j) {
                if(isalpha(text_buffer[j])) {
                    if(i != j) {
                        struct pair_t *new_data = pair_ctor(text_buffer + i, text_buffer + j);
                        hashtable_insert(h, new_data); 
                    }
                    j += strlen(text_buffer + j);
                }
            }
            i += strlen(text_buffer + i);
        }
    }
}

unsigned get_answer(struct hashtable_t *h, struct node_t *cur) {

    assert(h);
    assert(cur);

    unsigned quads_in_bkt = 0;
    unsigned key = hashtable_get_key(h, cur->data);

    struct node_t *last = cur;
    unsigned counter = 1;
    while(last->next && hashtable_get_key(h, last->data) == key) {
        last = last->next;
        ++counter;
    }

    while(cur != last->next) {
        
        struct node_t * comp_node = cur->next;
        
        while(comp_node != last->next) {
            
            int res = compare(cur->data, comp_node->data);
            if(res) {
                ++quads_in_bkt;

                #ifdef PRINT_QUADS
                print_quad(cur->data, comp_node->data);
                #endif
            }
            comp_node = comp_node->next;
        }
        cur = cur->next;
    }
    return quads_in_bkt;
}


unsigned quads_count(struct hashtable_t *h) {
    assert(h);

    unsigned num_of_quads = 0;
    struct node_t **nodes_arr = hashtable_get_arr(h);
    unsigned hashtable_size = hashatble_get_size(h); 

    for(int i = 0; i < hashtable_size; ++i) {
        if(!nodes_arr[i])
            continue;
        struct node_t *cur = nodes_arr[i]->next;
        num_of_quads += get_answer(h, cur);
    }

    return num_of_quads;
}

//------------------------- MAIN ----------------------------//
int main() {
    int res = 0;
    unsigned strs_amount = 0;
    unsigned buf_len = 0;
    unsigned quads_num = 0;

    struct buffer_t *buf = NULL;
    struct hashtable_t *hashtable;

    res = scanf("%d", &strs_amount);
    if (res != 1) {
        printf("%s\n", "Wrong input of strings amount");
        abort();
    }

    buf = make_buffer(buf, strs_amount);

    hashtable = hashtable_ctor(START_HT_SIZE, HASH_THRESHOLD, hash_pair_function, pair_dtor);
    hashtable_fill(hashtable, buf);


    quads_num = quads_count(hashtable);
    printf("Num of quads: %u\n", quads_num);
    hashtable_dtor(hashtable);
    buffer_dtor(buf);
    
    return 0;
}