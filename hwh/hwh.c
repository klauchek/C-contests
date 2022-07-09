#include "hashtable.h"

struct node_t {
    char *data;
    struct node_t *next;
};

struct hashtable_t {
    struct node_t **arr;
    struct node_t *head;
    unsigned size;
    unsigned inserts;

};

// static void print_list (struct node_t *head, int key, int size) {

//     struct node_t *node = head->next;

//     while (node && hash(node->data) % size == key) {

//         printf ("\t%s\n", node->data);
//         node = node->next;
//     }
// }

// static void print_table (struct hashtable_t *table) {
    
//     struct node_t **arr = table->arr;

//     for (int i = 0; i < table->size; ++i) {
        
//         if (arr[i]) {
            
//             printf ("\t\t###Key: %d\n", i);
//             print_list (table->arr[i], i, table->size);
//         }
//     }
// }

//---------------------------------------------------------
struct hashtable_t *hashtable_ctor(unsigned sz) {
    struct hashtable_t *h = (struct hashtable_t *)calloc(1, sizeof(struct hashtable_t));
    assert(h);
    h->head = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(h->head);
    h->arr = (struct node_t **)calloc(sz, sizeof(struct node_t *));
    assert(h->arr);
    h->size = sz;

    return h;
}

char* make_buffer(unsigned buf_len) {
    int res = 0;
    char *buffer = (char *)calloc(buf_len + 1, sizeof(char));
    assert(buffer);
    scanf("\n");
    for(int i = 0; i < buf_len; ++i) {
        res = scanf("%c", buffer + i);
        assert(res == 1);
        if(buffer[i] == ' ')
            buffer[i] = '\0';
    }  
    buffer[buf_len] = '\0';
    return buffer;
}

char* make_word(const char *str) {
    int len = 0;
    char *word = NULL;
    assert(str);

    len = strlen(str);
    word = (char *)calloc(len + 1, sizeof(char));
    assert(word);
    for(int i = 0; i < len; ++i)
        word[i] = str[i];
    word[len] = '\0';

    return word;
}

struct node_t *add_node(const char *value) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(new_node);
    int len = strlen(value) + 1;
    char *str = (char *)calloc(len, sizeof(char));
    assert(str);
    memmove(str, value, len);
    new_node->data = str;
    new_node->next = NULL;

    return new_node;
}



void hashtable_insert(struct hashtable_t *h, unsigned key, const char *value) {
    assert(h);
    assert(value);

    if (((double)h->inserts / h->size) >= 0.75) //double
       hashtable_resize(h);

    struct node_t *new_node = add_node(value);

    if(!h->arr[key]) {
        new_node->next = h->head->next;
        h->head->next = new_node;
        if(new_node->next) {
            int next_key = hash(new_node->next->data) % h->size;
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
    int new_key = 0;
    struct node_t *cur = h->head->next;
    struct node_t *last = h->head;
    struct node_t *next = NULL;

    free(arr);

    h->size *= 2;

    h->arr = (struct node_t **)calloc(h->size, sizeof(struct node_t *));

    while(cur) {
        next = cur->next;
        new_key = hash(cur->data) % h->size;

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
    free(buf);
}


// ok
int hashtable_find(struct hashtable_t *h, unsigned key, const char *str) {
    unsigned freq = 0;
    assert(h);
    assert(str);
    
    if(!h->arr[key])
        return 0;
    else {
        struct node_t *cur = h->arr[key];
        cur = cur->next;

        while(cur && (hash(cur->data) % h->size) == key) {
            if(strcmp(cur->data, str) == 0)
                ++freq;
            cur = cur->next;
        }
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
    free(words_buf);
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
    list_dtor(h->head);
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
