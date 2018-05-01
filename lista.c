#include <stdio.h>
#include <stdlib.h>
#include "headers/lista.h"
//-----Funções Básicas de Gerenciamento de Lista-----//


//Função que cria uma lista e retorna um ponteiro para área de memória alocada para mesma
Lista* createList(){
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->head = NULL;
	l->begin = NULL;
	l->size = 0;
}



//A lista está vazia?
int isEmpety(Lista* l){
	return (l->size == 0);
}


//Função que insere célula no fim da "Fila"
void push(Lista* l, Demand demand){
	Node* node = (Node*)malloc(sizeof(Node));
	node->demand = demand;
	node->next = NULL;
	if(isEmpety(l)){
		l->begin = node;
		l->head = node;
		l->first = 1;
		l->size++;
		return;
	}
	l->head->next = node;
	l->head = node;
	l->size++;
}


//Função pop  boladona
//Ressalto que o caralho da lista tem que tá ordenada pela id
void pop(Lista* l,int id){
	//Nó auxiliar para percorrer a lista, começa no begin
	Node* aux = createNode();
	aux = l->begin;
	
	//Nó a ser removido
	Node* toPop = createNode();
	toPop = find(l,id);

	//Remoção inválida: fecha na bruteza o programa
	if(toPop == NULL){
		exit(1);
	}

	//Se o tamanho da lista for 1 apaga a lista inteira
	else if(l->size == 1){
		free(l->begin);
		l->begin = NULL;
		l->head = NULL;
	}	

	//Remove do fim quando o tamanho da lista é maior que 2
	else if(l->head->demand.id == id && l->size >= 2){

		while(aux->next != toPop)
			aux = aux->next;
		aux->next = toPop->next;
		l->head = aux;
		free(toPop);

	}

	//Remove do começão quando o tamnho da lista é maior que 2
	else if(id == l->first && l->size >= 2){
		l->begin = l->begin->next;
		l->first = l->begin->demand.id;	
		free(aux);

	}
	//Remove do miolo quando o tamnho da lista é maior que 2
	else if(id > l->first && l->size > 2){
		while(aux->next != toPop)//Guarda o nó anterior ao nó desejado
			aux = aux->next;
		aux->next = toPop->next;
		free(toPop);
	}
	
	else if(l->size == 2){
		l->head = l->begin;
		free(toPop);
	}
	l->size--;//Diminui o tamnho da lista

}


//Imprime a lista
void printList(Lista* l){
	if(isEmpety(l))//verifica se a lista está vazia
		return;
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		printNode(pointer);
		pointer = pointer->next;
	}
}


//Retorna um nó com id id
Node* find(Lista* l,int id){
	Node* node = l->begin;
	int i =1;
	for(i = 1; i <= l->size;i++){
		if(node->demand.id == id)	
			return node;
		else{
			node = node->next;
		}
	}
	return NULL;
}

//Retorna uma nova lista que é cópia da recebida como parâmetro
Lista* copyList(Lista* l){
	Lista* new_l = createList();
	Node* pointer = createNode();
	Demand demand;
	pointer = l->begin;
	while(pointer){
		demand = pointer->demand;
		push(new_l,demand);
		pointer = pointer->next;
	}
	return new_l;
}


//Cria um nó
Node* createNode(){
	Node* node = (Node*)malloc(sizeof(Node));
	return node;
}

//Imprime um nó
void printNode(Node* node){
	if(node != NULL){
		int tempoEspera = 0, tempoAtendimento = 0, tempoTotal = 0;
		/*
			Por Definição uma solicitação demora pelo menos duas unidade de tempo
			para ser atendida
		*/
		if(node->demand.momentoDesembarque != 0){
			tempoEspera = node->demand.momentoEmbarque - node->demand.tempo; 
			tempoTotal = node->demand.momentoDesembarque - node->demand.tempo;
			tempoAtendimento = tempoTotal - tempoEspera;
		}
		printf("Id: %.3d ", node->demand.id);
		printf("Origem: %.3d ", node->demand.origem);
		printf("Destino: %.3d ", node->demand.destino);
		printf("TO: %.3d ", node->demand.tempo);
		printf("TE: %.3d ", tempoEspera);
		printf("TA: %.3d ", tempoAtendimento);
		printf("TT: %.3d \n", tempoTotal);

	}
	else
		exit(1);
}

