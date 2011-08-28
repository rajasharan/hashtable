DEBUG=-ggdb

hashtable : main.o hash.o
	gcc $(DEBUG) -o hashtable main.o hash.o

main.o : main.c hash.h
	gcc $(DEBUG) -c main.c

hash.o : hash.c hash.h
	gcc $(DEBUG) -c hash.c

clean :
	rm -f hashtable hash.o main.o

