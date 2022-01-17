test: project1.o test.o
	gcc ggdb -o test project1.o test.c
test.o: test.c project1.h
	gcc -c project1.c test.c -pedantic -std=gnu99 -Wall -Werror
project1.o: project1.c project1.h
	gcc -c project1.c -pedantic -std=gnu99 -Wall -Werror

clean:
	rm -f *~ *.o
