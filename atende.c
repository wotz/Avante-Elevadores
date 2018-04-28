#include "headers/lista.h"
#include "headers/gerador.h"
#include "headers/elevador.h"
#include "headers/merge.h"
#include "headers/atende.h"
#include <stdlib.h>
#include <stdio.h>


//Andar chato :(
void boringFloor(Elevador* e, Lista* l, Lista* all){
	Node* pointer = createNode();
	pointer = all->begin;

	while(pointer != NULL){
			if(pointer->demand.origem == e->posicao && pointer->demand.status == 0){
				
				if(e->capacidade - e->lotacao > 0){
					embarca(e);
					pointer->demand.status = 1;
				}
				
			}
			else if(pointer->demand.destino == e->posicao && pointer->demand.status == 1){
				pointer->demand.status = 2;
				desembarca(e);
			}
			pointer = pointer->next;
	}
}

//Andar divertido :)
void funnyFloor(Elevador* e, Lista* l, Lista* all, int andar){
	int opc;
	if(andar < e->posicao)
		opc = 0;

	else
		opc = 1;

	if(opc){
		for(int i = e->posicao; i < andar; i++){

			//Partezinha da animação
			printStatus(e);
			

			if(i == e->posicao)
				boringFloor(e, l, all);
			subir(e);
			boringFloor(e, l, all);
			
			//Partezinha da animação
			printStatus(e);
			int c = getchar();
		}
	}
	else{
		for(int i = e->posicao; i > andar; i--){
			//Partezinha da animação
			printStatus(e);
			
			
			if(i == e->posicao)
				boringFloor(e, l, all);
			descer(e);
			boringFloor(e, l, all);
			
			//Partezinha da animação
			printStatus(e);
			int c = getchar();
		}
	}
}


void go(Elevador* e, Lista* l, int andar){
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

	else if(andar < e->posicao)		
		all = generateDown(all, e->posicao, andar);
	
	
	printf("L antes de go:\n");
	printList(l);
	printf("All antes de funnyFloor\n");
	printList(all);
	int c = getchar();


	funnyFloor(e, l, all, andar);

	
	printf("L depois de funnyFloor:\n");
	printList(l);
	printf("All antes de crossing:\n");
	printList(all);
	crossing(l,all);
	printf("L depois de crossing:\n");
	printList(l);
	printf("All depois de crossing:\n");
	printList(all);
	
}

