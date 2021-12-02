#include "fibonacci.h"

unsigned long long fib_nums[LAST_ULL_FIB] = {0};

//! Function for finding fibonacci number by its index n
unsigned long long fib(unsigned n)
{
    fib_nums[0] = 1; fib_nums[1] = 2;

    for (int i = 2; i <= n; ++i)
    {
       fib_nums[i] = fib_nums[i - 1] + fib_nums[i - 2];
    }
    return fib_nums[n];
}

//! Function for converting from decimal system to Fibonacci system
void fib_convert(unsigned num, unsigned *arr)
{
    assert(arr);
    unsigned fib_idx = 0;
    unsigned clst_fib = 0;

    fib_idx = count_fib(num);//узнали индекс предыдущего числа f

    while(num)
    {
        clst_fib = closest_fib(num, &fib_idx);
        arr[fib_idx] = 1;

        if (clst_fib == num)
            break;

        num -= clst_fib;
    }
}


//! Function for defining the closest fibonacci number to num (from the left)
unsigned closest_fib(unsigned num, unsigned *clst_fib_idx)
{
    assert(clst_fib_idx);
    unsigned i = 1;
    *clst_fib_idx = 0;
    if (num == 0 || num == 1)
        return num;

    if (num == 2)
    {
        *clst_fib_idx = 1;
        return 2;
    }

    while(fib_nums[i] <= num)
    {
        ++i;
        ++(*clst_fib_idx);
    }

    return fib_nums[i - 1];
}

//! Function for defining previous fibonacci number index
unsigned count_fib(unsigned num)
{
    int counter = 1;

    if (num < 3)
        return num;

    while (fib_nums[counter] <= num)
    {
        ++counter;
        if (fib_nums[counter] == 0)
            fib(counter);     
    }
    
    return counter;
}
