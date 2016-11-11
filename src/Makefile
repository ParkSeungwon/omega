CFLAG = -g -c -fmax-errors=1 
INCLUDE = -I../
CC = gcc
OBJ = $(patsubst %.c, ../obj/%.o, $(wildcard *.c))
MAIN_OBJ = $(patsubst %.C, ../obj/%.x, $(wildcard *.C))

all : $(OBJ) $(MAIN_OBJ)

../obj/%.o : %.c 
	$(CC)  $(INCLUDE) $(CFLAG) $< -o $@

../obj/%.x : %.C
	$(CC)  $(INCLUDE) $(CFLAG) $< -o $@
