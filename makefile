all: 
	gcc -c lista.c -o bin/lista.o
	gcc -c elevador.c -o bin/elevador.o
	gcc -c main.c -o bin/main.o
	gcc -c data.c -o bin/data.o
	gcc -c smart.c -o bin/smart.o
	gcc -c estatistica.c -o bin/estatistica.o
	gcc bin/lista.o bin/elevador.o bin/main.o bin/smart.o bin/data.o bin/estatistica.o -lm -o exit
