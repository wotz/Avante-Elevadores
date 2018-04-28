#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/merge.h"
#include "headers/elevador.h"
#include "headers/gerador.h"
#include "headers/atende.h"
#include "headers/data.h"

int main(int argc, char *argv[]){
	Dados dataInput;
	Elevador e;
	Lista *l;
	if (strcmp(argv[2], "fcfs") && strcmp(argv[2], "sjf")) {
		printf("Nome da estrategia de escalonamento invalido. Escolha 'fcfs' ou 'sjf'\n");
		return 0;
	}
	dataInput = recebedados(argc, argv);
	
	e = dataInput.elevador;
	l = dataInput.evento;
	printf("\nLista de Solicitações:\n");
	printList(l);

	if (!strcmp(argv[2], "fcfs")) {

	}
	else if (!strcmp(argv[2], "sjf")) {

	}
	return 0;
}
