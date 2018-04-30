#include "headers/lista.h"
#include "headers/gerador.h"
#include "headers/elevador.h"
#include "headers/merge.h"
#include "headers/atende.h"
#include <stdlib.h>
#include <stdio.h>

//Andar chato :(
void boringFloor(Elevador* e, Lista* l, Lista* all, Lista* est){
	Node* pointer = createNode();
	pointer = all->begin;
	int istrue= 0;
	while(pointer != NULL){
		if(pointer->demand.origem == e->posicao && pointer->demand.status == 0 && 
			pointer->demand.tempo <= e->tempo){
		
			if(e->capacidade - e->lotacao > 0){
				//printNode(pointer);
				istrue = 1;//embarcou
				embarca(e);
				pointer->demand.status = 1;
			}
				
		}
		else if(pointer->demand.destino == e->posicao && pointer->demand.status == 1 && 
			pointer->demand.tempo <= e->tempo){
			istrue = 1;//desembarcou
			pointer->demand.status = 2;
			desembarca(e);
		}
			pointer = pointer->next;
	}
	if(istrue){
		e->operacao = 1;
		e->tempo++;
	}
	else 
		e->operacao = 0;
}

//Andar divertido :)
void funnyFloor(Elevador* e, Lista* l, Lista* all, Lista* est, int andar){
	int opc;
	if(andar < e->posicao)
		opc = 0;

	else
		opc = 1;
	if(opc){
		for(int i = e->posicao; i <= andar; i++){
			if(i == e->posicao)
				boringFloor(e, l, all, est);
			if(i != andar)
				subir(e);
			boringFloor(e, l, all, est);
		}
	}
	else{
		for(int i = e->posicao; i >= andar; i--){
			if(i == e->posicao)
				boringFloor(e, l, all, est);
				
			if(i != andar)
				descer(e);
			
			
			boringFloor(e, l, all, est);
		
		}
		
	}
	boringFloor(e, l, all, est);
}

void go(Elevador* e, Lista* l, Lista* est, int andar){
	Node* aux = createNode();
	aux = l->begin;
	
	if(e->posicao == andar){
		while (aux != NULL){

			if(aux->demand.origem == andar && aux->demand.status == 0 && 
				aux->demand.tempo <= e->tempo){
				if(e->capacidade - e->lotacao){
					aux->demand.status = 1;					
					embarca(e);
					if(!e->operacao)
						e->tempo++;
					e->operacao = 1;
				}
			}
			else if(aux->demand.destino == andar && aux->demand.status == 1){
				pop(l,aux->demand.id);
				desembarca(e);
				if(!e->operacao)
					e->tempo++;	
				e->operacao = 1;
			}
			aux = aux->next;
		}
		return;
	}
	
	//Faz de all uma cópia de l	
	Lista* all = createList();
	all = copyList(l);
	//Ordena all pela origem
	merge(all,0);
	
	/*
		Gera Lista com solicitações acima ou abaixo do elevador, dependendo do caso
	*/
	if(andar > e->posicao)
		all = generate(all, e->posicao, andar);

	else if(andar < e->posicao){
		all = generateDown(all, e->posicao, andar);
	}
	
	funnyFloor(e, l, all, est, andar);
	
	crossing(l,all);

}

void atende(Elevador* e, Lista* l, Lista* est, Node* node){
	if(node->demand.status != 1)
		go(e, l, est, node->demand.origem);
	
	go(e, l, est, node->demand.destino);
	
}