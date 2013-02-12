all:main

main:main.c funcs.a
	gcc -o main main.c funcs.a
funcs.a:
	gcc -c funcs.c
	ar rcu funcs.a funcs.o
