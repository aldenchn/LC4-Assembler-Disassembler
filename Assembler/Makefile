all: assembler asm_parser.o

asm_parser.o: asm_parser.c asm_parser.h
	clang -c asm_parser.c
	
assembler: assembler.c asm_parser.h asm_parser.o
	clang -g asm_parser.o assembler.c -o assembler	
	
clean:
	rm -rf *.o

clobber: clean
	rm -rf assembler 