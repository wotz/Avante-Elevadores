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
	Lista* est = createList();
	if (argc <= 1){
		printf("Há menos parâmetros que o necessário. Digite o nome do progama (./""nome_do_programa"")\nseguido do nome da estratégia de escalonamento (fcfs ou sjf).\n");
		return 0;
	}
	else if (strcmp(argv[1], "fcfs") && strcmp(argv[1], "sjf")) {
		printf("Nome da estrategia de escalonamento invalido. Escolha 'fcfs' ou 'sjf'\n");
		return 0;
	}
	dataInput = recebedados(argc, argv);
	
	e = dataInput.elevador;
	l = dataInput.evento;
	est = dataInput.evento;
	printf("Lista l:\n");
	printList(l);

	if (!strcmp(argv[1], "fcfs")) 
		fcfs(&e,l, est);
	else if (!strcmp(argv[1], "sjf"))
		sjf(&e, l, est);

	return 0;
}
