#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define t (table_mem)=(table_mem)+(sizeof(table))
#define pt (pair_mem)=(pair_mem)+(sizeof(pair))

static long collisions = 0;
static long long table_mem = 0;
static long long pair_mem = 0;
static long long real_mem = 0;
static long long key_count = 0;
static long long hash(unsigned char *);
static table *get_location(table *,unsigned char *);

long long hash(unsigned char *c) {
  if(!c) {
    perror("HASH");
    exit(1);
  }
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
  if(!key || !val)
    return -1;
  int collided = 0, klen = strlen(key)+1, vlen = strlen(val)+1;
  unsigned char *k, *v;

  table *tab = get_location(main_table,key);
  if(!tab) {
    perror("INSERT");
    exit(1);
  }
  
  if(tab->l != NULL && strcmp(key,(unsigned char *)(((pair *)tab->l)->key)) == 0) {
    v = (unsigned char *)malloc(vlen); real_mem+=vlen;
    memcpy(v,val,vlen);
    ((pair *)tab->l)->val = v; /* overwrite value */
    return 0;
  }

  pair *p = (pair *)malloc(sizeof(pair)); pt;
  k = (unsigned char *)malloc(klen); real_mem+=klen;
  v = (unsigned char *)malloc(vlen); real_mem+=vlen;
  if(!p || !k || !v) {
    perror("INSERT");
    exit(1);
  }
  p->key = NULL; p->val = NULL; p->next = NULL;

  memcpy(k,key,klen);
  memcpy(v,val,vlen);
  p->key = (unsigned char *) k;
  p->val = (unsigned char *) v;

  if(tab->l == NULL) {
    tab->l = p;
  }else {
    collisions++;
    collided++;
    pair *temp = tab->l;
    tab->l = p;
    p->next = temp;
  }
  key_count++;
  return collided;
}

unsigned char * lookup(table *main_table, unsigned char *key) {
  table *tab = get_location(main_table,key);
  if(!tab) {
    perror("LOOKUP");
    exit(1);
  }

  if(tab->l == NULL)
    return NULL;
  else if(tab->l != NULL && ((pair *)tab->l)->next == NULL)
    return (unsigned char *)(((pair *)tab->l)->val);
  else {
    /* search through the chain to resolve collision */
    pair *temp = tab->l;
    while(temp->next != NULL) {
      if(strcmp(key, (unsigned char *)(temp->key)) == 0)
        return (unsigned char *)(temp->val);
      temp = temp->next;
    }
  }
  return NULL;
}

table *get_location(table *main_table, unsigned char *key) {
  if(!main_table) {
    perror("GET_LOCATION");
    exit(1);
  }
  table *tab = main_table;
  long long h = hash(key);
  long long mask;
  int count = 0;

  while(count < 64) {
    mask = 1;
    if(!(h & (mask<<count))) { /* left */
      if(tab->l == NULL) {
        tab->l = (table *)malloc(sizeof(table)); t;
        if(tab->l == NULL) {
          perror("GET_LOCATION");
          exit(1);
        }
        tab = tab->l;
        tab->l = NULL; tab->r = NULL;
      }else{
        tab = tab->l;
      }
    }else{ /* right */
      if(tab->r == NULL) {
        tab->r = (table *)malloc(sizeof(table)); t;
        if(tab->r == NULL) {
          perror("GET_LOCATION");
          exit(1);
        }
        tab = tab->r;
        tab->l = NULL; tab->r = NULL;
      }else{
        tab = tab->r;
      }
    }
    count++;
  }
  return tab;
}

long total_collisions() {
  return collisions;
}

long long total_memory() {
  return table_mem + pair_mem + real_mem;
}

long long real_memory() {
  return real_mem;
}

long long total_keys() {
  return key_count;
}

double memory_efficiency() {
  return (double)((real_mem * (long double)100)/(table_mem + pair_mem + real_mem));
}
