#include "hashtable.h"
#include "text_buffer/buffer.h"
#include <limits.h>

unsigned hash_function(const char *str) {
    unsigned hash = 5381;
    int c = 0;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

//..............................................................................

// Вход:
// Размер массива строк
// Строки, разделенные через перенос строки

// Выход:
// Количество найденных четверок


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

    hashtable = hashtable_ctor(128, hash_function);
    hashtable_fill(hashtable, buf);


    quads_num = quads_count(hashtable, buf);
    printf("Num of quads: %u\n", quads_num);
    hashtable_dtor(hashtable);
    buffer_dtor(buf);
    
    return 0;
}