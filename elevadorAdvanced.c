#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void goTo(Elevador *e, int destino){
	int i = 0;
	int posicao = e->posicao;
	if(destino > posicao){
		for(i = posicao; i < destino; i++){
			system("clear");			
			printStatus(e);
			sleep(0.5);
			subir(e);		
		}
	}
	else if(destino < posicao){
		for(i = destino; i < posicao; i++){
			printStatus(e);
			sleep(0.5);
			system("clear");
			descer(e);			
		}
	}
}

void atende(Elevador* e, Lista* l,int destino){
	//Gera lista com solicitações passíveis de serem atendidas agora
	Lista* impossible = createList();
	impossible = generateImpossible(l,e->posicao,destino);
	
	Lista* possible= createList();
	possible = generatePossible(l,e->posicao, destino);

	//Cria nó auxiliar para percorrer now
	Node* pointer = createNode();
	pointer = possible->begin;

	//Variáveis auxiliares para guarda origem e destino do pointer
	int origin;
	origin  = pointer->demand.origem;
	int destiny;
	destiny = pointer->demand.destino;

	for(int andar = e->posicao; andar <= destino; andar++){

		//Loop que verifica se temos solicitações para o andar andar
		while(pointer != NULL){
			
			//Solicitacoes por origem(embarque)
			if(andar == pointer->demand.origem){
				if(e->capacidade - 1 > 0)//Temos que guardar espaço para a primeira requisição
					embarca(e);
				pointer->demand.status = 1;//em atendimento
			}
			//Solicitacoes por destino(desembarque)
			else if(andar == pointer->demand.destino){
				desembarca(e);
				pointer->demand.status = 2;
				pop(l,pointer->demand.id);
			}
			//printNode(pointer);
			pointer = pointer->next;
		}
		pointer = possible->begin;
		/*system("clear");			
		printStatus(e);
		sleep(0.2);
		subir(e);*/
	}
	pointer = possible->begin;
	printf("\n\n\n");
	while(pointer != NULL){
		printNode(pointer);
		pointer = pointer->next;
	}

}


/*
system("clear");			
		printStatus(e);
		printNode(pointer);
		if(pointer->next != NULL)
			pointer = pointer->next;
		sleep(0.5);
		subir(e);		*/