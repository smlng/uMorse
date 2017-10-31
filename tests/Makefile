CFLAGS += -I../

.PHONY: all

all: test

test: main.o umorse.o print.o
	gcc -o test main.o print.o umorse.o

main.o: main.c
	gcc $(CFLAGS) -c $< -o $@

umorse.o: ../umorse.c
	gcc $(CFLAGS) -c $< -o $@

print.o: ../print.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o test
