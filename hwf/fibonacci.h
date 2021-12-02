#ifndef __FIB__H__
#define __FIB__H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define LAST_ULL_FIB 91

//! NOTE: LAST_ULL_FIB is defined by unsigned long long overflow
//! LAST_ULL_FIB will be 93 using f[1] = 1, f[2] = 1, f[3] = 2, f[4] = 3, f[5] = 5, f[6] = 8...
//! We use f[0] = 1, f[1] = 2, f[2] = 3, f[3] = 5, f[4] = 8... - convenient for converting to fibonacci system

unsigned long long fib(unsigned n);
unsigned count_fib(unsigned num);
unsigned closest_fib(unsigned num, unsigned *clst_fib_idx);
void fib_convert(unsigned num, unsigned *arr);


#endif //__FIB__H__