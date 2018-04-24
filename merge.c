#include "headers/lista.h"
#include "headers/merge.h"
#include <stdio.h>
#include <stdlib.h>
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
   	else if(opt == 1){
		x = a->demand.destino;
   		y = b->demand.destino;
   	}
    else{
        x = a->demand.id;
   		y = b->demand.id;
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
