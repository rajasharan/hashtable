#ifndef __HASH__
#define __HASH__ 
struct table {
  void *l; /* left */
  void *r; /* right */
  void *p; /* key-val pair */
};
typedef struct table table;

struct pair {
  void *key;
  void *val;
  void *p;
};
typedef struct pair pair;

int insert(table *, unsigned char *, unsigned char *);

unsigned char * lookup(table *, unsigned char *);

long total_collisions();
long long total_memory();
long long real_memory();
long long total_keys();
double memory_efficiency();

#endif
