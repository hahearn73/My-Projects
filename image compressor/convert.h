/* convert.h
 * Assignment 4: arith
 * Harry Ahearn (hahear01), Adnan Jalal (ajalal03)
 * Date: 3/10/22
 * defines functions for converting from rgb color space to composite video
 */

#include "a2methods.h"
#include "pnm.h"
#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

struct a2_closure {
    A2Methods_UArray2 *arr;
    A2Methods_T methods;
    unsigned denom;
};

extern A2Methods_UArray2 rgb_to_v(Pnm_ppm img, A2Methods_mapfun *map,
    A2Methods_T methods);

extern void apply_rgb_to_v(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl);

float range_helper(float n, float bottom, float top);

#endif
