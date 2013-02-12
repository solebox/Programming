#all: binsem.a ut.a ph 
all: ph
FLAGS = -Wall -Werror  -L./


ph: ph.c binsem.a ut.a 
	gcc ${FLAGS} ph.c -lbinsem -lut -o ph


binsem.a: 
	gcc $(FLAGS) -c binsem.c
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
	rm -f *a 
