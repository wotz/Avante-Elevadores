#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include "headers/impressao.h"
#include <stdio.h>
#include <stdlib.h>

void fcfs(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = l->begin;

	int i = 0;
	while(!isEmpety(l)){
		i = 0;
		if(node->demand.tempo <= getTempo(e) && node->demand.status == 0){
			go(e, l, est, node->demand.origem);
			i = 1;
		}
		else if(node->demand.status == 1){
			go(e, l, est, node->demand.destino);
			i = 1;
		}
		if(i == 0){
			setTempo(e);
		}
		node = l->begin;
	}
}

void sjf(Elevador* e, Lista* l, Lista* est){
	while(!isEmpety(l)){
		if(!isFull(e))
			sjf_funny(e, l, est);
		else
			sjf_boring(e, l, est);

		printStatus(e);
		int c = getchar();
	}	
}

void sjf_boring(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = l->begin;
	int distancia = abs(getAndarMax(e)) + abs(getAndarMin(e));
	int destino;
	calculaDistancia(e, l);
	printList(l);
	while(node != NULL){

		if(node->demand.status == 1 && distancia > node->demand.d){
			printf("Eu perdi %d\n", distancia);
			printNode(node);
			distancia = node->demand.d;
			destino = node->demand.destino;
			printf("Para %d\n", distancia);
		}
		node = node->next;
	}	

	go(e, l, est, destino);
}

void sjf_funny(Elevador* e, Lista* l, Lista* est){
	
	Node* node = createNode();
	
	calculaDistancia(e, l);
	node = shortest(e, l);
	
	if(node->demand.tempo <= getTempo(e)){
		if(node->demand.status == 0){
			go(e, l, est, node->demand.origem);
		}
		else{
			go(e, l, est, node->demand.destino);
		}
	}
	else
		setTempo(e);	
}

Node* shortest(Elevador* e, Lista* l){
	
	Node* aux = createNode();
	aux = l->begin;
	
	Node* node = createNode();
	node = l->begin;

	while(node != NULL){
		if(aux->demand.d > node->demand.d && node->demand.tempo <= getTempo(e))
			aux = node;
		node = node->next;
	}

	return aux;
}

void calculaDistancia(Elevador* e, Lista* l) {
	Node* pointer = l->begin;
	while (pointer != NULL) {
		
		if (pointer->demand.status == 0){
			if(e->posicao == pointer->demand.origem)
				pointer->demand.d = abs(pointer->demand.destino - e->posicao);
			else
				pointer->demand.d = abs(pointer->demand.origem - e->posicao);
		}
		
		else if (pointer->demand.status == 1)
			pointer->demand.d = abs(pointer->demand.destino - e->posicao);
		
		pointer = pointer->next;	
	}
}