#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dados recebedados(int argc, char **argv)
{
	Dados conjuntoentrada;
	int andarMin, andarMax, capacidade;
	int tempo, origem, destino, id = 0;

	FILE *arquivoElevador;
	FILE *arquivoEventos;

	Elevador elevador;
	Lista* evento;
	Demand demand;

	printf("Quantidade de parametros: %d\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo do ambiente do elevador: %s\n", argv[1]);
	printf("Estrategia de alocacao: %s\n", argv[2]);
	printf("Arquivo de eventos: %s\n", argv[3]);
	/**************************************************************************************************/
	arquivoElevador = fopen(argv[1], "r");
	if (arquivoElevador == NULL)
		printf("ERRO: Nao foi possivel abrir o arquivo do ambiente de elevador\n");
	else {
		fscanf(arquivoElevador, "%d %d\n", &andarMin, &andarMax);
		fscanf(arquivoElevador, "%d\n", &capacidade);
	}
	elevador = createElevador(andarMin, andarMax, capacidade);
	printf("Parametros do elevador - Andar Mínimo: %d Andar Máximo: %d Capacidade: %d\n", andarMin, andarMax, capacidade);
	fclose(arquivoElevador);
	
	evento = createList();
	
	arquivoEventos = fopen(argv[3], "r");
	if (arquivoEventos == NULL)
		printf("ERRO: Nao foi possivel abrir o arquivo que descreve os eventos\n");
	else {
		while (fscanf(arquivoEventos, "%d %d %d\n", &tempo, &origem, &destino) != EOF) {
			if(origem != destino){
				id++;
				demand.status = 0;
				demand.id = id;
				demand.origem = origem;
				demand.destino = destino;
				demand.t = tempo;
				demand.distancia = 0;
				push(evento, demand);	
			}
			
		}
	}
	fclose(arquivoEventos);

	conjuntoentrada.elevador = elevador;
	conjuntoentrada.evento = evento;
	return conjuntoentrada;
}
