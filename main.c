#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include "headers/data.h"
#include "headers/impressao.h"

//-------------Main-------------//

int main(int argc, char *argv[]){

	//-------------Recebimento de Dados-------------//
		Dados dataInput;
		Elevador* e;
		Lista* l;
		Lista* est = createList();

		if (argc <= 1){

			printf("Há menos parâmetros que o necessário.\n");
			printf("	Falta estratégia de escalonamento (fcfs ou sjf)\n");
			return 0;
		}

		else if (strcmp(argv[1], "fcfs") && strcmp(argv[1], "sjf")) {
		
			printf("Nome da estrategia de escalonamento invalido. ");
			printf("Escolha 'fcfs' ou 'sjf'\n");
			return 0;
		}

		dataInput = recebedados(argc, argv);
	
		e = dataInput.elevador;
		l = dataInput.evento;
	
		//Orginiza l em ordem crescente de tempo
		l = generateTime(l);
		est = copyList(l);

		printLogo();
		printStatus(e);

		printf("Dados Recebidos:\n");
		printList(l);
	
	//-------------Operações sobre os dados-------------//
	
		/*
			First-Come First-Served
			A primeira Solicitação feita é a primeira atendida
		*/
		if (!strcmp(argv[1], "fcfs")) 
			fcfs(e, l, est);

		/*
			Shortest Job First
			A solicitação mais próxima tem prioridade
		*/
		else if (!strcmp(argv[1], "sjf"))
			sjf(e, l, est);

	//-------------Saída de dados-------------//
		printf("\nResultado:\n");
		printList(est);

		printf("\nSolicitações pendentes: %d\n", l->size);
		printList(l);
		printf("\n\n");
	
		printStatus(e);
	return 0;
}
