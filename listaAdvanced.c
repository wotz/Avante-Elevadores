#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
/*
Gera todas as solicitações possiveis de serem atendidas ao se mover para o destino destino
ou seja
Retorna uma lista que contém todas as solicitações origem e destino dentro do intervalo
[posicao,destino]
Por enquanto só funciona para destino > posicao 
*/

Lista* generate(Lista* l, int posicao, int destino){
	//Nova lista para inserção das demandas passíveis de ser atendidas
	//Salva os atendimentos intermediarios
	Lista* now = createList();
	
	//Ponteiro auxiliar para percorrer lista começando do begin
	Node* pointer = createNode();
	pointer 	  = l->begin;

	//Variáveis auxiliares para comparações no for
	int origin;
	origin  = 	pointer->demand.origem;
	int destiny;
	destiny =	pointer->demand.destino;

	while(pointer != NULL){
		if(origin >= posicao && destiny <= destino){
			push(now,pointer->demand);
		}
		pointer = pointer->next;
		if(pointer != NULL){
			origin  = pointer->demand.origem;
			destiny = pointer->demand.destino; 
		}
	}
	return now;
}

void popDone(Lista* l){
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		if(pointer != NULL && pointer->demand.status == 2){
			pop(l, pointer->demand.id);
		}
		pointer = pointer->next;
	}
}