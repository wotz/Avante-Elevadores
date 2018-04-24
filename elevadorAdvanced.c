#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void goTo(Elevador *e, int destino){
	int i = 0;
	int posicao = e->posicao;
	if(destino > posicao){
		for(i = posicao; i < destino; i++){
			system("clear");			
			printStatus(e);
			sleep(0.5);
			subir(e);		
		}
	}
	else if(destino < posicao){
		for(i = destino; i < posicao; i++){
			printStatus(e);
			sleep(0.5);
			system("clear");
			descer(e);			
		}
	}
}

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
				/*system("clear");			
				printStatus(e);
				printf("Embarcando\n");
				printNode(pointer);
				sleep(5);*/
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
				/*system("clear");			
				printStatus(e);
				printf("Desembarcando\n");
				printNode(pointer);
				sleep(5);
				desembarca(e);*/
				pointer->demand.status = 2;
				pop(l,pointer->demand.id);
			}
			//printNode(pointer);
			pointer = pointer->next;
		}
		pointer = all->begin;
		/*system("clear");			
		printStatus(e);
		sleep(1);
		subir(e);*/
		
		
	}
	/*printList(all);
	printf("\n\n");
	printList(l);*/

}

/*
system("clear");			
		printStatus(e);
		printNode(pointer);
		if(pointer->next != NULL)
			pointer = pointer->next;
		sleep(0.5);
		subir(e);		*/