OBJECTS = main.o sort.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c sort.h
	@gcc main.c -c $(FLAGS)

sort.o: sort.c sort.h
	@gcc sort.c -c $(FLAGS)

run: all
	@./exec $$ARG

valgrind: all
	@valgrind $(VFLAGS) ./exec $$ARG

clean:
	@rm -rf *.o exec

zip:
	@zip sort.zip Makefile main.c sort.c sort.h
