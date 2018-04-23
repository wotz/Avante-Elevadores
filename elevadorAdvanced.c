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

	/*for(int andar = e->posicao; andar <= destino; andar++){
		system("clear");			
		printStatus(e);
		printNode(pointer);
		if(pointer->next != NULL)
			pointer = pointer->next;
		sleep(0.5);
		subir(e);		
		
	}
	system("clear");
	printStatus(e);
*/
	printf("possible:\n");
	printList(possible);
	printf("\nImpossible:\n");
	printList(impossible);
	
}
