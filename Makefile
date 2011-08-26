hashtable : main.o hash.o
	gcc -o hashtable main.o hash.o

main.o : main.c hash.h
	gcc -c main.c

hash.o : hash.c hash.h
	gcc -c hash.c

clean :
	rm -f hashtable hash.o main.o

