#ifndef __HASH__
#define __HASH__ 

typedef struct pair {
  unsigned char *key;
  unsigned char *val;
  struct pair *p;
}pair;

typedef struct table {
  struct table *l; /* left */
  struct table *r; /* right */
  pair *p; /* key-val pair */
} table;

int insert(table *, unsigned char *, unsigned char *);

unsigned char * lookup(table *, unsigned char *);

long total_collisions();
long long total_memory();
long long real_memory();
long long total_keys();
double memory_efficiency();

#endif
