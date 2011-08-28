DEBUG=-ggdb

tests : 
	rm -rf hash*
	cp ../hash.c .
	cp ../hash.h .
	gcc $(DEBUG) -o hash-test test.c hash.c
	rm -rf hash.c hash.h hash.o
	echo 'USAGE: ./hash-test <input-files-containing-keys>'

clean :
	rm -f hash-test hash.o test.o hash.c hash.h 
