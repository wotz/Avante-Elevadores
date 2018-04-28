#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/atende.h"
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
	int destino;
	while(!isEmpety(l)){
		calculaDistancia(e, l);//pensar em quando exatamente voltar a calcular a distancia[
		printList(l);
		destino = shortDemand(e,l);
		printf("estou na sjf %d\n", destino);
		go(e, l, destino);
	}
	
	//repetir várias vezes
}




void calculaDistancia(Elevador* e, Lista* l) {
	Node* pointer = l->begin;
	while (pointer != NULL) {
		
		if (pointer->demand.status == 0)
			pointer->demand.d = abs(pointer->demand.origem - e->posicao);
		
		else if (pointer->demand.status == 1)
			pointer->demand.d = abs(pointer->demand.destino - e->posicao);
		
		pointer = pointer->next;	
	}
}

int shortDemand(Elevador *e, Lista *l) {;


	Node *node = l->begin;
	

	int shortestDist = node->demand.d;//menor distancia começa como a do inicia da lista
	int destino;// = node->demand.distancia;//destino recebe a 
	

	if (node->demand.status == 0 && node->demand.tempo >= e->t)
		destino = node->demand.origem;
	

	else if (node->demand.status == 1 && node->demand.tempo >= e->t)
		destino = node->demand.destino;

	node = l->begin->next;
	while (node != NULL) {
		if (node->demand.d < shortestDist) {//pensar no que ocorre quando a distancia é igual.
			shortestDist = node->demand.d;


			if (node->demand.status == 0){
				destino = node->demand.origem;
			
			}
	
			else if (node->demand.status == 1){
			
				destino = node->demand.destino;
				
			}
		}
		node = node->next;
		int c = getchar();

	}
	return destino;
}

