#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


unsigned long long fib_nums[100] = {0};
//--------------------------------------------------------
void play_game(int n);
unsigned fib(unsigned n);
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
    to_take = fib(fib_idx);

    if (possible >= to_take)
        return to_take;
    else return 1;   
}

//! Function for finding fibonacci number by its index n
unsigned fib(unsigned n)
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
    unsigned tmp = 0;
    int counter = 1;

    if (num < 3)
        return num;

    while (tmp <= num)
    {
        ++counter;
        tmp = fib(counter);
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