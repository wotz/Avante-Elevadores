#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/impressao.h"
#include <stdio.h>
#include <stdlib.h>

//Imprime a lista
void printList(Lista* l){
	if(isEmpety(l))//verifica se a lista está vazia
		return;
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		printNode(pointer);
		pointer = pointer->next;
	}
}

//Imprime um nó
void printNode(Node* node){
	if(node != NULL){
		int tempoEspera = 0, tempoAtendimento = 0, tempoTotal = 0;
		/*
			Por Definição uma solicitação demora pelo menos duas unidade de tempo
			para ser atendida
		*/
		if(node->demand.momentoDesembarque != 0){
			tempoEspera = node->demand.momentoEmbarque - node->demand.tempo; 
			tempoTotal = node->demand.momentoDesembarque - node->demand.tempo;
			tempoAtendimento = tempoTotal - tempoEspera;
		}
		else if(node->demand.momentoEmbarque != 0){
			tempoEspera = node->demand.momentoEmbarque - node->demand.tempo; 
		}
		printf("Id: %.3d ", node->demand.id);
		printf("Origem: %.3d ", node->demand.origem);
		printf("Destino: %.3d ", node->demand.destino);
		printf("TO: %.3d ", node->demand.tempo);
		printf("TE: %.3d ", tempoEspera);
		printf("TA: %.3d ", tempoAtendimento);
		printf("TT: %.3d ", tempoTotal);
		printf("d: %d ", node->demand.d);
		printf("Status: %d \n", node->demand.status);
	}
	else
		exit(1);
}

//Imprime status do elevador
void printStatus (Elevador* e){
	printf("-------Acima e avante: %.2dº andar----\n", getPosicao(e));
	printf("|      Andar Mín: %.2dº              |\n",getAndarMin(e));
	printf("|      Andar Máx: %.2dº              |\n",getAndarMax(e));
	printf("|      Capacidade Máx: %.2d          |\n",getCapacidade(e));
	printf("|      Lotacao atual: %.2d           |\n",getLotacao(e));
	printf("|      Tempo atual: %.2d             |\n",getTempo(e));
	printf("------------------------------------\n");
}

//Imprime a logo do Acima e Avante Elevadores
void printLogo(){
	printf("\n\n");
	printf("-------------------Acima e Avante Elvadores-------------------\n");
	printf("|TO: momento de ocorrencia                                   |\n");
	printf("|TE: tempo ate o elvador chegar na solicitacao               |\n");
	printf("|TA: tempo que a pessoa passsa dentro do elevador            |\n");
	printf("|TT: tempo decorrido desde a solicitacao ate o atendimento   |\n");
	printf("--------------------------------------------------------------\n");
	printf("\n\n");
}