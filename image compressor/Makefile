# Makefile for arith (Comp 40 Assignment 4)
CC = gcc # The compiler being used
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

LDLIBS = -larith40 -l40locality -lnetpbm -lcii40 -lm -lrt
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: 40image

## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

40image: a2plain.o uarray2.o convert.o bitpack.o 40image.o compress40.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)
