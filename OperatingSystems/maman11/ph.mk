all: binsem.a ut.a ph
FLAGS = -Wall -g -L./


ph: ph.c 
	gcc ${FLAGS} ph.c -lbinsem -lut -o ph


binsem.a:
	gcc $(FLAGS)  -c binsem.c
	ar rcu libbinsem.a binsem.o
	ranlib libbinsem.a 


ut.a:
	gcc $(FLAGS)  -c ut.c
	ar rcu libut.a ut.o
	ranlib libut.a 

clean:
	rm -f *.o 
	rm -f a.out
	rm -f *~
	rm -f ph
 
