all: 
	gcc -c lista.c -o bin/lista.o
	gcc -c elevador.c -o bin/elevador.o
	gcc -c merge.c -o bin/merge.o
	gcc -c main.c -o bin/main.o
	gcc -c gerador.c -o bin/gerador.o
	gcc -c atende.c -o bin/atende.o
	gcc -c data.c -o bin/data.o
	gcc bin/lista.o bin/elevador.o bin/merge.o bin/gerador.o bin/atende.o bin/data.o bin/main.o -o exit
