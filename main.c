#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash.h"

int main() {
  hTab *main_table = (hTab *)malloc(sizeof(hTab));
  unsigned char *key;
  unsigned char *val;
  unsigned char *result;

  char input[1000];
  int in,collision,n;
  while(1) {
    collision=0;
    n=0;
    putchar('>');
    putchar('>');
    putchar(' ');

    while ((in = getchar()) != EOF && in != 10 && in != 13 && n < 1000) {
      input[n++] = in;
    }
    input[n] = '\0';

    key = strtok(input,"=");
    val = strtok(NULL,"=");
    if(val != NULL) { /* insert */
      collision = insert(main_table,key,val);
      if(collision)
        printf("key '%s' inserted with collision\n",key);
      else
        printf("key '%s' inserted\n",key);
    }else { /* lookup */
      result = lookup(main_table,input);
      if(result == NULL)
        printf("Value not found for key '%s'\n",key);
      else
        printf("%s\n",result);
    }
  }

  return 0;
}

