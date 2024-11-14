#include "arcfour.h"
#include <stdlib.h>

Arcfour *rc4init(int8 *key, int16 size) {
  int16 x;
  int8 tmp;
  Arcfour *p = malloc(sizeof(struct s_arcfour));

  if (!p) {
    printf("Malloc error. Exiting Program.\n");
    exit(EXIT_FAILURE);
  }

  for (x = 0; x < 256; x++) {
    p->s[x] = 0;
  }
  p->i = p->j = p->k = 0;

  //   for i from 0 to 255
  //     S[i] := i
  // endfor
  for (p->i = 0; p->i <= 255; p->i++) {
    p->s[p->i] = (int8)p->i;
  }
  // for i from 0 to 255
  //     j := (j + S[i] + key[i mod keylength]) mod 256
  //     swap values of S[i] and S[j]
  // endfor

  for (p->i = 0; p->i <= 255; p->i++) {
    p->j = (p->j + p->s[p->i] + key[(p->i % size)]) % 256;
    tmp = p->s[p->i];
    p->s[p->i] = p->s[p->j];
    p->s[p->j] = tmp;
  }
  p->i = p->j = 0;
  return p;
}

int8 rc4byte(Arcfour *p) {
  int8 tmp;
  int16 t;
  p->i = (p->i + 1) % 256;
  p->j = (p->j + p->s[p->i]) % 256;
  tmp = p->s[p->i];
  p->s[p->i] = p->s[p->j];
  p->s[p->j] = tmp;
  t = (p->s[p->i] + p->s[p->j]) % 256;
  p->k = p->s[t];
  return p->k;
}

int8 *rc4encrypt(int8 *pt, int16 size, Arcfour *p) {
  int8 *cipher_text = malloc((sizeof(int8) * size) + 1);
  int8 *ct = cipher_text;
  while (*pt) {
    *ct = *pt ^ rc4byte(p);
    ct += 1;
    pt += 1;
  }
  *ct = '\0';
  return cipher_text;
}
