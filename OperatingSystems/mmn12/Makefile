CC = gcc  -m32 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
 
DEBUG = 

all: libmm.a simpleTest complexTest 


simpleTest : simpleTest.c 
	$(CC) $(DEBUG) -Wall -o simpleTest simpleTest.c -lmm -L.

complexTest : complexTest.c 
	$(CC) $(DEBUG) -Wall -o complexTest complexTest.c -lmm -L.

libmm.a: malloc.o
	ar rcu libmm.a malloc.o
	ranlib libmm.a

malloc.o: malloc.c mm.h
	$(CC) $(DEBUG) -Wall -c malloc.c 

clean:
	rm -f complexTest simpleTest *.o libmm.a a.out *~
