#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include "headers/data.h"
#include "headers/impressao.h"

int main(int argc, char *argv[]){
	Dados dataInput;
	Elevador* e;
	Lista* l;
	Lista* est = createList();
	if (argc <= 1){
		printf("Há menos parâmetros que o necessário. Digite o nome do progama (./""nome_do_programa"")\n");
		printf("seguido do nome da estratégia de escalonamento (fcfs ou sjf).\n");
		return 0;
	}
	else if (strcmp(argv[1], "fcfs") && strcmp(argv[1], "sjf")) {
		printf("Nome da estrategia de escalonamento invalido. Escolha 'fcfs' ou 'sjf'\n");
		return 0;
	}
	dataInput = recebedados(argc, argv);
	
	e = dataInput.elevador;
	l = dataInput.evento;
	l = generateTime(l);
	est = copyList(l);
	printLogo();

	printStatus(e);
	
	printf("Dados Recebidos:\n");
	printList(l);
	
	if (!strcmp(argv[1], "fcfs")) 
		fcfs(e, l, est);
	else if (!strcmp(argv[1], "sjf"))
		sjf(e, l, est);
	
	printf("\nResultado:\n");
	printList(est);
	printf("\nSolicitações pendentes: %d\n", l->size);
	printList(l);
	printf("\n\n");
	printStatus(e);

	

	return 0;
}
