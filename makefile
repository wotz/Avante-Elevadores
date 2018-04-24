all: 
	gcc -c lista.c -o lista.o
	gcc -c elevador.c -o elevador.o
	gcc -c main.c -o main.o
	gcc -c merge.c -o merge.o
	gcc -c listaAdvanced.c -o listaAdvanced.o
	gcc -c elevadorAdvanced.c -o elevadorAdvanced.o
	gcc lista.o elevador.o merge.o listaAdvanced.o elevadorAdvanced.o main.o -o exit
