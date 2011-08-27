#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define t (table_mem)=(table_mem)+(sizeof(hTab))
#define pt (real_mem)=(real_mem)+(sizeof(pair))

static long collisions = 0;
static long long table_mem = 0;
static long long real_mem = 0;
static long long key_count = 0;
static long long hash(unsigned char *);

long long hash(unsigned char *c) {
  long long h = 6; /* 0110 */
  while(*c != '\0' && *c != 10 && *c != 13) {
    /* shifting bits left because there will be new bits of c coming in */
    h = (h<<5) + *c ;
    c++;
  }
  //printf("%llx\n",h);
  return h;
}

int insert(hTab *main_table, unsigned char *key, unsigned char *val) {
  if(key == NULL || val == NULL)
    return -1;
  int collided = 0;
  long long h = hash(key);
  unsigned char *c = (unsigned char *) &h;
  short i = *c;

  if(main_table->x[i] == NULL) {
    main_table->x[i] = (hTab *)malloc(sizeof(hTab));
    if(main_table->x[i] == NULL) {
      perror("INSERT: ");
      return -1;
    }
    t; 
  }

  hTab *tab;
  tab = main_table->x[i];
  int count = 0;
  while(count < 7) { /* 8-byte (64-bit) address spacing */
    i = *++c;
    if(tab->x[i] == NULL) {
      tab->x[i] = (hTab *)malloc(sizeof(hTab));
      if(tab->x[i] == NULL) {
        perror("INSERT: ");
        return -1;
      }
      t;
    }
    tab = tab->x[i];
    count++;
  }
  
  pair *p = (pair *)malloc(sizeof(pair)); pt;
  unsigned char *k, *v;
  k = (unsigned char *)malloc(1000);
  v = (unsigned char *)malloc(1000);
  strcpy(k,key);
  strcpy(v,val);
  p->key = (unsigned char *) k;
  p->val = (unsigned char *) v;
  if(tab->p == NULL) {
    tab->p = p;
  }else { 
    collisions++;
    collided++;
    pair *temp = tab->p;
    tab->p = p;
    p->p = temp;
  }
  key_count++;
  return collided;
}

unsigned char * lookup(hTab *main_table, unsigned char *key) {
  long long h = hash(key);
  unsigned char *c = (unsigned char *) &h;
  short i = *c;

  if(main_table->x[i] == NULL)
    return NULL;
  
  hTab *tab = main_table->x[i];
  int count = 0;
  while(count < 7) {
    i = *++c;
    if(tab->x[i] == NULL)
      return NULL;

    tab = tab->x[i];
    count++;
  }

  if(tab->p == NULL)
    return NULL; /* should never reach here */
  else if(tab->p != NULL && ((pair *)tab->p)->p == NULL) /* when no collision */ 
    return (unsigned char *)(((pair *)tab->p)->val);
  else {
    /* search through the chain to resolve collision */
    pair *temp = tab->p;
    while(temp->p != NULL) {
      if(strcmp(key, (unsigned char *)(temp->key)) == 0)
        return (unsigned char *)(temp->val);
      temp = temp->p;
    }
  }

  return NULL;
}

long total_collisions() {
  return collisions;
}

long long total_memory() {
  return real_mem + table_mem;
}

long long total_keys() {
  return key_count;
}

int memory_efficiency() {
  return (int)((real_mem * 100.0f )/(real_mem + table_mem));
}
