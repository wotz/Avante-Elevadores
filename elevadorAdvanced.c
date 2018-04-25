#include "headers/lista.h"
#include "headers/listaAdvanced.h"
#include "headers/elevador.h"
#include "headers/merge.h"
#include "headers/elevadorAdvanced.h"
#include <stdlib.h>
#include <stdio.h>
void middleFloor(Elevador* e, Lista* l, Lista* all, Node* pointer, int andar){
	//Nó para colocar as solicitações de @l em atendimento
	Node* aux = createNode();

	while(pointer != NULL){
			
		//Solicitacoes por origem(embarque)
		if(andar == pointer->demand.origem){

					//Temos que guardar espaço para a primeira requisição
			if(e->capacidade - 1 > 0)
				embarca(e);

			//Coloca solicitacao em all em atendimento
			pointer->demand.status = 1;
				
			//Coloca solicitacao em l em atendimento
			aux = find(l,pointer->demand.id);
			if(aux != NULL)
				aux->demand.status = 1;

		}

		//Solicitacoes por destino(desembarque)
		if(andar == pointer->demand.destino && pointer->demand.status == 1){
			desembarca(e);
			pointer->demand.status = 2;
			pop(l,pointer->demand.id);
		}

		pointer = pointer->next;
	}
}

void atendeMiolo(Elevador* e,Lista* l, Lista* all, int destino, int opc){
	//Cria nó auxiliar para percorrer @all
	Node* pointer = createNode();
	pointer = all->begin;

	
	if(opc == 1){
		for(int andar = e->posicao; andar <= destino; andar++){

			//Loop que verifica se temos solicitações para o andar andar
			middleFloor(e, l, all, pointer, andar);
			if(andar != destino)
				subir(e);
			pointer = all->begin;	
		}
	}
	else{
		for(int andar = e->posicao; andar >= destino; andar--){

			//Loop que verifica se temos solicitações para o andar andar
			middleFloor(e, l, all, pointer, andar);
			if(andar != destino)
				descer(e);
			pointer = all->begin;	
		}

	}
}

void atende(Elevador* e, Lista* l, Node* node){
	int destino = node->demand.origem;	
	for(int i = 0; i < 2; i++){
		int opc;
		if(e->posicao <= destino)
			opc = 1;
		else
			opc = 0;
		//Faz de @all uma cópia de @l
		Lista* all = createList();
		all = copyList(l);
	
		//Ordena a @all pela origem
		merge(all,0);

		//Gera lista com solicitações passíveis de serem atendidas agora
		if(opc == 1 )
			all = generate(all,e->posicao, destino);
		else if(opc == 0)
			all = generateDown(all, e->posicao, destino);

		atendeMiolo(e, l, all, destino,opc);
		destino = node->demand.destino;
	}
}