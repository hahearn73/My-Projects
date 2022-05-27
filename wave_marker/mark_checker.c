/* Harry Ahearn
 * checks 8 bit wav files for a water marking as specified in wave_marker.c
 */

#include <stdio.h>
#include <stdint.h>

#define SUBCHUNK2_START 40
#define SUBCHUNK2_END   44

int get_size  (FILE *fp);
int is_marked (FILE *fp, int size);

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
    /* sets position pointer for get_size */
    for (int i = 0; i < SUBCHUNK2_START; i++);
    int size = get_size(fp);
    /* arbitrarily sets position in data chunk to be tested for marking */
    char c;
    for (int i = 0; i < 100; i++) {
        c = fgetc(fp);
    }
    if (is_marked(fp, size))
        printf("marked\n");
    else
        printf("not marked\n");
    fclose(fp);
    return 0;
}

/* get_size
 * returns number of bytes in data chunk of wav file
 * assumes file position is properly set to SUBCHUNK2_START
 * SIDE EFFECT: sets position pointer of fp to SUBCHUNK2_END
 */
int get_size (FILE *fp)
{
    uint32_t size = 0;
    uint32_t temp;
    char c;
    for (int i = 0; i < SUBCHUNK2_END - SUBCHUNK2_START; i++) {
        c = fgetc(fp);
        temp = c;
        size = (temp << (8 * i)) | size; /* bytes are in little endian */
    }
    return size;
}

/* is_marked
 * returns 1 if each byte is marked with a 1 at least significant bit,
 * 0 otherwise
 * assumes file position pointer is in the data chunk with at least 1000 bytes
 * remaining in chunk to check for mark
 * SIDE EFFECT: moves position pointer 1000 bytes
 */
int is_marked (FILE *fp, int size)
{
    uint8_t MASK = 1;
    uint8_t temp;
    char c;
    for (int i = 0; i < 1000; i++) {
        c = fgetc(fp);
        temp = c;
        temp = MASK & temp;
        if (temp != 1)
            return 0;
    }
    return 1;
}
