#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

static int collisions = 0;
static long long hash(unsigned char *);
static int total_collisions();

long long hash(unsigned char *c) {
  long long h = 6; /* 0110 */
  while(*c != '\0' && *c != 10 && *c != 13) {
    /* shifting bits left because there will be new bits of c coming in */
    h = (h<<5) + *c ;
    c++;
  }
  return h;
}

int insert(hTab *main_table, unsigned char *key, unsigned char *val) {
  int collided = 0;
  long long h = hash(key);
  unsigned char *c = (unsigned char *) &h;
  short i = *c;
  //printf("c = %d\n",i);

  if(main_table->x[i] == NULL)
    main_table->x[i] = (hTab *)malloc(sizeof(hTab));

  hTab *tab;
  tab = main_table->x[i];
  int count = 0;
  while(count < 7) { /* 8-byte (64-bit) address spacing */
    i = *++c;
    //printf("c = %d\n",i);
    if(tab->x[i] == NULL)
      tab->x[i] = (hTab *)malloc(sizeof(hTab));
    tab = tab->x[i];
    count++;
  }
  
  pair *p = (pair *)malloc(sizeof(pair));
  unsigned char *k, *v;
  k = (unsigned char *)malloc(1000);
  v = (unsigned char *)malloc(1000);
  memcpy(k,key,val-key);
  strcpy(v,val);
  p->key = (unsigned char *) k;
  p->val = (unsigned char *) v;
  if(tab->p == NULL || lookup(main_table,key) != NULL) { /* if key exsists, overwrite */
    tab->p = p;
  }else { /* collision should not happen otherwise performance is screwed */
    pair *temp = tab->p;
    while(temp->p != NULL) {
      collisions++;
      collided++;
      temp = temp->p; 
    }
    temp->p = p;
  }

  return collided;
}

unsigned char * lookup(hTab *main_table, unsigned char *key) {
  long long h = hash(key);
  unsigned char *c = (unsigned char *) &h;
  short i = *c;
  //printf("v = %d\n",i);

  if(main_table->x[i] == NULL)
    return NULL;
  
  hTab *tab = main_table->x[i];
  int count = 0;
  while(count < 7) {
    i = *++c;
    //printf("v = %d\n",i);
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
      //printf("s = %s\n",(unsigned char *)(((pair *)tab->p)->key));
      if(strcmp(key, (unsigned char *)(temp->key)) == 0)
        return (unsigned char *)(temp->val);
      temp = temp->p;
    }
  }

  return NULL;
}

int total_collisions() {
  return collisions;
}
