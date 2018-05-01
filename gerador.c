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
	if(l->size == 1){
		push(now, l->begin->demand);
		return now;
	}
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
	if(l->size == 1){
		push(now, l->begin->demand);
		return now;
	}
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
}

Lista* generateTime(Lista* l){
	int id = 1;
	//Faz uma lista auxiliar  
	Lista* aux = createList();
	//Ordena aux pelo tempo
	merge(l, 4);
	//Ponteiro para percorrer a l
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		pointer->demand.id = id;
		push(aux, pointer->demand);
		//anda pointer
		pointer = pointer->next;
		id++;
	}

	return aux;
}

/*
	Atualiza Lista l com as operações realizadas em all
	Atualiza all removendo as solicitações já atendidas
*/
void crossing(Lista* l, Lista* all, Lista* est){
	
	//Ordena a lista de comparação pela id
	merge(all,2);
	//Nó auxiliar para percorrer all
	Node* pointer = createNode();
	pointer = all->begin;

	//Nó auxliar para percorrer l
	Node* aux = createNode();
	aux = l->begin;

	//Nó auxliar para percorrer est
	Node* node = createNode();
	node = est->begin;
	
	//Looping externo para percorrer all
	while(pointer != NULL){

		//Faz o ponteiro de l apontar para elemento de mesma id de all
		while(aux->demand.id != pointer->demand.id)
			aux = aux->next;

		while(node->demand.id != pointer->demand.id)
			node = node->next;
		
		//Atualiza o status de aux
		if(pointer->demand.status== 1 && aux->demand.status == 0){
			aux->demand.status = 1;
			node->demand.momentoEmbarque = pointer->demand.momentoEmbarque;
		}

		//Remove da lista l e da lista all solicitações já atendidas
		else if(pointer->demand.status == 2 && aux->demand.status == 1){
			node->demand.momentoDesembarque = pointer->demand.momentoDesembarque;
			pop(l,pointer->demand.id);
			pop(all, pointer->demand.id);

		}

		//Ponteiro da all vai pro próximo nó
		pointer = pointer->next;
	}

}