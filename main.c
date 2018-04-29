#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/merge.h"
#include "headers/elevador.h"
#include "headers/gerador.h"
#include "headers/atende.h"
#include "headers/data.h"
#include "headers/smart.h"


int main(int argc, char *argv[]){
	Dados dataInput;
	Elevador e;
	Lista* l;
	if (strcmp(argv[1], "fcfs") && strcmp(argv[1], "sjf")) {
		printf("Nome da estrategia de escalonamento invalido. Escolha 'fcfs' ou 'sjf'\n");
		return 0;
	}
	dataInput = recebedados(argc, argv);
	
	e = dataInput.elevador;
	l = dataInput.evento;

	if (!strcmp(argv[1], "fcfs")) {
		fcfs(&e, l);
	}
	else if (!strcmp(argv[1], "sjf")) {
		Node* node = createNode();
		node = NULL;
		calculaDistancia(&e, l);
		printList(l);
		node = shortest(&e, l);
		printNode(node);
	}

	return 0;
}
