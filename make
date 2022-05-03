all: solution.c solution.h
	gcc -shared solution.c -fPIC -o libsolution.so
