#include "hashtable.h"
#include "text_buffer/buffer.h"


unsigned hash_function(const char *str) {
    unsigned hash = 5381;
    int c = 0;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

int pow_mod (unsigned n, unsigned k, unsigned m)
{
  int mult, prod;
  if (n == 0 || n == 1 || k == 1)
    return n;
  if (k == 0)
    return 1;
  mult = n;
  prod = 1;
  while (k > 0)
  {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k = k / 2;
  }
  return prod;
}

int Hash_of_Int (int number)
{
  int p = 2909;
  int a = 211;
  int b = 521;
  int m = 2137;

  int h_int = 0;

  h_int = ((a*number + b) % p) % m;

  return h_int;

}
unsigned Hash_of_Char (const char* string)
{
    int len = strlen(string);
    int h_c = 0;
    int r = 241;
    int p = 919;
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
    sum += (string[i] * pow_mod (r, len - i, p)) % p;
    }
    sum = sum % p;

    h_c = Hash_of_Int (sum);

    return h_c;
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

    hashtable = hashtable_ctor(128, Hash_of_Char);
    hashtable_fill(hashtable, buf);



    quads_num = quads_count(hashtable, buf);
    printf("Num of quads: %d\n", quads_num);
    hashtable_dtor(hashtable);
    buffer_dtor(buf);
    
    return 0;
}