#include "hashtable.h"

struct data_t {
    unsigned idx_1;
    unsigned idx_2;
};

struct answer_t {
    struct data_t first_pair;
    struct data_t second_pair;
};

struct node_t {
    struct data_t data;
    struct node_t *next;
};

struct hashtable_t {
    struct node_t **arr;
    struct node_t *head;
    unsigned size;
    unsigned inserts;
    hash_func hash;
};

struct hashtable_t *hashtable_ctor(unsigned sz, hash_func hashFunc) {
    struct hashtable_t *h = (struct hashtable_t *)calloc(1, sizeof(struct hashtable_t));
    assert(h);
    h->head = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(h->head);
    h->arr = (struct node_t **)calloc(sz, sizeof(struct node_t *));
    assert(h->arr);
    h->size = sz;
    h->hash = hashFunc;

    return h;
}


char *get_concat_str(struct hashtable_t *h, unsigned idx1, unsigned idx2, char *text_buffer) {
    assert(h);
    assert(text_buffer);

    unsigned key = 0;

    char *word1 = make_word(text_buffer + idx1);
    char *word2 = make_word(text_buffer + idx2);
    char *res = (char *)calloc(strlen(word1) + strlen(word2) + 1, sizeof(char));
    assert(res);
    strcat(res, word1);
    strcat(res, word2);

    free(word1);
    free(word2);

    return res;
}


struct node_t *add_node(struct data_t *new_data) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    assert(new_node);
    new_node->data.idx_1 = new_data->idx_1;
    new_node->data.idx_2 = new_data->idx_2;
    new_node->next = NULL;

    return new_node;
}


