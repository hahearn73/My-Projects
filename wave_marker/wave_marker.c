
/* Harry Ahearn
 * watermarks 8 bit wav files. maps each byte in data chunk as byte | 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SUBCHUNK2_START 40
#define SUBCHUNK2_END 44

void print_header (FILE *fp);
int  get_size     (FILE *fp);
void print_masked (FILE *fp, int size);

/* main
 * infuses all data bytes in a wav file
 * maps byte | 1 over data chunk
 */
int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./mark file\n"); /* assumes executable is mark */
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File could not be opened.\n");
        return -1;
    }
    print_header(fp);
    print_masked(fp, get_size(fp));
}

/* copy_header
 * prints the header of wav file to stdout
 * SIDE EFFECT: moves the position pointer of fp to 40
 */
void print_header (FILE *fp)
{
    char c;
    uint32_t size;
    for (int i = 0; i < SUBCHUNK2_START; i++) {
        c = fgetc(fp);
        putchar(c);
    }
}

/* get_size
 * returns number of bytes in data chunk of wav file
 * assumes file position is properly set
 * SIDE EFFECT: prints subchunk2size to stdout,
 *              sets position pointer of fp to 44
 */
int get_size (FILE *fp)
{
    uint32_t size = 0;
    uint32_t temp;
    char c;
    for (int i = 0; i < SUBCHUNK2_END - SUBCHUNK2_START; i++) {
        c = fgetc(fp);
        putchar(c);
        temp = c;
        size = (temp << (8 * i)) | size; /* bytes are in little endian */
    }
    return size;
}

/* print_masked
 * masks each byte with byte | 1 and prints to stdout
 */
void print_masked (FILE *fp, int size)
{
    uint8_t MASK = 1;
    uint8_t temp;
    char c;
    for (int i = 0; i < size; i++) {
        c = fgetc(fp);
        temp = MASK | c;
        putchar(temp);
    }
}
