#include "hashtable.h"
#include <stdio.h>

#define START_HT_SIZE 128
#define HASH_THRESHOLD 0.75

unsigned hash_function(void *data) {
    unsigned hash = 5381;
    int c = 0;

    char *str = (char *)data;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

int compare(void *data_1, void *data_2) {

    char *str_1 = (char *)data_1;
    char *str_2 = (char *)data_2;

    if(strcmp(str_1, str_2) == 0)
        return 1;
    return 0;
}

void str_dtor(void *data) {/* do nothing */}

//------------------------- READING INPUT ----------------------------//

char* make_buffer(unsigned buf_len) {

    char *buffer = (char *)calloc(buf_len + 1, sizeof(char));
    assert(buffer);

    char sym = getchar();

    for(int i = 0; i < buf_len; ++i) {

        sym = getchar();
        if (sym == ' ' || sym == '\n')
            buffer[i] = '\0';
        else    
            buffer[i] = sym;
    }
    return buffer;
}

//------------------------- COUNTING FREQUENCY OF WORDS ----------------------------//

void hashtable_fill(struct hashtable_t *h, char *buf, unsigned buf_len) {
    assert(h);
    assert(buf);

    for(int i = 0; i < buf_len; ++i)
    {
        if(isalpha(buf[i])) {
            hashtable_insert(h, buf + i);
            i += strlen(buf + i);
        }
    }
}
void freq_count(struct hashtable_t *h, unsigned w_buf_len) {
    char c = 0;
    unsigned key = 0;
    unsigned freq = 0;
    char *words_buf = NULL;
    assert(h);

    words_buf = make_buffer(w_buf_len);
    for(int i = 0; i < w_buf_len; ++i)
    {
        if(isalpha(words_buf[i])) {
            freq = hashtable_count(h, words_buf + i, compare);
            i += strlen(words_buf + i);
            printf("%d ", freq);
        }
    }
    free(words_buf);
}

//------------------------- MAIN ----------------------------//

int main() {
    int res = 0;
    unsigned words_amount = 0;
    unsigned buf_len = 0;
    unsigned w_buf_len = 0;
    struct hashtable_t *hashtable;
    char* buffer;

    res = scanf("%d %d", &words_amount, &buf_len);
    if (res != 2) {
        printf("%s\n", "Wrong input of words amount and text buffer lenght");
        abort();
    }

    hashtable = hashtable_ctor(START_HT_SIZE, HASH_THRESHOLD, hash_function, str_dtor);
    buffer = make_buffer(buf_len);
    hashtable_fill(hashtable, buffer, buf_len);

    res = scanf("%d", &w_buf_len);
    if (res != 1) {
        printf("%s\n", "Wrong input of words buffer lenght");
        abort();
    }

    freq_count(hashtable, w_buf_len);
    hashtable_dtor(hashtable);
    free(buffer);
    
    return 0;
}