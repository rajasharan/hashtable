#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "hash.h"

#define LEN 8000

int main(int argc, char *argv[]) {
  if(argc < 2 ) {
    printf("Usage: ./hash-test <list-of-input-files>\n");
    return -1;
  }
  
  int debug;
  FILE * f[260];
  int count = 1;
  while(count < argc && count < 259) {
    f[count] = fopen(argv[count],"r");
    char *line = malloc(LEN);
    int i;

    table *main_table = (table *)malloc(sizeof(table));
    main_table->l = NULL; main_table->r = NULL;
    if(!main_table) {
      perror("MAIN");
      exit(-1);
    }

    char *key, *val, *result;
    while(fgets(line,LEN,f[count]) != NULL) {
      i = insert(main_table,line,"5");
      if(i>0) {
        //printf("COLLISION: %s\n",key);
      }
    }

    line = malloc(LEN);
    fseek(f[count],0l,SEEK_SET);
    while(fgets(line,2000,f[count]) != NULL) {
      result = lookup(main_table,line);
      if(result == NULL) {
        //printf("ERROR: Not Found - %s\n",line);
      }
    }
    
    fclose(f[count]);
    f[count] = NULL;
    count = count+1;
  }

  printf("Total # of collisions: %lu\n",total_collisions());
  printf("Number of keys: %llu\n",total_keys());
  printf("Total memory footprint: %llu\n",total_memory());
  printf("Actual memory used: %llu\n",real_memory());
  printf("Memory efficiency: %f%%\n",memory_efficiency());
  //getchar();
  return 0;
}
