#include "headers/lista.h"
#include "headers/elevador.h"
#include <stdlib.h>
#include <stdio.h>

//-------------"Classe Elevador"-------------//

//-------------Constructor-------------//
Elevador* newElevador(int min, int max, int c){
	Elevador* e = (Elevador*)malloc(sizeof(Elevador));
	e->andarMin = min;//static
	e->andarMax = max;//static
	e->capacidade = c;//static
	e->tempo = 0;
	e->operacao = 0;
	e->lotacao=0;
	e->posicao=7;
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

//-------------Setters-------------//
void setTempo(Elevador* e){
	e->tempo++;
}

int setOperacao(Elevador* e){
	e->operacao = !e->operacao;
}



void setPosicao(Elevador* e, int o){
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
		setOperacao(e);
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
	Node* node = createNode();
	node = find(l, id);
	
	Node* aux = createNode();
	aux = find(est, id);


	if(!isFull(e) && node->demand.status == 0){
		setLotacao(e, 1);
		node->demand.status = 1;
		
		aux->demand.status = 1;
		aux->demand.momentoEmbarque = getTempo(e);
	}
}

void desembarca(Elevador* e, Lista* l, Lista* est, int id){
	Node* aux = createNode();
	aux = find(est, id);


	if(!isFull(e) && aux->demand.status == 0){
		setLotacao(e, 0);
		aux->demand.status = 2;
		pop(l, id);
		aux->demand.momentoDesembarque = getTempo(e);
	}
}


void stop(Elevador* e, Lista* l, Lista* est){
	Node* aux  = est->begin;

	//Primeiro desembarque todas as solicitações neste andar
	while(aux != NULL){
		if(aux->demand.status == 1 && aux->demand.destino == getPosicao(e))
			desembarca(e, l, est, aux->demand.id);
		aux = aux->next;
	}

	//Agora embarque todas as solicitações possíveis neste andar
	aux = est->begin;
	while(aux != NULL){

		if(aux->demand.status == 0 && aux->demand.tempo == getTempo(e) &&
		aux->demand.destino == getPosicao(e))
			embarca(e, l, est, aux->demand.id);
		aux = aux->next;
	}
	
	
}

//-------------Atendimento de Solicitações-------------//
/*
void go(Elevador* e, Lista* l, Lista* est, int destino){
	
	if(destino > e->posicao)
		//goUp();
	
	else if(destino < e->posicao)
		//goDown();
	
	else
		//stop();
}


void goUp(Elevador* e, Lista* l, Lista* est, int destino){

}

/*
void goDown(Elevador* e, Lista* l, Lista* est, int destino){
	while(getPosicao(e) != destino){
		stop(e);
		descer(e);
	}
	stop(e, l, est);

}



*/





void update(Lista* origem, Lista* destino){

}




//Imprime o status doo elevador
void printStatus (Elevador *e){
	printf("---Satanas Elevadores: %dº andar-----\n", getPosicao(e));
	printf("|	Andar Mín: %dº		    |\n",e->andarMin);
	printf("|	Andar Máx: %dº		    |\n",e->andarMax);
	printf("|	Capacidade Máx: %d 	    |\n",e->capacidade);
	printf("|	Lotacao atual: %d 	    |\n",e->lotacao);
	printf("|       Tempo atual: %d              |\n",e->tempo);
	printf("-------------------------------------\n");
}

/*
Lista* onElevator(Lista* l){
	Lista* onElevator = createList();
	
	Node* node = createNode();
	node = l->begin;
	
	while(node != NULL){
		if(node->demand.id == 1)
			push(onElevator, demand);
		node = node->next;	
	}
	printList(onElevator);
	return onElevator;
}	

*/