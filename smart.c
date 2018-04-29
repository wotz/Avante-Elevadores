#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/atende.h"
#include "headers/merge.h"
#include "headers/smart.h"


void fcfs(Elevador* e, Lista* l){
	l = generateTime(l);
	printf("\n\n");
	printList(l);
	Node* node = createNode();
	node = l->begin;
	e->operacao = 0;
	while(!isEmpety(l)){
		if(node->demand.tempo <= e->tempo){
			atende(e, l, node);	
		}
		if(e->operacao == 0)
			e->tempo ++;
		node = l->begin;
	}
}


void sjf(Elevador* e, Lista* l){
	Lista *aux = createList();
	aux = copyList(l);
	Node* temp = createNode();
	int destino;
	while(!isEmpety(aux)){
	
		calculaDistancia(e, aux);
		
		temp = shortest(e,aux);
		
		destino = temp->demand.origem;
		
		if(destino == e->posicao || temp->demand.status == 1)
			destino = temp->demand.destino;
		
		go(e, aux, destino);
		if(!e->operacao)
			e->tempo++;
		

	}
	
	//repetir várias vezes
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

Node* shortest(Elevador* e, Lista* l){
	
	Node* aux = createNode();
	aux = l->begin;
	
	Node* node = createNode();
	node = l->begin;

	while(node != NULL){
		if(aux->demand.d > node->demand.d && node->demand.tempo <= e->tempo){
			aux = node;
		}

		//printNode(node);
		node = node->next;
	}

	return aux;
}