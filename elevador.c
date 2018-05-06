#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/data.h"
#include <stdlib.h>
#include <stdio.h>
//-----Funções de Gerenciamento Simples de Elevador-----//

//-------------"Classe Elevador"-------------//

//-------------Constructor-------------//
Elevador* newElevador(int min, int max, int c){
	Elevador* e = (Elevador*)malloc(sizeof(Elevador));
	e->andarMin = min;//static
	e->andarMax = max;//static
	e->capacidade = c;//static
	e->tempo = 0;
	e->operacao = 0;
	e->lotacao = 0;
	e->deslocamento = 0;
	if(min <= 0 && max >= 0)
		e->posicao = 0;
	else
		e->posicao = min;
	return e;
}


//-------------Getters-------------//

int getAndarMin(Elevador* e){
	return e->andarMin;
}

int getAndarMax(Elevador* e){
	return e->andarMax;
}

int getCapacidade(Elevador* e){
	return e->capacidade;
}


int getTempo(Elevador* e){
	return e->tempo;
}

int getPosicao(Elevador* e){
	return e->posicao;
}

int getLotacao(Elevador* e){
	return e->lotacao;
}

int getOperacao(Elevador* e){
	return e->operacao;
}

int getDeslocamento(Elevador* e){
	return e->deslocamento;
}

//-------------Setters-------------//
void setTempo(Elevador* e){
	e->tempo++;
}

void setOperacao(Elevador* e, int operacao){
	e->operacao = operacao;
}



void setPosicao(Elevador* e, int o){
	e->deslocamento++;
	if(o){
		e->posicao++;
		setTempo(e);
	}
	else{
		e->posicao--;
		setTempo(e);
	}
}

void setLotacao(Elevador* e, int o){
	if(!getOperacao(e)){
		setTempo(e);
		setOperacao(e, 1);
	}
	if(o)
		e->lotacao++;
	else
		e->lotacao--;
}



//-------------Verificações Booleanas-------------//
int isFull(Elevador* e){
	if(getLotacao(e) == getCapacidade(e))
		return 1;
	else
		return 0;	
}


//-------------Entrada e Saída de pessoas-------------//
void embarca(Elevador* e, Lista* l, Lista* est, int id){
	Node* aux = createNode();
	aux = find(est, id);

	Node* node = createNode();
	node = find(l, id);

	if(!isFull(e) && aux->demand.status == 0){
		setLotacao(e, 1);
		aux->demand.status = 1;
		node->demand.status = 1;
		node->demand.momentoEmbarque = getTempo(e);
		aux->demand.momentoEmbarque = getTempo(e);
	}	
}

void desembarca(Elevador* e, Lista* l, Lista* est, int id){
	Node* aux = createNode();
	aux = find(est, id);


	if(aux->demand.status == 1){
		setLotacao(e, 0);
		aux->demand.status = 2;
		pop(l, id);
		aux->demand.momentoDesembarque = getTempo(e);
	}
}

//Para no andar e realiza operações de embarque e desembarque
void stop(Elevador* e, Lista* l, Lista* est){

	Node* aux  = est->begin;
	setOperacao(e, 0);
	
	//Primeiro desembarque todas as solicitações neste andar
	while(aux != NULL){
		if(aux->demand.status == 1 && aux->demand.destino == getPosicao(e))
			desembarca(e, l, est, aux->demand.id);	
		aux = aux->next;
	}

	//Agora embarque todas as solicitações possíveis neste andar
	aux = est->begin;
	while(aux != NULL){

		if(aux->demand.status == 0 && aux->demand.tempo <= getTempo(e) &&
		aux->demand.origem == getPosicao(e)){
			embarca(e, l, est, aux->demand.id);
		}
		
		aux = aux->next;
	}
}

//-------------Atendimento de Solicitações-------------//

//Vai para o destino destino
void go(Elevador* e, Lista* l, Lista* est, int destino){
	if(destino > e->posicao)
		goUp(e, l, est, destino);
	else if(destino < e->posicao)
		goDown(e, l, est, destino);
	else
		stop(e, l, est);
}

//Vai para cima
void goUp(Elevador* e, Lista* l, Lista* est, int destino){
	stop(e, l, est);
	while(getPosicao(e) != destino){
		setPosicao(e, 1);
		stop(e, l, est);
	}
	stop(e, l, est);
}

//Vai para baixo
void goDown(Elevador* e, Lista* l, Lista* est, int destino){
	stop(e, l, est);	
	while(getPosicao(e) != destino){
		setPosicao(e, 0);
		stop(e, l, est);
	}
	stop(e, l, est);
}