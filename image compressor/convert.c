/* convert.c
 * Assignment 4: arith
 * Harry Ahearn (hahear01), Adnan Jalal (ajalal03)
 * Date: 3/10/22
 * implements functions for converting from rgb color space to composite video
 */

#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pnm_ybr.h"
#include <mem.h>

#define DENOM 255

/* range_helper
 * returns bottom if n is less than bottom, top if more than top, n otherwise
 */
float range_helper(float n, float bottom, float top)
{
    if (n < bottom) {
        n = bottom;
    }
    else if (n > top) {
        n = top;
    }
    return n;
}

/* rgb_to_v
 * returns a UArray2 as specified by methods->new where every pixel is a
 * video encoding of img's rbg values
 */
A2Methods_UArray2 rgb_to_v(Pnm_ppm img, A2Methods_mapfun *map,
    A2Methods_T methods)
{
    int width = img->width;
    int height = img->height;
    A2Methods_UArray2 v_img = methods->new(width, height,
        sizeof(struct Pnm_ybr));
    struct a2_closure *cl = malloc(sizeof(*cl));
    cl->arr = v_img;
    cl->denom = img->denominator;
    cl->methods = methods;
    map(img->pixels, apply_rgb_to_v, cl);
    if (cl != NULL) {
        free(cl);
    }
    return v_img;
}

/* apply_rgb_to_v
 * sets Pnm_rgb el to its corresponding Pnm_ybr counterpart by saving results
 * to *cl's arr
 */
void apply_rgb_to_v(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl)
{
    (void)arr;
    struct a2_closure *new_cl = cl;
    if ((col > new_cl->methods->width(new_cl->arr)) ||
            (row > new_cl->methods->height(new_cl->arr))) {
        return;
    }
    Pnm_ybr ybr = new_cl->methods->at(new_cl->arr, col, row);
    Pnm_rgb rgb = el;
    float r = (rgb->red * 1.0)/(new_cl->denom);
    float g = (rgb->green * 1.0)/(new_cl->denom);
    float b = (rgb->blue * 1.0)/(new_cl->denom);
    float y = .299 * r + .587 * g + .114 * b;
    float pb = -.168736 * r - .331264 * g + .5 * b;
    float pr = .5 * r + -.418688 * g - .081312 * b;
    ybr->y = range_helper(y, 0, 1);
    ybr->pb = range_helper(pb, -0.5, 0.5);
    ybr->pr = range_helper(pr, -0.5, 0.5);
}
