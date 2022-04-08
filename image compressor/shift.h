/* shift.h
 * Assignment 4: arith
 * Harry Ahearn (hahear01), Adnan Jalal (ajalal03)
 * Date: 3/10/22
 * contains functions for shifting uint64_t's left and right
 */

#define MAX_WIDTH 64

/* shift_leftu
 * returns a uin64_t that is equivalent to n << width assuming width is valid
 * according to MAX_WIDTH, otherwise returns 0
 */
static inline uint64_t shift_leftu(uint64_t n, unsigned width)
{
    assert(width <= MAX_WIDTH);
    return (n << width);
}

/* shift_rightu
 * returns a uin64_t that is equivalent to n >> width assuming width is valid
 * according to MAX_WIDTH, otherwise returns 0
 */
static inline uint64_t shift_rightu(uint64_t n, unsigned width)
{
    assert(width <= MAX_WIDTH);
    return (n >> width);
}
