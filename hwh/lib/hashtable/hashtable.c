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

static struct node_t *add_node(void *new_data) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(new_node);
    new_node->data = new_data;
    new_node->next = NULL;

    return new_node;
}

static void hashtable_resize(struct hashtable_t *h) {
    assert(h);

    struct node_t **arr = h->arr;
    unsigned new_key = 0;
    struct node_t *cur = h->head->next;
    struct node_t *last = h->head;
    struct node_t *next = NULL;

    h->size *= 2;
    h->arr = realloc(h->arr, h->size * sizeof(struct node_t *));
    memset(h->arr, 0, h->size * sizeof(struct node_t *));

    while(cur) {
        next = cur->next;
        new_key = hashtable_get_key(h, cur->data);

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

void hashtable_insert(struct hashtable_t *h, void *new_data) {
    assert(h);

    if (((double)h->inserts / h->size) >= h->threshold)
       hashtable_resize(h);

    unsigned key = hashtable_get_key(h, new_data);
    struct node_t *new_node = add_node(new_data);

    if(!h->arr[key]) {
        new_node->next = h->head->next;
        h->head->next = new_node;
        if(new_node->next) {
            unsigned next_key = hashtable_get_key(h, new_node->next->data);;
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

struct node_t *hashtable_find(struct hashtable_t *h, unsigned key) {
    assert(h);

    if(!h->arr[key])
        return 0;
    else
        return h->arr[key]->next;
}

int hashtable_count(struct hashtable_t *h, void *data, int (*data_comp)(void *, void *)) {
    assert(h);
    
    unsigned freq = 0;
    unsigned key = hashtable_get_key(h, data);

    if(!h->arr[key])
        return 0;
    else {
        struct node_t *cur = h->arr[key]->next;

        while(cur && hashtable_get_key(h, data) == key) {
            if(data_comp(cur->data, data)) {
                ++freq;
            }
            cur = cur->next;
        }
    }
    return freq;
}

static void list_dtor(struct hashtable_t *h) {
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

unsigned hashatble_get_size(const struct hashtable_t *h) {
    assert(h);
    return h->size;
}

unsigned hashtable_get_key(struct hashtable_t *h, void *data) {
    assert(h);
    return h->hash(data) % h->size;
}
