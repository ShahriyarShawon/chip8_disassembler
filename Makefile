dasm: main.c
	gcc -g -Wall -pedantic main.c -o dasm 

clean: dasm
	rm dasm
