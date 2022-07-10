#include "hashtable.h"

unsigned hash_function(const char *str) {
    unsigned hash = 5381;
    int c = 0;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

int main() {
    int res = 0;
    unsigned words_amount = 0;
    unsigned buf_len = 0;
    unsigned w_buf_len = 0;
    struct hashtable_t *hashtable;

    res = scanf("%d %d", &words_amount, &buf_len);
    if (res != 2) {
        printf("%s\n", "Wrong input of words amount and text buffer lenght");
        abort();
    }

    hashtable = hashtable_ctor(1, hash_function);
    hashtable_fill(hashtable, buf_len);

    res = scanf("%d", &w_buf_len);
    if (res != 1) {
        printf("%s\n", "Wrong input of words buffer lenght");
        abort();
    }

    freq_count(hashtable, w_buf_len);
    hashtable_dtor(hashtable);
    
    return 0;
}