#include "headers/lista.h"
#include "headers/gerador.h"
#include "headers/merge.h"
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
	pointer = l->begin;

	//Variáveis auxiliares para comparações no for
	int origin;
	origin  = 	pointer->demand.origem;
	int destiny;
	destiny =	pointer->demand.destino;
	while(pointer != NULL){
		
		if(origin >= posicao && origin <= destino){
			push(now,pointer->demand);
		
		}
		pointer = pointer->next;
		if(pointer != NULL){
			origin  = pointer->demand.origem;
			destiny = pointer->demand.destino; 
		}
			
	}
	if(isEmpety(now))
		return now;
	merge(now, 2);
	now->first = now->begin->demand.id;	
	merge(now, 0);

			
	return now;
}


Lista* generateDown(Lista* l, int posicao, int destino){
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
	
		if(origin <= posicao && destiny >= destino || pointer->demand.status == 1 && destiny <= destino){
			push(now,pointer->demand);
		}
		pointer = pointer->next;
		if(pointer != NULL){
			origin  = pointer->demand.origem;
			destiny = pointer->demand.destino; 
		}
	}
	merge(now, 2);
	now->first = now->begin->demand.id;

	merge(now, 0);
	return now;
	return now;
}

/*
	Atualiza Lista l com as operações realizadas em all
	Atualiza all removendo as solicitações já atendidas
*/
void crossing(Lista* l, Lista* all){
	
	//Ordena a lista de comparação pela id
	merge(all,2);

	//Nó auxiliar para percorrer all
	Node* pointer = createNode();
	pointer = all->begin;

	//Nó auxliar para percorrer l
	Node* aux = createNode();
	aux = l->begin;
	
	//Looping externo para percorrer all
	while(pointer != NULL){

		//Faz o ponteiro de l apontar para elemento de mesma id de all
		while(aux->demand.id != pointer->demand.id)
			aux = aux->next;

		//Atualiza o status de aux
		if(pointer->demand.status== 1){
			aux->demand.status = 1;
		}

		//Remove da lista l e da lista all solicitações já atendidas
		else if(pointer->demand.status == 2){
			pop(l,pointer->demand.id);
			pop(all, pointer->demand.id);

		}

		//Ponteiro da all vai pro próximo nó
		pointer = pointer->next;
	}

}