#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include <stdio.h>
#include <stdlib.h>

void fcfs(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = l->begin;

	int i = 0;
	while(!isEmpety(l)){
		i = 0;
		if(node->demand.tempo <= getTempo(e) && node->demand.status == 0){
			go(e, l, est, node->demand.origem);
			i = 1;
		}
		else if(node->demand.status == 1){
			go(e, l, est, node->demand.destino);
			i = 1;
		}
		if(i == 0){
			setTempo(e);
		}
		node = l->begin;
	}
}