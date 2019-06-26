/*===-- mulodi4.c - Implement __mulodi4 -----------------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __mulodi4 for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */
#include <inttypes.h>

__mulodi4(int64_t a, int64_t b, int* overflow) {
    const int N = (int)(sizeof(int64_t) * 8);
    const int64_t MIN = (int64_t) 1 << (N-1);
    const int64_t MAX = ~MIN;
    *overflow = 0; 
    int64_t result = a * b;
    if (a == MIN)
    {
        if (b != 0 && b != 1)
	    *overflow = 1;
	return result;
    }
    if (b == MIN)
    {
        if (a != 0 && a != 1)
	    *overflow = 1;
        return result;
    }
    int64_t sa = a >> (N - 1);
    int64_t abs_a = (a ^ sa) - sa;
    int64_t sb = b >> (N - 1);
    int64_t abs_b = (b ^ sb) - sb;
    if (abs_a < 2 || abs_b < 2)
        return result;
    if (sa == sb)
    {
        if (abs_a > MAX / abs_b)
            *overflow = 1;
    }
    else
    {
        if (abs_a > MIN / -abs_b)
            *overflow = 1;
    }
    return result;
}