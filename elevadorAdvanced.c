#include "headers/lista.h"
#include "headers/listaAdvanced.h"
#include "headers/elevador.h"
#include "headers/merge.h"
#include "headers/elevadorAdvanced.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void atende(Elevador* e, Lista* l,int destino){
	//Gera lista com solicitações passíveis de serem atendidas agora
	Lista* all = createList();
	all = copyList(l);
	merge(all,0);
	all = generate(all,e->posicao, destino);
	//Cria nó auxiliar para percorrer all
	Node* pointer = createNode();
	pointer = all->begin;

	Node* aux = createNode();

	for(int andar = e->posicao; andar <= destino; andar++){

		//Loop que verifica se temos solicitações para o andar andar
		while(pointer != NULL){
			
			//Solicitacoes por origem(embarque)
			if(andar == pointer->demand.origem){
				if(e->capacidade - 1 > 0)//Temos que guardar espaço para a primeira requisição
					embarca(e);
				pointer->demand.status = 1;//em atendimento
				aux = find(l,pointer->demand.id);
				if(aux != NULL)
					aux->demand.status = 1;
			}
			//Solicitacoes por destino(desembarque)
			if(andar == pointer->demand.destino && 
							pointer->demand.status == 1){
				desembarca(e);
				pointer->demand.status = 2;
				pop(l,pointer->demand.id);
			}
			//printNode(pointer);
			pointer = pointer->next;
		}
		pointer = all->begin;
		
	}
	merge(all, 2);
}

void atendeDown(Elevador* e, Lista* l,int destino){
	//Gera lista com solicitações passíveis de serem atendidas agora
	Lista* all = createList();
	all = copyList(l);
	merge(all,0);
	all = generateDown(all,e->posicao, destino);
	//Cria nó auxiliar para percorrer all
	Node* pointer = createNode();
	pointer = all->begin;

	Node* aux = createNode();

	for(int andar = e->posicao; andar >= destino; andar--){

		//Loop que verifica se temos solicitações para o andar andar
		while(pointer != NULL){
			
			//Solicitacoes por origem(embarque)
			if(andar == pointer->demand.origem){
				if(e->capacidade - 1 > 0)//Temos que guardar espaço para a primeira requisição
					embarca(e);
				pointer->demand.status = 1;//em atendimento
				aux = find(l,pointer->demand.id);
				if(aux != NULL)
					aux->demand.status = 1;
			}
			//Solicitacoes por destino(desembarque)
			if(andar == pointer->demand.destino && 
							pointer->demand.status == 1){
				desembarca(e);
				pointer->demand.status = 2;
				pop(l,pointer->demand.id);
			}
			//printNode(pointer);
			pointer = pointer->next;
		}
		pointer = all->begin;
		
	}
	merge(all, 2);
	popDone(all);
	printf("All:\n");
	printList(all);
}