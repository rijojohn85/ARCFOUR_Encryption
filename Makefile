all: clean arcfour.o example
example: example.o
	gcc arcfour.o example.o -o bin/example -Wall -O2
example.o: example.c
	gcc -c -O2 -Wall example.c
archfour.so: arcfour.o
	gcc arcfour.o -o arcfour.so O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE
arcfour.o: ./arcfour.c
	gcc -c -O2 -Wall arcfour.c

clean:
	rm -rf *.o *.so bin/*

#test
compile_test: ./munit/munit.h ./munit/munit.c ./arcfour.h arcfour.c
	gcc -o bin/arcfour_test ./munit/munit.c ./arcfour.c ./test.c
unit-test: compile_test
	bin/arcfour_test
