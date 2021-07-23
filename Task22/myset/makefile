myset: myset.o set.o
	gcc -g -ansi -pedantic -Wall myset.o set.o -o myset
set.o: set.c set.h
	gcc -c -g -ansi -pedantic -Wall set.c -o set.o
myset.o: myset.c myset.h set.o
	gcc -c -g -ansi -pedantic -Wall myset.c -o myset.o
