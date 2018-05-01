#include "headers/elevador.h"
#include <stdlib.h>
#include <stdio.h>
//-----Funções de Gerenciamento Simples de Elevador-----//


//Cria e retorna um novo elevador
Elevador* newElevador(int min, int max, int c){
	Elevador* e = (Elevador*)malloc(sizeof(Elevador));
	e->andarMin = min;//static
	e->andarMax = max;//static
	e->capacidade = c;//static
	e->tempo = 0;
	e->lotacao=0;
	e->posicao=7;
	return e;
}


//-------------Getters-------------//
int getTime(Elevador* e){
	return e->tempo;
}

int getPosicao(Elevador* e){
	return e->posicao;
}

int getCapacidade(Elevador* e){
	return e->capacidade;
}

int getLotacao(Elevador* e){
	return e->lotacao;
}

int getAndarMin(Elevador* e){
	return e->andarMin;
}

int getAndarMax(Elevador* e){
	return e->andarMax;
}

//-------------Setters-------------//
void setPosicao(Elevador* e, int o){
	if(o)
		e->posicao++;
	else
		e->posicao--;
}

void setLotacao(Elevador* e, int o){
	if(o)
		e->lotacao++;
	else
		e->lotacao--;
}


void setTempo(Elevador* e){
	e->tempo++;
}






