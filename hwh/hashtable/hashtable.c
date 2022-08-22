#include "hashtable.h"

struct hashtable_t {
    struct node_t **arr;
    struct node_t *head;
    unsigned size;
    unsigned inserts;
    double threshold;

    hash_func hash;
    data_dtor data_dtor;
};

struct hashtable_t *hashtable_ctor(unsigned sz, double threshold_coef, hash_func hashFunc, data_dtor dataDtor) {
    struct hashtable_t *h = (struct hashtable_t *)calloc(1, sizeof(struct hashtable_t));
    assert(h);
    h->head = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(h->head);
    h->arr = (struct node_t **)calloc(sz, sizeof(struct node_t *));
    assert(h->arr);
    h->size = sz;
    h->threshold = threshold_coef;

    h->hash = hashFunc;
    h->data_dtor = dataDtor;

    return h;
}

struct node_t *add_node(void *new_data) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(new_node);
    new_node->data = new_data;
    new_node->next = NULL;

    return new_node;
}


void hashtable_insert(struct hashtable_t *h, void *new_data) {
    assert(h);

    if (((double)h->inserts / h->size) >= h->threshold)
       hashtable_resize(h);

    unsigned key = h->hash(new_data) % h->size;
    struct node_t *new_node = add_node(new_data);

    if(!h->arr[key]) {
        new_node->next = h->head->next;
        h->head->next = new_node;
        if(new_node->next) {
            unsigned next_key = h->hash(new_node->next->data) % h->size;
            h->arr[next_key] = new_node;
        }
        h->arr[key] = h->head;
    }
    else {
        new_node->next = h->arr[key]->next;
        h->arr[key]->next = new_node;
    }
    ++h->inserts;
}


void hashtable_resize(struct hashtable_t *h) {
    assert(h);

    struct node_t **arr = h->arr;
    unsigned new_key = 0;
    struct node_t *cur = h->head->next;
    struct node_t *last = h->head;
    struct node_t *next = NULL;

    free(arr);

    h->size *= 2;

    h->arr = (struct node_t **)calloc(h->size, sizeof(struct node_t *));

    while(cur) {
        next = cur->next;
        new_key = h->hash(cur->data) % h->size;

        if(!h->arr[new_key]) {
            last->next = cur;
            h->arr[new_key] = last;
            last = cur;
            last->next = NULL;
        }
        else {
            cur->next = h->arr[new_key]->next;
            h->arr[new_key]->next = cur;

        }
        cur = next;
    }
}

unsigned hashatble_get_size(struct hashtable_t *h) {
    assert(h);
    return h->size;
}

unsigned hashtable_get_key(struct hashtable_t *h, struct node_t *node) {
    assert(h);
    return h->hash(node->data) % h->size;
}

struct node_t **hashtable_get_arr(struct hashtable_t *h) {
    assert(h);
    return(h->arr);
}


void list_dtor(struct hashtable_t *h) {
    struct node_t *cur = h->head;
    struct node_t *prev = NULL;
    while(cur->next) {
        prev = cur;
        cur = cur->next;

        h->data_dtor(prev->data);
        free(prev);
    }
    h->data_dtor(cur->data);
    free(cur);
}

void hashtable_dtor(struct hashtable_t *h) {
    assert(h);
    list_dtor(h);
    free(h->arr);
    free(h);
}