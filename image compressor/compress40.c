/* compress40.c
 * Assignment 4: arith
 * Harry Ahearn (hahear01), Adnan Jalal (ajalal03)
 * Date: 3/10/22
 * contains functions for compressing and decompressing image files
 */

#include "compress40.h"
#include <arith40.h>
#include "pnm_ybr.h"
#include <assert.h>
#include "pnm.h"
#include "a2methods.h"
#include "a2plain.h"
#include <inttypes.h>
#include <bitpack.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "convert.h"
#include "shift.h"
#include "mem.h"

#define DENOM 255
#define PR_LSB 0
#define PB_LSB 4
#define D_LSB 8
#define C_LSB 13
#define B_LSB 18
#define A_LSB 23

struct codeword {
    uint64_t pb, pr, a;
    int64_t b, c, d;
};
typedef struct codeword codeword;

void decompress_words(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl);
void compress_to_words(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl);
struct Pnm_rgb ybr_to_rgb(struct Pnm_ybr ybr);

/* compress40
 * compresses image held in fp to component video format and then to 32 bit
 * codewords and outputs result to stdout
 */
void compress40(FILE *fp)
{
    A2Methods_T methods = uarray2_methods_plain;
    A2Methods_mapfun *map = methods->map_default;
    Pnm_ppm rgb = Pnm_ppmread(fp, methods);
    rgb->height = rgb->height - (rgb->height % 2) + 1;
    rgb->width = rgb->width - (rgb->width % 2) + 1;
    A2Methods_UArray2 v_img = rgb_to_v(rgb, map, methods);
    printf("COMP40 Compressed image format 2\n%u %u\n", rgb->width - 1,
        rgb->height - 1);
    map(v_img, compress_to_words, methods);
    Pnm_ppmfree(&rgb);
    methods->free(&v_img);
}

/* decompress40
 * decompresses a compressed ppm in fp and outputs resulting ppm image to
 * stdout
 */
void decompress40(FILE *fp)
{
    unsigned width, height;
    int read = fscanf(fp, "COMP40 Compressed image format 2\n%u %u", &width,
        &height);
    assert(read == 2);
    int c = getc(fp);
    assert(c == '\n');
    A2Methods_T methods = uarray2_methods_plain;
    A2Methods_UArray2 arr = methods->new(width, height,
        sizeof(struct Pnm_rgb));
    struct Pnm_ppm pix = {
        .width = width, .height = height, .denominator = DENOM, .pixels = arr,
        .methods = methods
    };
    methods->map_col_major(pix.pixels, decompress_words, fp);
    Pnm_ppmwrite(stdout, &pix);
    methods->free(&arr);
}

/* get_codeword
 * extracts a 32 bit word from fp and returns a codeword with uncompressed
 * data from the word
 */
codeword get_codeword(FILE *fp)
{
    uint64_t word = 0;
    unsigned char byte;
    for (int i = 0; i <= 3; i++) {
        byte = getc(fp);
        uint64_t mask = shift_leftu((uint64_t)byte, 24 - (8  * i));
        word = word | mask;
    }
    codeword ret;
    ret.pr = Bitpack_getu(word, 4, PR_LSB);
    ret.pb = Bitpack_getu(word, 4, PB_LSB);
    ret.d = Bitpack_gets(word, 5, D_LSB);
    ret.c = Bitpack_gets(word, 5, C_LSB);
    ret.b = Bitpack_gets(word, 5, B_LSB);
    ret.a = Bitpack_getu(word, 9, A_LSB);
    return ret;
}

/* decompress_words
 * creates 4 Pnm_ybr pixels from arr based on col and row and saves them to arr
 * in positions (col, row), (col - 1, row), (col, row - 1), and (col - 1,
 * row - 1)
 */
void decompress_words(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl)
{
    (void)el;
    if (col % 2 == 1 && row % 2 == 1) {
        codeword block = get_codeword((FILE *) cl);
        struct Pnm_ybr one, two, three, four;
        float a = (float) block.a / 511.0;
        float b = (float) block.b / 50.0;
        float c = (float) block.c / 50.0;
        float d = (float) block.d / 50.0;
        one.y = range_helper(a - b - c + d, 0, 1);
        two.y = range_helper(a - b + c - d, 0, 1);
        three.y = range_helper(a + b - c - d, 0, 1);
        four.y = range_helper(a + b + c + d, 0, 1);
        float pb = Arith40_chroma_of_index(block.pb);
        float pr = Arith40_chroma_of_index(block.pr);
        one.pb = pb;
        two.pb = pb;
        three.pb = pb;
        four.pb = pb;
        one.pr = pr;
        two.pr = pr;
        three.pr = pr;
        four.pr = pr;
        A2Methods_T methods = uarray2_methods_plain;
        *((struct Pnm_rgb *) methods->at(arr, col, row)) =
            ybr_to_rgb(one);
        *((struct Pnm_rgb *) methods->at(arr, col - 1, row)) =
            ybr_to_rgb(two);
        *((struct Pnm_rgb *) methods->at(arr, col, row - 1)) =
            ybr_to_rgb(three);
        *((struct Pnm_rgb *) methods->at(arr, col - 1, row - 1)) =
            ybr_to_rgb(four);
    }
}

