all: 
	gcc -c lista.c -o lista.o
	gcc -c elevador.c -o elevador.o
	gcc -c controle.c -o controle.o
	gcc -c main.c -o main.o
	gcc -c merge.c -o merge.o
	gcc -c listaAdvanced.c -o listaAdvanced.o
	gcc listaAdvanced.o main.o elevador.o lista.o controle.o merge.o -o exit

