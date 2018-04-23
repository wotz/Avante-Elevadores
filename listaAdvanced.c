#include "lista.h"
#include "merge.h"
#include "elevador.h"
#include "listaAdvanced.h"
#include <stdio.h>
#include <stdlib.h>
/*
Gera todas as solicitações possiveis de serem atendidas ao se mover para o destino destino
ou seja
Retorna uma lista que contém todas as solicitações origem e destino dentro do intervalo
[posicao,destino]
Por enquanto só funciona para destino > posicao 
*/
Lista* generateNow(Lista* l, int posicao, int destino){
	//Nova lista para inserção das demandas passíveis de ser atendidas
	Lista* now = createList();
	
	//Ponteiro auxiliar para percorrer lista começando do begin
	Node* pointer = createNode();
	pointer 	  = l->begin;

	//Variáveis auxiliares para comparações no for
	int origin;
	origin  = 	pointer->demand.origem;
	int destiny;
	destiny =	pointer->demand.destino;

	for(int i = 1; i < l->size;i++){
		if(origin >= posicao && destiny <= destino && destiny >= posicao){
			push(now,pointer->demand);
		}
		pointer = pointer->next;
		origin  = pointer->demand.origem;
		destiny = pointer->demand.destino; 
	}
	return now;
}