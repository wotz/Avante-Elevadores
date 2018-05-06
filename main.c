#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/data.h"
#include "headers/estatistica.h"
#include "headers/smart.h"

/********************************************************************************************************
Desenvolvedores: Lucas Hélio e Juliano Balcante
Início de desenvolvimento: 11/04/2018
Última versão: 03/05/2018

Este programa foi desenvolvido para simular o funcionamento de um elevador conforme duas estratégias de
escalonamento: FCFS (First-Come, First Served) E SJF (Shortest Job First). 
********************************************************************************************************/
int main(int argc, char *argv[]){

	Dados dataInput;
	Elevador* e;
	Lista* l;
	Lista* est = createList();
	if (argc != 4 ){
		printf("\nERRO 1: Há menos parâmetros que o necessário\n");
		printf("Digite a entrada na linha de comando seguinte formato: ./nomePrograma ArqElevador <fcfs,sjf> ArqEventos\n");
		printf("Onde ArqElevador: arquivo do ambiente do elevador\n     ArqEventos: arquivo de eventos\n");
		return 0;
	}
	else if (strcmp(argv[2], "fcfs") && strcmp(argv[2], "sjf")) {
		printf("\nERRO 2: Nome da estrategia de escalonamento invalido. Escolha 'fcfs' ou 'sjf'\n");
		return 0;
	}
	
	dataInput = recebedados(argc, argv);
	
	e = dataInput.elevador;
	l = dataInput.evento;
	l = generateTime(l);
	est = copyList(l);
	
	printf("saí do meger \n");
	if (!strcmp(argv[2], "fcfs")) 
		fcfs(e,l, est);
	else if (!strcmp(argv[2], "sjf"))
		sjf(e, l, est);


	//Saida de dados

	saida_dados(e, est);



	return 0;
}