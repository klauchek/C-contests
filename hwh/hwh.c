#include "hwh.h"
//cписок частот встретившихся в файле слов
//На стандартном вводе: количество ожидаемых ответов, длина (текста в символах),
//текст, разделённый пробелами, длина (списка слов в символах), список искомых слов,
//разделённый пробелами

//На стандартный вывод: сколько раз слово из списка слов встретилось в тексте

//сами строки!!!1
struct node_t {
    char *data;
    struct node_t *next;
}

struct hashtable_t {
    struct node_t **arr; //массив указателей на ноды
    unsigned size;
}


//finished
hashtable_t *hashtable_ctor(unsigned h_size) {
    struct hashtable_t *h = (struct hashtable_t *)calloc(1, sizeof(struct hashtable_t));
    assert(h);
    h->arr = (struct node_t **)calloc(h_size, sizeof(struct node_t *));
    h->size = h_size;

    return h;
}


//мы не знаем изначально количество слов, которые к нам поступили,
//только длину массива с этими словами

//create str
const char* make_words(unsigned buf_len) {
    unsigned char *word_buf = (char *)calloc(buf_len, sizeof(char))
}

//fill with strs
void hashtable_fill(hashtable_t *h, buf_len) {
    char c = 0;

    for(int i = 0; i < buf_len; ++i)//с 1 ??
    {
        c = getchar();
        if(isalpha(c)) {

        }
    }
}

//finished
//создать сущность типа node, который элемент хеш-таблицы, из имеющейся строки
node_t *add_node(const char *str) {
    struct node_t *new_node = (struct node_t *)calloc(1, sizeof(struct node_t));
    int len = strlen(value) + 1; //тк еще \0
    char *str = (char *)calloc(len, sizeof(char));
    memmove(str, value, len);
    new_node->next = NULL;
    new_node->data = str;

    return new_node;
}

//finished
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

const char *hashtable_find(struct hashtable_t *h, unsigned key) {

}


void hashtable_dtor(struct hashtable_t *h) {
    for (unsigned i = 0; i < h->size; ++i) {

    }
}

unsigned hash(const char *str) {
    unsigned hash = 5381;
    int c = 0;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}
