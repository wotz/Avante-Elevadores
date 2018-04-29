#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/atende.h"
#include "headers/merge.h"
#include "headers/smart.h"


void fcfs(Elevador* e, Lista* l){
	Node* node = createNode();
	node = l->begin;
	while(!isEmpety(l)){
		atende(e, l, node);
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
		
		printList(aux);
		go(e, aux, destino);
		printList(aux);
		int c = getchar();
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
		if(aux->demand.d > node->demand.d){
			aux = node;
		}

		//printNode(node);
		node = node->next;
	}

	return aux;
}



































Node* shortDemand(Elevador *e, Lista *l) {;
	Node* node = l->begin;
	Node* aux = createNode();

	int shortestDist = node->demand.d;//menor distancia começa como a do inicia da lista
	int destino;// = node->demand.distancia;//destino recebe a 
	
	if (node->demand.status == 0 )//&& node->demand.tempo >= e->t
		destino = node->demand.origem;
	else if (node->demand.status == 1 )//&& node->demand.tempo >= e->t)
		destino = node->demand.destino;

	node = l->begin->next;
	printf("shortDemand\n");
	while (node != NULL) {
		if (node->demand.d < shortestDist){
			shortestDist = node->demand.d;

			if (node->demand.status == 0){
				destino = node->demand.origem;

			}
			else if (node->demand.status == 1){
			
				destino = node->demand.destino;
				
			}
			printf("\n\n");
			printNode (aux);
			printf("\n\n");
			aux = node;
		}
		node = node->next;

	}
	printf("Retorna: ");
	printNode(aux);
	return aux;
}