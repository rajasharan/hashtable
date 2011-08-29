#ifndef __HASH__
#define __HASH__ 

typedef struct pair {
  void *key;
  void *val;
  void *next;
}pair;

typedef struct table {
  void *l; /* left  */ //as well as act as pair pointer when leaf
  void *r; /* right */
} table;

int insert(table *, unsigned char *, unsigned char *);

unsigned char * lookup(table *, unsigned char *);

long total_collisions();
long long total_memory();
long long real_memory();
long long total_keys();
double memory_efficiency();

#endif
