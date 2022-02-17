all: lc4_loader.o lc4_memory.o lc4_disassembler.o lc4 

lc4_disassembler.o: lc4_memory.o lc4_memory.h lc4_disassembler.c lc4_disassembler.h 
	clang -g -c lc4_disassembler.c

lc4_memory.o: lc4_memory.c lc4_memory.h
	clang -g -c lc4_memory.c
    
lc4_loader.o: lc4_loader.c lc4_loader.h lc4_memory.h
	clang -g -c lc4_loader.c
    
lc4: lc4.c lc4_memory.o lc4_loader.o
	clang -g lc4_loader.o lc4_disassembler.o lc4_memory.o lc4.c -o lc4
	
clean:
	rm -rf *.o
	
clobber: clean
	rm -rf lc4