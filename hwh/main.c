#include "hwh.h"

int main() {
    unsigned words_amount = 0;
    unsigned buf_len = 0;
    unsigned w_buf_len = 0;
    struct hashtable_t *hashtable;

    assert(scanf("%d %d", &words_amount, &buf_len) == 2);
    hashtable = hashtable_ctor(H_SIZE);
    
    hashtable_fill(hashtable, buf_len);
    assert(scanf("%d", &w_buf_len) == 1);

    freq_count(hashtable, w_buf_len);
    hashtable_dtor(hashtable);
    
    return 0;
}