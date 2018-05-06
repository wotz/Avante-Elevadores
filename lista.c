#include <stdio.h>
#include <stdlib.h>
#include "headers/lista.h"

//-------------Constructor-------------//
//Função que cria uma lista e retorna um ponteiro para área de memória alocada para mesma
Lista* createList(){
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->head = NULL;
	l->begin = NULL;
	l->size = 0;
}

//Cria um nó
Node* createNode(){
	Node* node = (Node*)malloc(sizeof(Node));
	return node;
}

//-------------Gerenciamento básico de Lista-------------//
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

//Retorna um nó com id id
Node* find(Lista* l, int id){

	Node* aux = createNode();
	aux = l->begin;	

	while(aux != NULL){

		if(aux->demand.id == id)
			return aux;
		
		aux = aux->next;
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

//A lista está vazia?
int isEmpety(Lista* l){
	return (l->size == 0);
}

//-------------Gerenciamento Avançado de Lista-------------//

//Gera uma lista ordenada pelo tempo
Lista* generateTime(Lista* l){
	int id = 1;
	//Faz uma lista auxiliar  
	Lista* aux = createList();
	//Ordena aux pelo tempo
	merge(l, 3);
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

//-------------Merge Sort-------------//

//Algoritmo obtido do site: https://ide.geeksforgeeks.org/index.php (adaptado)
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


Node* sortedMerge(Node* a, Node* b, int opt){
	/*(int) @opt -> opção de ordenação:
					   0: pela origem
					   1: pelo destino
					   2: pela distancia
					   3: pelo tempo
	*/				   
    Node* result = NULL;
    int x, y;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    switch(opt){

        //ordena pela origem
        case 0:
            x = a->demand.origem;
            y = b->demand.origem;
        break;
        
        //ordena pelo destino
        case 1:
            x = a->demand.destino;
            y = b->demand.destino;
        break;
        
        //ordena pela id
        case 2:
            x = a->demand.d;
            y = b->demand.d;
        break;

        //ordena pelo tempo
        case 3:
            x = a->demand.tempo;
            y = b->demand.tempo;
        break;
      
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