/* float_to_dct
 * performs a discrete cosine transformation on n and returns the result as an
 * int
 */
int float_to_dct(float n)
{
    return round((int)(50 * range_helper(n, -0.3, 0.3)));
}

/* make_codeword
 * returns a single codeword which is a representation of the 4 ybr values
 * one-four
 */
codeword make_codeword(Pnm_ybr one, Pnm_ybr two, Pnm_ybr three, Pnm_ybr four)
{
    float avg_pb, avg_pr, a, b, c, d;
    avg_pb = (one->pb + two->pb + three->pb + four->pb) / 4;
    avg_pr = (one->pr + two->pr + three->pr + four->pr) / 4;
    avg_pb = Arith40_index_of_chroma(avg_pb);
    avg_pr = Arith40_index_of_chroma(avg_pr);
    a = (one->y + two->y + three->y + four->y) / 4;
    b = (four->y + three->y - two->y - one->y) / 4;
    c = (two->y - one->y - three->y + four->y) / 4;
    d = (one->y - two->y - three->y + four->y) / 4;
    int a_ret = (int) round((511 * range_helper(a, 0, 1)));
    int b_ret = float_to_dct(b);
    int c_ret = float_to_dct(c);
    int d_ret = float_to_dct(d);
    codeword ret;
    ret.a = a_ret;
    ret.b = b_ret;
    ret.c = c_ret;
    ret.d = d_ret;
    ret.pb = avg_pb;
    ret.pr = avg_pr;
    return ret;
}

/* word_out
 * creates a uint32_t which is a compressed representation of word and outputs
 * it to stdout
 */
void word_out(codeword word)
{
    uint32_t out = 0;
    out = Bitpack_newu(out, 4, PR_LSB, word.pr);
    out = Bitpack_newu(out, 4, PB_LSB, word.pb);
    out = Bitpack_news(out, 5, D_LSB, word.d);
    out = Bitpack_news(out, 5, C_LSB, word.c);
    out = Bitpack_news(out, 5, B_LSB, word.b);
    out = Bitpack_newu(out, 9, A_LSB, word.a);
    unsigned char byte;
    for (int i = 0; i <= 3; i++) {
        byte = shift_rightu(out, (24 - (8 * i)));
        putchar(byte);
    }
}

/* compress_to_words
 * compresses groups of 4 pixels whenever col and row are both odd into a
 * codeword. calls word_out on the codeword to output the compressed word
 */
void compress_to_words(int col, int row, A2Methods_UArray2 arr, void *el,
    void *cl)
{
    A2Methods_T methods = cl;
    codeword word;
    (void)el;
    if (row % 2 == 1 && col % 2 == 1) {
        Pnm_ybr one = methods->at(arr, col, row);
        Pnm_ybr two = methods->at(arr, col - 1, row);
        Pnm_ybr three = methods->at(arr, col, row - 1);
        Pnm_ybr four = methods->at(arr, col - 1, row - 1);
        word = make_codeword(one, two, three, four);
        word_out(word);
    }
}

/* ybr_to_rgb
 * converts a Pnm_ybr to its corresponding Pnm_rgb and returns it
 */
struct Pnm_rgb ybr_to_rgb(struct Pnm_ybr ybr)
{
    struct Pnm_rgb ret;
    float y = ybr.y;
    float pb = ybr.pb;
    float pr = ybr.pr;
    int r = DENOM * ((1.0 * y) + (0 * pb) + (1.402 * pr));
    int g = DENOM * ((1.0 * y) + (-0.344136 * pb) + (-0.714136 * pr));
    int b = DENOM * ((1.0 * y) + (1.772 * pb) + (0 * pr));
    r = range_helper(r, 0, DENOM);
    g = range_helper(g, 0, DENOM);
    b = range_helper(b, 0, DENOM);
    ret.red = r;
    ret.green = g;
    ret.blue = b;
    return ret;
}
