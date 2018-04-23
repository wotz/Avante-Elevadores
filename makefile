all: 
	gcc -c listaBasics.c -o lista.o
	gcc -c elevador.c -o elevador.o
	gcc -c controle.c -o controle.o
	gcc -c main.c -o main.o
	gcc -c merge.c -o merge.o
	gcc main.o elevador.o lista.o controle.o merge.o -o exit

