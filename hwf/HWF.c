#include "fibonacci.h"

extern unsigned long long fib_nums[LAST_ULL_FIB];
//-------------------------------------
void start_game();
void play_game(int n);
int next_turn(int total, int possible);
void move_dump(int possible, int taken, int player, int counter, int left);
void check_inp(int checker, int input);
//-------------------------------------

void start_game()
{
    int checker = 0;
    int n = 0;
    printf("Enter start number of matches: \n");
    checker = scanf("%d", &n);
    check_inp(checker, n);

    play_game(n);
}

//! Function for simulating the game process
void play_game(int n)
{
    int taken = 0;
    int checker = 0;
    int possible = 0;
    int left = 0;
    int player = 0;
    int counter = 0;
    possible = n - 1;
    left = n;
    while (left)
    {   
        if (!player)
        {
            printf("Now you can take not more than %d matches. Your move: \n", possible);
            checker = scanf("%d", &taken);
            check_inp(checker, taken);

            while (taken > possible)
            {
                printf("Incorrect amount of matches. Try again: \n");
                checker = scanf("%d", &taken);
                check_inp(checker, taken);
            }
        }
        else
            taken = next_turn(left, possible);

        left -= taken;
        possible = 2 * taken;
    
        ++counter;
        player = (++player) % 2;

        move_dump(possible, taken, player, counter, left);
    }
    printf("Player #%d won!", player);
}

void move_dump(int possible, int taken, int player, int counter, int left)
{
    printf("Player: %d\n", player);
    printf("Number of move: %d\n", counter);
    printf("Taken on this move by player #%d: %d\n", player, taken);
    printf("Sticks left: %d\n", left);
    printf("Possible to take for next player: %d\n", possible);
    printf("====================================\n");
}

//! Function for determining how many sticks to take on the mth move
int next_turn(int total, int possible)
{
    unsigned total_fib[20] = {0};
    unsigned length = 0;
    unsigned fib_idx = 0;
    unsigned to_take = 0;

    if (total <= possible)
        return total;
    
    fib_convert(total, total_fib);
    length = count_fib(total);

    for (int i = 0; i < length; ++i)
    {
        if ((total_fib[i] == 1) && (i != length - 1))
        {
            fib_idx = i;
            break;
        }
    }

    if (fib_nums[fib_idx] == 0)
        fib(fib_idx);
    to_take = fib_nums[fib_idx];//HERE!

    if (possible >= to_take)
        return to_take;
    else return 1;   
}

void check_inp(int checker, int input)
{
    if (checker != 1 || input < 1)
    {
        printf("Incorrect input\n");
        abort();
    }

}

int main()
{
    start_game();

    return 0;
}