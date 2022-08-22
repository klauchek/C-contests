#include "strs_pair.h"

struct pair_t {
    char *str_1;
    char *str_2;
};

struct answer_t {
    struct pair_t first_pair;
    struct pair_t second_pair;
};

struct pair_t *pair_ctor(char *str1, char *str2) {

    struct pair_t *new_pair = (struct pair_t *)calloc(1, sizeof(struct pair_t));
    assert(new_pair);
    new_pair->str_1 = str1;
    new_pair->str_2 = str2;
    
    return new_pair;
}

void pair_dtor(void *data) {
    struct pair_t *pair = (struct pair_t *)data;
    free(pair);
}

int compare(void *first, void *second) {

    struct pair_t *pair_1;
    struct pair_t *pair_2;

    int flag_1 = 0;
    int flag_2 = 0;

    pair_1 = (struct pair_t *)first;
    pair_2 = (struct pair_t *)second;

    if(strlen(pair_1->str_1) + strlen(pair_1->str_2) != strlen(pair_2->str_1) + strlen(pair_2->str_2))
        return 0;

    char *ptr_1 = pair_1->str_1;
    char *ptr_2 = pair_2->str_1;

    while (*ptr_1) {

        if(*ptr_1 != *ptr_2)
            return 0;
        
        *ptr_1++;

        if(!*ptr_1 && !flag_1) {
            ptr_1 = pair_1->str_2;
            flag_1 = 1;
        }

        *ptr_2++;

        if(!*ptr_2 && !flag_2) {
            ptr_2 = pair_2->str_2;
            flag_2 = 1;
        }
    }

    return 1;
}

char *get_concat_str(char *first, char *second) {

    assert(first);
    assert(second);

    char *res = (char *)calloc(strlen(first) + strlen(second) + 1, sizeof(char));
    assert(res);
    strcat(res, first);
    strcat(res, second);
    
    return res;
}

//--- hash function adaptation ------------

unsigned hash_2sts_function(char *str_1, char *str_2) {

    unsigned hash = 5381;
    int c = 0;

    while(c = *str_1++)
        hash = ((hash << 5) + hash) + c;

    while(c = *str_2++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned hash_pair_function(void *strs_pair) {

    struct pair_t *pair = (struct pair_t *)strs_pair;

    return hash_2sts_function(pair->str_1, pair->str_2);
}


// int main() {

//     char *str_1 = "abr";
//     char *str_2 = "abrcd";
//     char *str_3 = "cdef";
//     char *str_4 = "ef";

//     struct pair_t *pair_1 = pair_ctor(str_1, str_3); //abr cdef
//     struct pair_t *pair_2 = pair_ctor(str_2, str_4); //abrcd el


//     int res = compare(pair_1, pair_2);
//     printf("%d\n", res);

//     return 0;
// }