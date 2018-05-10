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
	

$(LIB): lib.o
	ar rcs $@ lib.o

clean:
	rm $(LIB)
	rm test		
	rm fichier.stl  
	
