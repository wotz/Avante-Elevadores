all: 
	gcc -c lista.c -o lista.o
	gcc -c elevador.c -o elevador.o
	gcc -c merge.c -o merge.o
	gcc -c main.c -o main.o
	gcc -c gerador.c -o gerador.o
	gcc -c atende.c -o atende.o
	gcc lista.o elevador.o merge.o gerador.o atende.o main.o -o exit
