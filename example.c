/* example.c */

#include "arcfour.h"

#define F fflush(stdout);

int main(void);
int16 length(int8 *str);

void printbin(int8 *input, int16 size) {
  int16 i;
  int8 *p;
  assert(size > 0);
  for (i = size, p = input; i; i--, p++) {
    /* code */
    if (!((i + 1) % 2)) {
      /* code */
      printf(" ");
    }
    printf("%.02x", *p);
  }
  printf("\n");
  return;
}

int16 length(int8 *str) {
  int8 *p = str;
  int16 len = 0;

  while (*p++) {
    len++;
  }
  return len;
}
// TODO: implement read and write to file.
//
//  char *readline(FILE *fp) {
//    size_t offset = 0;  // Index next char goes in the buffer
//    size_t bufsize = 4; // initial size of the buffer. preferably multiple of
//    2 char *buf;          // the buffer int c;              // the character
//    we are going to read.
//
//    buf = malloc(bufsize); // allocate inital buffer
//
//    while (c = fgetc(fp), c != '\n' && c != EOF) {
//      // check if we're out of room in the buffer account for the extra byte
//      for
//      // the NULL terminator
//      if (offset == bufsize - 1) { //-1 for the null terminator.
//        bufsize *= 2;
//        char *new_buf = realloc(buf, bufsize);
//        if (new_buf == NULL) {
//          free(buf); // bail on error
//          perror("Error in realloc\n");
//          exit(EXIT_FAILURE);
//        }
//        buf = new_buf; // successful realloc
//      }
//      buf[offset++] = c; // add the byte onto the buffer
//    }
//    // we hit newline or EOF
//    //
//    // if at EOF and we read no bytes, free the buffer and return NULL to
//    indicate
//    // we've hit EOF
//    if (c == EOF && offset == 0) {
//      free(buf);
//      return NULL;
//    }
//
//    // shrink to fit
//    if (offset < bufsize - 1) {
//      char *new_buf = realloc(buf, offset + 1); //+1 for the null terminator
//      if (new_buf == NULL) {
//        free(buf); // bail on error
//        perror("Error in realloc\n");
//        exit(EXIT_FAILURE);
//      }
//      buf = new_buf; // successful realloc
//    }
//    // Add the nul terminator
//    buf[offset] = '\0';
//    return buf;
//  }

int main(void) {
  Arcfour *rc4;
  int16 skey, stext;
  int8 *key, *from, *encrypted, *decrypted;
  key = (int8 *)"tomatoestomatoestomatoestomatoes"; /* 8 bits to 2048 bits */
  skey = length(key);
  from = (int8 *)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                 "Pellentesque tempor ornare porta. Sed ante ex, ultricies vel "
                 "sodales id, sodales ut quam. Nam ac auctor urna. Praesent "
                 "finibus purus a tincidunt scelerisque. Etiam tincidunt metus "
                 "quis sem ullamcorper, in tempus massa blandit. Curabitur vel "
                 "sem fringilla, gravida ante in, rutrum mi. Nulla facilisi. "
                 "Pellentesque id fringilla lectus, a molestie turpis. Cras "
                 "mollis velit a facilisis sagittis. Orci varius natoque "
                 "penatibus et magnis dis justo.";
  stext = length(from);
  printf("Initializing encryption..");
  F;
  rc4 = rc4init(key, skey); // could fail. check for 0 in production -- malloc
  // error.
  printf("done\n");
  // printbin(key, skey);
  // printf("'%s'\n->", from);
  // printbin(from, stext);
  // printbin(rc4->s, 256);
  // printf("array:\n");
  encrypted = rc4encrypt(from, stext, rc4);
  printf("Encrypted: %s\n", encrypted);
  free(rc4);
  rc4 = rc4init(key, skey); // could fail. check for 0 in production -- malloc
  decrypted = rc4decrypt(encrypted, length(encrypted), rc4);
  printf("Decrypted: %s\n", decrypted);
  free(rc4);
  free(encrypted);
  free(decrypted);

  // encrypted = rc4encrypt(from, stext);
}
