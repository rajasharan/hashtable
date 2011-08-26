#ifndef __HASH__
#define __HASH__ 
struct hTab {
  void *x[256]; /* 00 to FF */
  void *p;
};
typedef struct hTab hTab;

struct pair {
  void *key;
  void *val;
  void *p;
};
typedef struct pair pair;

long long hash(unsigned char *);

int insert(hTab *, unsigned char *, unsigned char *);

unsigned char * lookup(hTab *, unsigned char *);

int total_collisions();
#endif
