INC=-I../

.PHONY: all

all: test

test: main.o umorse.o print.o
	gcc -o test main.o print.o umorse.o

main.o: main.c
	gcc $(INC) -c $< -o $@

umorse.o: ../umorse.c
	gcc $(INC) -c $< -o $@

print.o: ../print.c
	gcc $(INC) -c $< -o $@

clean:
	rm *.o test
