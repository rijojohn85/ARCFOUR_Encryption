#ifndef ARCFOUR
#define ARCFOUR

#define _GNU_SOURCE

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define rc4decrypt(x, y, z) rc4encrypt(x, y, z)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_arcfour {
  int16 i, j;
  int8 k;
  int8 s[256];
};

typedef struct s_arcfour Arcfour;

Arcfour *rc4init(int8 *, int16);
int8 rc4byte(Arcfour *rc4);
int8 *rc4encrypt(int8 *, int16, Arcfour *);

#endif
