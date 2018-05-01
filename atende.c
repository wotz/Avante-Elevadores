#include "headers/lista.h"
#include "headers/gerador.h"
#include "headers/elevador.h"
#include "headers/merge.h"
#include "headers/atende.h"
#include <stdlib.h>
#include <stdio.h>
/*


void goDown(Elevador* e, Lista* l, Lista* est, int destino){
	while(getPosicao(e) != destino){
		stop(e);
		descer(e);
	}
	stop(e, l, est);

}



void stop(Elevador* e, Lista* l, Lista* est){
	merge(l, 2);
	Node* node = l->begin;
	Node* aux  = est->begin;
	
	while(node != NULL){

		node = node->next;
	}
}


void go(Elevador* e, Lista* l, Lista* est, int destino){
	
	if(destino > e->posicao)
		goUp();
	
	else if(destino < e->posicao)
		goDown();
	
	else
		stop();
}


Lista* onElevator(Lista* l){
	Lista* onElevator = createList();
	
	Node* node = createNode();
	node = l->begin;
	
	while(node != NULL){
		if(node->demand.id == 1)
			push(onElevator, demand);
		node = node->next;	
	}
	printList(onElevator);
	return onElevator;
}	

void update(Lista* origem, Lista* destino){

}

void entra(Elevador* e, Lista* l){

}

void sai(Elevador* e, Lista* l){

}

void goUp(Elevador* e, Lista* l, Lista* est, int destino){

}
*/