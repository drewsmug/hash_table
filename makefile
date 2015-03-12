OBJECTS = main.o hash.o
CFLAGS = -g

main : $(OBJECTS)
	gcc -o main $(OBJECTS)

main.o : main.c globals.h hash.h
	gcc $(CFLAGS) -c -o main.o main.c
hash.o : hash.c globals.h hash.h
	gcc $(CFLAGS) -c -o hash.o hash.c

clean :
	rm -f main $(OBJECTS)
