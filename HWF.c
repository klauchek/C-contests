#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define LAST_ULL_FIB 91

//! NOTE: LAST_ULL_FIB is defined by unsigned long long overflow
//! LAST_ULL_FIB will be 93 using f[1] = 1, f[2] = 1, f[3] = 2, f[4] = 3, f[5] = 5, f[6] = 8...
//! We use f[0] = 1, f[1] = 2, f[2] = 3, f[3] = 5, f[4] = 8... - convenient for converting to fibonacci system

unsigned long long fib_nums[LAST_ULL_FIB] = {0};
//--------------------------------------------------------
void play_game(int n);
unsigned long long fib(unsigned n);
unsigned count_fib(unsigned num);
unsigned closest_fib(unsigned num, unsigned *clst_fib_idx);
unsigned* fib_convert(unsigned num);
int next_turn(int total, int possible);
//--------------------------------------------------------


//! Function for simulating the game process
void play_game(int n)
{
    int possible = 0;
    int taken = 0;
    int left = 0;
    int player = 0;
    int counter = 0;
    possible = n - 1;
    left = n;
    while (left)
    {
        taken = next_turn(left, possible);
        left -= taken;
        possible = 2 * taken;
    
        ++counter;
        player = (++player) % 2;
        
        printf("Player: %d\n", player);
        printf("Number of move: %d\n", counter);
        printf("Taken on this move by player #%d: %d\n", player, taken);
        printf("Sticks left: %d\n", left);
        printf("Possible to take for next player: %d\n", possible);
        printf("====================================\n");
    }
    printf("Player #%d won!", player);
}

//! Function for determining how many sticks to take on the mth move
int next_turn(int total, int possible)
{
    unsigned* total_fib = NULL;
    unsigned length = 0;
    unsigned fib_idx = 0;
    unsigned to_take = 0;

    if (total <= possible)
        return total;
    
    total_fib = fib_convert(total);
    length = count_fib(total);

    for (int i = 0; i < length; ++i)
    {
        if ((total_fib[i] == 1) && (i != length - 1))
        {
            fib_idx = i;
            break;
        }
    }

    free(total_fib);

    if (fib_nums[fib_idx] == 0)
        fib(fib_idx);
    to_take = fib_nums[fib_idx];//HERE!

    if (possible >= to_take)
        return to_take;
    else return 1;   
}

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
unsigned* fib_convert(unsigned num)
{
    unsigned* arr = NULL;
    unsigned fib_idx = 0;
    unsigned clst_fib = 0;
    
    
    fib_idx = count_fib(num);//узнали индекс предыдущего числа f

    arr = (unsigned*) calloc(fib_idx, sizeof(unsigned));
    assert(arr);

    while(num)
    {
        clst_fib = closest_fib(num, &fib_idx);
        arr[fib_idx] = 1;

        if (clst_fib == num)
            break;

        num -= clst_fib;
    }

    return arr;
}


//! Function for defining the closest fibonacci number to num (from the left)
unsigned closest_fib(unsigned num, unsigned *clst_fib_idx)
{
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

int main()
{
    int res;
    int n;
    res = scanf("%d", &n);
    if (res != 1)
    {
        printf("%s\n", "Incorrect input");
        abort();
    }
    play_game(n);
    
    return 0;
}