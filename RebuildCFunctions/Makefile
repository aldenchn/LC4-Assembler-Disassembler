all: my_string.o program1 program2 program3 program4
    
my_string.o: my_string.c my_string.h
	clang -c my_string.c

program1: program1.c my_string.h my_string.o
	clang my_string.o program1.c -o program1

program2: program2.c my_string.h my_string.o
	clang my_string.o program2.c -o program2
	
program3: program3.c my_string.h my_string.o
	clang my_string.o program3.c -o program3

program4: program4.c my_string.h my_string.o
	clang my_string.o program4.c -o program4
	
clean:
	rm -rf *.o

clobber: clean
	rm -rf program1 program2 program3