#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/atende.h"
#include "headers/merge.h"
#include "headers/gerador.h"
#include "headers/smart.h"
/*

void fcfs(Elevador* e, Lista* l, Lista* est){
	l = generateTime(l);
	Node* node = createNode();
	node = l->begin;
	e->operacao = 0;
	while(!isEmpety(l)){
		if(node->demand.tempo <= e->tempo){
			atende(e, l, est, node);	
		}
		if(e->operacao == 0)
			e->tempo ++;
		node = l->begin;
	}
}




void calculaDistancia(Elevador* e, Lista* l) {
	Node* pointer = l->begin;
	while (pointer != NULL) {
		
		if (pointer->demand.status == 0){
			if(e->posicao == pointer->demand.origem)
				pointer->demand.d = abs(pointer->demand.destino - e->posicao);
			else
				pointer->demand.d = abs(pointer->demand.origem - e->posicao);
		}
		
		else if (pointer->demand.status == 1)
			pointer->demand.d = abs(pointer->demand.destino - e->posicao);
		
		pointer = pointer->next;	
	}
}
*/