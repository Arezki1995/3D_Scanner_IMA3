#VARIABLES
CC = clang
CFLAGS = -Wall -Werror -g
EXEC = test
DEPENDENCIES = main.c $(LIB)
HEADER =  lib.h
LIB = lib.a




$(EXEC): $(DEPENDENCIES)
	$(CC) $(CFLAGS) $^ -o $@
	rm *.o
	

lib.a: lib.o
	ar rcs lib.a lib.o

clean:
	rm test		
	rm fichier.stl  
	rm lib.a
