all: 
	gcc -c lista.c -o lista.o
	gcc -c elevador.c -o elevador.o
	gcc -c controle.c -o controle.o
	gcc -c main.c -o main.o
	gcc main.o elevador.o lista.o controle.o -o exit

