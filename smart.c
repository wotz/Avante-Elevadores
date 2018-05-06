 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include "headers/data.h"

/*	
	Função que controla o elevador conforme as regras da estratégia First-Come, First-Served
	Parâmetros:
		(Elevador*) @e -> elevador
		(Lista*) @l -> lista de solicitações
		(Lista*) @est -> lista usada para cálculos estatísticos
	Variáveis locais:
		(Node*) @node -> nó para percorrer a lista @l
	Retorna:
		Função do tipo vazio
*/
void fcfs(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = l->begin;

	int i = 0;
	while(!isEmpety(l)){
		i = 0;
		printNode(node);
		if(!isFull(e) && node->demand.tempo <= getTempo(e) && node->demand.status == 0){
			go(e, l, est, node->demand.origem);
			i = 1;
			node = l->begin;
		}
		else if(!isFull(e) && node->demand.status == 1){
			go(e, l, est, node->demand.destino);
			i = 1;
			node = l->begin;
		}
		else if(isFull(e)){
			while(node != NULL || i==0){
				if(node->demand.status == 1){
					go(e, l, est, node->demand.destino);
					i = 1;
					break;
				}		
				else
					node = node->next;
			}
			
			node = l->begin;
		}
		
		if(i == 0){
			setTempo(e);
		}
		
		
	}
}

/*	
	Função que controla o elevador conforme as regras da estratégia Shortest Job First
	Parâmetros:
		(Elevador*) @e -> elevador
		(Lista*) @l -> lista de solicitações
		(Lista*) @est -> lista usada para cálculos estatísticos
	Variáveis locais:
		(Lista*) @aux -> lista auxiliar usada para fazer operações e sofrer modificações. Ela recebe o conteúdo da lista @l.
		(Node*) @temp -> nó temporário que recebe o nó da solicitação mais próxima do elevador a cada repetição do loop
	Retorna:
		Função do tipo vazio
*/
void sjf(Elevador* e, Lista* l, Lista* est){
	while(!isEmpety(l)){
		if(!isFull(e))
			sjf_funny(e, l, est);
		else
			sjf_boring(e, l, est);
	}	
}

void sjf_funny(Elevador* e, Lista* l, Lista* est){
	
	Node* node = createNode();
	
	calculaDistancia(e, l);
	node = shortest(e, l);
	
	if(node->demand.tempo <= getTempo(e)){
		if(node->demand.status == 0){
			printNode(node);
			go(e, l, est, node->demand.origem);
		}
		else{
			go(e, l, est, node->demand.destino);
		}
	}
	else
		setTempo(e);	
}

void sjf_boring(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = l->begin;
	int distancia = abs(getAndarMax(e)) + abs(getAndarMin(e));
	int destino;
	calculaDistancia(e, l);
	
	while(node != NULL){

		if(node->demand.status == 1 && distancia > node->demand.d){
			distancia = node->demand.d;
			destino = node->demand.destino;
		}
		node = node->next;
	}	

	go(e, l, est, destino);
}

/*	
	Função que calcula a distância entre cada solicitação e a posição do elevador no instante em que é chamada
	Parâmetros:
		(Elevador*) @e -> elevador
		(Lista*) @l -> lista de solicitações
	Variáveis locais:
		(Node*) @pointer -> nó que percorre toda a lista @l
	Retorna:
		Função do tipo vazio
*/
void calculaDistancia(Elevador* e, Lista* l) {
	Node* pointer = l->begin;
	while (pointer != NULL) {
		/*
			Se for uma solicitação do tipo embarque, a distância é calculada em relação a origem da solicitação e o elevador,
			desde que a origem não seja na mesma posição do elevador. Neste caso é calculada em relção ao destino da solicitação.
		*/
		if (pointer->demand.status == 0){
			if(e->posicao == pointer->demand.origem)
				pointer->demand.d = abs(pointer->demand.destino - e->posicao);
			else
				pointer->demand.d = abs(pointer->demand.origem - e->posicao);
		}

		/*
			Se for uma solicitação do tipo desembarque, a distância é calculada em relação ao destino da solicitação e o elevador.
		*/
		else if (pointer->demand.status == 1)
			pointer->demand.d = abs(pointer->demand.destino - e->posicao);
		
		pointer = pointer->next;	
	}
}

/*	
	Função que encontra a solcitação com menor distância
	Parâmetros:
		(Elevador*) @e -> elevador
		(Lista*) @l -> lista de solicitações
	Variáveis locais:
		(Node*) @node -> nó que percorre toda a lista @l
		(Node*) @aux -> nó que percorre a lista @l até encontrar a menor distancia. Tem a função de auxiliar nas comparações.
	Retorna:
		Nó @aux encontrada
*/
Node* shortest(Elevador* e, Lista* l){
	
	Node* aux = createNode();
	aux = l->begin;
	
	Node* node = createNode();
	node = l->begin;

	while(node != NULL){
		if(aux->demand.d > node->demand.d && node->demand.tempo <= getTempo(e))
			aux = node;
		node = node->next;
	}

	return aux;
}