/* a2plain.c
 * by Louis Tuccio and Harry Ahearn, 2-23-22
 * HW3: Locality and the costs of loads and stores
 *
 * Summary: implementation of method suite A2Methods_UArray2 of type
 * A2Methods
 */

#include <string.h>
#include <a2plain.h>
#include "uarray2.h"

/* new: creates new A2Methods_UArray2 and returns it
 *
 * Note(s): raises checked runtime error if width or height is negative,  
 * size is non-positive
 */
static A2Methods_UArray2 new(int width, int height, int size)
{
  return UArray2_new(width, height, size);
}

/* new_with_blocksize: creates new A2Methods_UArray2 and returns it,
 * blocksize parameter is ignored
 *
 * Note(s): raises checked runtime error if width or height is negative,  
 * size is non-positive
 */
static A2Methods_UArray2 new_with_blocksize(int width, int height, int size, 
int blocksize)
{
  /* must void parameter since we do not use it */ 
  (void) blocksize;
  return UArray2_new(width, height, size);
}

/* a2free: deallocates and frees array2p
 *
 * Note(s): it is a checked runtime error for *array2p or array2p to be null 
 */
static void a2free(A2Methods_UArray2 *array2p)
{
  UArray2_free((UArray2_T *) array2p);
}

/* height: returns the  width of array2
 * 
 * Note(s): It is a checked runtime error for array2 to be null
 */
static int width(A2Methods_UArray2 array2)
{
  return UArray2_width(array2);
}

/* height: returns the height of array2
 * 
 * Note(s): It is a checked runtime error for array2 to be null
 */
static int height(A2Methods_UArray2 array2)
{
  return UArray2_height(array2);
}

/* size: returns the size of each element in array2
 * 
 * Note(s): It is a checked runtime error for array2 to be null
 */
static int size(A2Methods_UArray2 array2)
{
  return UArray2_size(array2);
}

/* blocksize: returns one (blocksize is not used in this implementation)
 */
static int blocksize(A2Methods_UArray2 array2)
{
  (void) array2;
  return 1;
}

/* at: returns pointer to the element stored at the given column and row
 *
 * Note(s): it is a checked runtime error for array2 to be null or for the
 * column or row number to be out of bounds
 */
static A2Methods_Object *at(A2Methods_UArray2 array2, int i, int j)
{
  return UArray2_at(array2, i, j);
}
/*
typedef void UArray2_applyfun(int i, int j, UArray2_T array2, void *elem,
        void *cl);*/

static void map_row_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

static void map_col_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}


struct small_closure {
  A2Methods_smallapplyfun *apply; 
  void                    *cl;
};


static void apply_small(int i, int j, UArray2_T uarray2,
                        void *elem, void *vcl)
{
  struct small_closure *cl = vcl;
  (void)i;
  (void)j;
  (void)uarray2;
  cl->apply(elem, cl->cl);
}

static void small_map_row_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_row_major(a2, apply_small, &mycl);
}

static void small_map_col_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_col_major(a2, apply_small, &mycl);
}


static struct A2Methods_T uarray2_methods_plain_struct = {
  new,
  new_with_blocksize,
  a2free,
  width,
  height,
  size,
  blocksize,
  at,
  map_row_major,
  map_col_major,
  NULL,                         // map_block_major
  map_col_major,                // map_default
  small_map_row_major,
  small_map_col_major,
  NULL,                         //small_map_block_major,
  small_map_col_major,          // small_map_default
};

// finally the payoff: here is the exported pointer to the struct

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
