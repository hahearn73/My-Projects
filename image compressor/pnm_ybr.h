/* pnm_ybr.h
 * Assignment 4: arith
 * Harry Ahearn (hahear01), Adnan Jalal (ajalal03)
 * Date: 3/10/22
 * defines the Pnm_ybr struct and typedefines it as Pnm_ybr*
 */

#ifndef PNM_YBR_INCLUDED
#define PNM_YBR_INCLUDED
/* video encoded version of Pnm_rgb */
typedef struct Pnm_ybr {
    float y;
    float pb;
    float pr;
} *Pnm_ybr;

#endif
