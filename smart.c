#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/smart.h"
#include "headers/impressao.h"
#include <stdio.h>
#include <stdlib.h>
//-------------Smart-------------//

//-------------Metodos Principais-------------//

void fcfs(Elevador* e, Lista* l, Lista* est){

	Node* node = createNode();
	node = l->begin;

	int i = 0; //verifica se o tempo tempo foi atualizado
	while(!isEmpety(l)){
		if(!isFull(e)){
			fcfsNotFull(e, l, est);
			printf("minha marca\n");
			int c = getchar();
		}
		else{
			printf("não é minha marca\n");
			fcfsFull(e, l, est);
		}
		
		node = l->begin;
	}
}

void sjf(Elevador* e, Lista* l, Lista* est){

	while(!isEmpety(l)){
		
		if(!isFull(e))
			sjfNotFull(e, l, est);
		
		else
			sjf_full(e, l, est);
	}	
}
//-------------Metodos Auxiliares FCFS-------------//

//Caso em que o elevador lota
void fcfsFull(Elevador* e, Lista* l, Lista* est){
	Node* node = createNode();
	node = est->begin;
	
	int destino, b = 1;
	
	//Escolhe a solicitação de id menor já dentro do elevador
	while(b){
		
		if(node->demand.status == 1){
			printf("deu ruim aqui\n");
			b = 0; //sai do loop
			destino = node->demand.destino;
		}
	}
	//Atende a solicitação escolhida
	go(e, l, est, destino);
}

//(getCapacidade(e) - getLotacao(e)) >= 1
void fcfsNotFull(Elevador* e, Lista* l, Lista* est){
	int b = 0;//guarda se foi realizada alguma movimentação no elevador

	Node* node = createNode();
	node = l->begin;


	//Se a demanda tiver status pendente vá para sua origem
	if(node->demand.tempo <= getTempo(e) && node->demand.status == 0){
			
		go(e, l, est, node->demand.origem);
		b = 1;
	}

	//Se a demanda tiver status em atendimento vá para o destino dela
	else if(node->demand.status == 1){	
		go(e, l, est, node->demand.destino);
		b = 1;
	}
	if(b == 0)		
		setTempo(e);
	
}

//-------------Metodos Auxiliares SJF-------------//

//Elevador Lotado
void sjf_full(Elevador* e, Lista* l, Lista* est){
	
	Node* node = createNode();
	node = l->begin;
	
	// Distancia superior a máxima
	int distancia = abs(getAndarMax(e)) + abs(getAndarMin(e))+1;
	int destino;
	
	calculaDistancia(e, l);

	//Escolhe a solicitação com menor distancia dentro do elevador
	while(node != NULL){

		if(node->demand.status == 1 && distancia > node->demand.d){
			
			distancia = node->demand.d;
			destino = node->demand.destino;
		}

		node = node->next;
	}	

	//Atende essa solicitação
	go(e, l, est, destino);
}

//O elevador não está lotado
void sjfNotFull(Elevador* e, Lista* l, Lista* est){
	
	Node* node = createNode();
	
	calculaDistancia(e, l);
	node = shortest(e, l);
	
	//Quando houver demanda, atenda-a
	if(node->demand.tempo <= getTempo(e))

		if(node->demand.status == 0)
			go(e, l, est, node->demand.origem);
		
		else
			go(e, l, est, node->demand.destino);
		
	
	else
		setTempo(e);	
}

//Calcula a demanda mais Próxima
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

//Calcula a distancia de cada solicitaçao até o elevador
void calculaDistancia(Elevador* e, Lista* l) {
	Node* pointer = l->begin;
	while (pointer != NULL) {
		
		if (pointer->demand.status == 0)

			if(e->posicao == pointer->demand.origem)
				pointer->demand.d = abs(pointer->demand.destino - e->posicao);

			else
				pointer->demand.d = abs(pointer->demand.origem - e->posicao);
		
		else if (pointer->demand.status == 1)
			pointer->demand.d = abs(pointer->demand.destino - e->posicao);
		
		pointer = pointer->next;	
	}
}




