#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define t (table_mem)=(table_mem)+(sizeof(table))
#define pt (real_mem)=(real_mem)+(sizeof(pair))
#define LENGHT 1000

static long collisions = 0;
static long long table_mem = 0;
static long long real_mem = 0;
static long long key_count = 0;
static long long hash(unsigned char *);
static table *get_location(table *,unsigned char *);

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

int insert(table *main_table, unsigned char *key, unsigned char *val) {
  if(key == NULL || val == NULL)
    return -1;
  int collided = 0;

  main_table = get_location(main_table,key);
  if(main_table->p != NULL && strcmp(key,(unsigned char *)(((pair *)main_table->p)->key)) == 0)
    return 0; /* incoming duplicate key */

  pair *p = (pair *)malloc(sizeof(pair)); pt;
  unsigned char *k, *v;
  k = (unsigned char *)malloc(LENGHT);
  v = (unsigned char *)malloc(LENGHT);
  strcpy(k,key);
  strcpy(v,val);
  p->key = (unsigned char *) k;
  p->val = (unsigned char *) v;
  if(main_table->p == NULL) {
    main_table->p = p;
  }else {
    collisions++;
    collided++;
    pair *temp = main_table->p;
    main_table->p = p;
    p->p = temp;
  }
  key_count++;
  return collided;
}

unsigned char * lookup(table *main_table, unsigned char *key) {
  main_table = get_location(main_table,key);
  if(main_table->p == NULL)
    return NULL;
  else if(main_table->p != NULL && ((pair *)main_table->p)->p == NULL)
    return (unsigned char *)(((pair *)main_table->p)->val);
  else {
    /* search through the chain to resolve collision */
    pair *temp = main_table->p;
    while(temp->p != NULL) {
      if(strcmp(key, (unsigned char *)(temp->key)) == 0)
        return (unsigned char *)(temp->val);
      temp = temp->p;
    }
  }
  return NULL;
}

table *get_location(table *main_table, unsigned char *key) {
  long long h = hash(key);
  long long mask = 1;
  long long temp;
  char *c;
  short byte = -1;
  short count = 0;

  while(count < 64) {
    mask = mask<<count;
    temp = h & mask;
    c = (char *)&temp;

    if(count % 8 == 0)
      byte++;

    while(byte > 0)
      c++; byte--;

    if(*c) { /* left */
      if(main_table->l == NULL) {
        main_table->l = (table *)malloc(sizeof(table)); t;
      }
      main_table = main_table->l;
    } else { /* right */
      if(main_table->r == NULL) {
        main_table->r = (table *)malloc(sizeof(table)); t;
      }
      main_table = main_table->r;
    }
    count++;
  }
  return main_table;
}

long total_collisions() {
  return collisions;
}

long long total_memory() {
  return real_mem + table_mem;
}

long long real_memory() {
  return real_mem;
}

long long total_keys() {
  return key_count;
}

double memory_efficiency() {
  return (double)((real_mem * (long double)100)/(real_mem + table_mem));
}
