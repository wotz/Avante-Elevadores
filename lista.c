/*
	Esta é uma lista simplesmente encadeada
*/
#include "headers.h"
#include <stdio.h>
#include <stdlib.h>

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
	Node* node = createNode();
	demand.status = 0;//Toda vez que for dado um push a demanda é pendente
	node->demand = demand;
	node->next = NULL;
	if(isEmpety(l)){
		l->begin = node;
		l->head = node;
		l->size++;
		return;
	}
	l->head->next = node;
	l->head = node;
	l->size++;
}


//Função que retira célula do começo da lista
void pop(Lista* l){

	if(l->size == 1){
		l->head = NULL;
		l->begin = NULL;
		l->size = 0;
		return;
	}
	Node* node = createNode();
	node = l->begin;
	l->begin = l->begin->next;
	free(node);
	l->size--;
}

void popAt(Lista* l,int id){

	Node* node = createNode();//no auxiliar para percorrer a lista
	node = find(l,id);
	
	Node* pointer = createNode();//guarda o no que tem que ser removido
	pointer  = l->begin;
	
	while(pointer->next != node)//percorre até o nó com id anterior a do nó buscado
		pointer = pointer->next;
	
	//se for remover o nó do fim da fila a l->head aponta pro nó anterior
	if(id == l->size && l->size>=2)
		l->head = pointer;
	
	pointer->next = node->next;//faz o nó anterior apontar pro próximo do nó desejado
	
	//se a id for o 1 e o tamanho for maior que 2 o begin passa apontar para o próximo no
	if(id == 1 && l->size>=2)
		l->begin = l->begin->next;
	
	free(node);
	l->size--;
}	

//Função que retira célula do fim da lista
void popEnd(Lista* l){
	if(l->size == 1){
		l->head = NULL;
		l->begin = NULL;
		l->size = 0;
		return;
	}
	Node* pointer = l->begin;
	Node* aux = createNode();
	while(pointer->next->next != NULL)
		pointer = pointer->next;
	aux = l->head;
	pointer->next = NULL;
	l->head = pointer;
	free(aux);
	l->size--;
}

//Imprime a lista
void printList(Lista* l){
	if(isEmpety(l))//verifica se a lista está vazia
		return;
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		printf("Id: %d Origem: %d Destino: %d\n", pointer->demand.id, pointer->demand.origem, pointer->demand.destino);
		pointer = pointer->next;
	}
}

//Retorna um nó com id id
Node* find(Lista* l,int id){
	Node* node = l->begin;
	int i =1;
	for(i = 1; i < l->size;i++){
		if(i == id)	
			return node;
		else{
			node = node->next;
			
		}
	}


	return NULL;
}

int findFloor(Lista* l,int andar){
	Node* node = l->begin;
	int i, busca, n = 0;
	busca = node->demand.origem;
	for(i = 1; i <= l->size;i++){
		if(andar == busca)
			n++;
		if(i != l->size){
			node = node->next;
			busca = node->demand.origem;
		}
	}
	return n;
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



//-----Merge Sort-----//

//Algoritmo obtido do site: https://ide.geeksforgeeks.org/index.php
void merge(Lista* l,int opt){
	mergeSort(&l->begin,opt);
	//Algoritmo que faz com que o head aponte para o fim da lista depois de aplicar o merge
	Node* pointer = createNode();
	pointer = l->begin; 
	while(pointer != NULL){
		if(pointer->next == NULL)
			l->head = pointer;
		pointer = pointer->next;
		
	}
}
void mergeSort(Node** beginPointer, int opt){
    Node* begin = *beginPointer;
    Node* a;
    Node* b;
    if ((begin == NULL) || (begin->next == NULL))
        return;

    frontBackSplit(begin, &a, &b); 


    mergeSort(&a, opt);
    mergeSort(&b, opt);

    *beginPointer = sortedMerge(a, b, opt);
}
Node* sortedMerge(Node* a,Node* b, int opt){
    Node* result = NULL;
    int x, y;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    //Escolha de condiçao: 0 para ordenar pela origem
   	if(opt == 0){
   		x = a->demand.origem;
   		y = b->demand.origem;
   	}
   	else{
		x = a->demand.destino;
   		y = b->demand.destino;
   	}

    if (x <= y){
        result = a;
        result->next = sortedMerge(a->next, b, opt);
    }
    else{
        result = b;
        result->next = sortedMerge(a, b->next, opt);
    }
    return(result);
}

void frontBackSplit(Node* source,Node** frontRef,Node** backRef){
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
    while (fast != NULL){
    	fast = fast->next;
    	if (fast != NULL){
        	slow = slow->next;
        	fast = fast->next;
    	}
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}


//-----Funções de gerenciamento Lógico da lista-----//


//Apaga todos os elementos com origem maior do que a posição p 
void generateUp(Lista* l, int p){
	Node* pointer = createNode();
	pointer = l->begin;
	int i = pointer->demand.origem;
	while(i < p){
		pop(l);
		pointer = pointer->next;
		i = pointer->demand.origem;
	}

}


//Apaga todos os elementos com origem menor do que a posição p 
void generateDown(Lista* l, int p){
	Node* pointer = createNode();
	pointer = l->head;
	int i = pointer->demand.origem;
	while(i > p){
		popEnd(l);
		pointer = l->head;
		i = pointer->demand.origem;
	}
}