void hashtable_insert(struct hashtable_t *h, struct data_t *new_data, char *text_buffer) {
    assert(h);
    assert(new_data);

    if (((double)h->inserts / h->size) >= 0.75)
       hashtable_resize(h, text_buffer);

    char *new_str = get_concat_str(h, new_data->idx_1, new_data->idx_2, text_buffer);
    unsigned key = h->hash(new_str) % h->size;
    free(new_str);
    struct node_t *new_node = add_node(new_data);

    if(!h->arr[key]) {
        new_node->next = h->head->next;
        h->head->next = new_node;
        if(new_node->next) {
            char *next_str = get_concat_str(h, new_node->next->data.idx_1, new_node->next->data.idx_2, text_buffer);
            unsigned next_key = h->hash(next_str) % h->size;
            free(next_str);
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

void hashtable_resize(struct hashtable_t *h, char *text_buffer) {
    assert(h);

    struct node_t **arr = h->arr;
    struct node_t *cur = h->head->next;
    struct node_t *last = h->head;
    struct node_t *next = NULL;

    free(arr);

    h->size *= 2;

    h->arr = (struct node_t **)calloc(h->size, sizeof(struct node_t *));

    while(cur) {
        next = cur->next;
        char *new_str = get_concat_str(h, cur->data.idx_1, cur->data.idx_2, text_buffer);
        unsigned new_key = h->hash(new_str) % h->size;

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


void hashtable_fill(struct hashtable_t *h, struct buffer_t *buffer) {
    char c = 0;
    unsigned key = 0;
    char *word1 = NULL;
    char *word2 = NULL;
    
    unsigned buf_len = get_buffer_size(buffer);
    char *text_buffer = get_text_buffer(buffer);

    for (int i = 0; i < buf_len; ++i) {
        if(isalpha(text_buffer[i])) {
            word1 = make_word(text_buffer + i);
            for (int j = 0; j < buf_len; ++j) {
                if(isalpha(text_buffer[j])) {
                    word2 = make_word(text_buffer + j);
                    if(i != j) {
                        struct data_t *new_data = (struct data_t *)calloc(1, sizeof(struct data_t));
                        assert(new_data);
                        new_data->idx_1 = i;
                        new_data->idx_2 = j;
                        hashtable_insert(h, new_data, text_buffer);
                        free(new_data); 
                    }
                    j += strlen(word2);
                    free(word2);
                }
            }
            i += strlen(word1);
            free(word1);
        }
    }
}

//сравнение на равенство двух строк, полученных конкатенацией
int compare (int idx_1, int idx_2, int idx_3, int idx_4, const char *buf) {

    if ( (strlen (buf + idx_1) + strlen (buf + idx_2)) != (strlen (buf + idx_3) + strlen (buf + idx_4))) {
        return 0;
    }

    unsigned word_idx_1 = idx_1;
    unsigned word_idx_2 = idx_3;

    unsigned counter = 0;
    unsigned total_size = strlen (buf + idx_1) + strlen (buf + idx_2);

    while (counter != total_size) {

        if (buf[word_idx_1] != buf[word_idx_2]) {
            return 0;
        }
        ++word_idx_1;
        ++word_idx_2;

        if (buf[word_idx_1] == '\0')
            word_idx_1 = idx_2;

        if (buf[word_idx_2] == '\0')
            word_idx_2 = idx_4;

        ++counter;   
    }

    return 1;
}

//поиск равных в одном бакете
struct answer_t *get_answer(struct hashtable_t *h, struct node_t *cur, char *text_buffer, unsigned *quads_in_bkt) {

    //ищем последний элемент в данном бакете
    char *cur_str = get_concat_str(h, cur->data.idx_1, cur->data.idx_2, text_buffer);
    unsigned key = h->hash(cur_str) % h->size;

    struct node_t *last = cur;
    unsigned counter = 1;
    while(last->next && (h->hash(cur_str) % h->size) == key) {
        last = last->next;
        free(cur_str);
        cur_str = get_concat_str(h, last->data.idx_1, last->data.idx_2, text_buffer);
        ++counter;
    }
    free(cur_str);

    struct answer_t *quads = (struct answer_t *)calloc((counter * (counter - 1)) / 2, sizeof(struct answer_t));

    //проход по бакету с поиском равных
    while(cur != last->next) {
        
        struct node_t * comp_node = cur->next;
        
        while(comp_node != last->next) {
            
            int res = compare(cur->data.idx_1, cur->data.idx_2, comp_node->data.idx_1, comp_node->data.idx_2, text_buffer);
            if(res) {
                struct answer_t quad;
                quad.first_pair = cur->data;
                quad.second_pair = comp_node->data;
                quads[*quads_in_bkt] = quad;
                ++*quads_in_bkt;
            }
            comp_node = comp_node->next;
        }
        cur = cur->next;
    }
    return quads;
}


//итерируемся по всей таблице и по каждому бакету
int quads_count(struct hashtable_t *h, struct buffer_t *buffer) {
    assert(h);
    assert(buffer);
    int counter = 0;
    unsigned quads_in_bkt = 0;//in one bucket

    char *text_buffer = get_text_buffer(buffer);

    //идем по таблице и заходим в каждый бакет
    for(int i = 0; i < h->size; ++i) {
        if(!h->arr[i])
            continue;
        struct node_t *cur = h->arr[i]->next;
        struct answer_t *res_from_bkt = get_answer(h, cur, text_buffer, &quads_in_bkt);
        for(int i = 0; i < quads_in_bkt; ++i) {
            char *str1 = make_word(text_buffer + res_from_bkt[i].first_pair.idx_1);
            char *str2 = make_word(text_buffer + res_from_bkt[i].first_pair.idx_2);
            char *str3 = make_word(text_buffer + res_from_bkt[i].second_pair.idx_1);
            char *str4 = make_word(text_buffer + res_from_bkt[i].second_pair.idx_2);

            printf("%s %s %s %s \n", str1, str2, str3, str4);

            free(str1);
            free(str2);
            free(str3);
            free(str4);
        }
        counter += quads_in_bkt;
        quads_in_bkt = 0;

        free(res_from_bkt);
    }

    return counter;
}


void list_dtor(struct node_t *node) {
    struct node_t *cur = node;
    struct node_t *prev = NULL;
    while(cur->next) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(cur);
}

void hashtable_dtor(struct hashtable_t *h) {
    assert(h);
    list_dtor(h->head);
    free(h->arr);
    free(h);
}

