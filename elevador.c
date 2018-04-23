#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-----Funções de Gerenciamento Simples de Elevador-----//


//Cria e retorna um novo elevador
Elevador createElevador(int min, int max, int c){
	Elevador e;
	e.andarMin = min;
	e.andarMax = max;
	e.capacidade = c;
	e.lotacao=0;
	e.posicao=7;
	return e;
}


//Sobe um andar
int subir(Elevador *e){
	if(e->posicao < e->andarMax)
		e->posicao++;
	else
		exit(1);
}


//Desce um andar
int descer(Elevador *e){
	if(e->posicao > e->andarMin)
		e->posicao--;
	else
		exit(1);
}


//O elevador está cheio?
int isLotado(Elevador e){
	if(e.lotacao < e.capacidade)
		return 0;
	else 
		return 1;
}


//Simula a entrada de uma pessoa no elevador
int embarca(Elevador *e){
	if(!isLotado(*e)){
		e->lotacao++;
		return 1;
	}
	else return 0;
	
}


//Simula a saída de uma pessoa no elevador
void desembarca(Elevador *e){
	e->lotacao--;
}


//Imprime o status doo elevador
void printStatus (Elevador *e){
	printf("---Satanas Elevadores: %dº andar-----\n", e->posicao);
	printf("|	Andar Mín: %dº		    |\n",e->andarMin);
	printf("|	Andar Máx: %dº		    |\n",e->andarMax);
	printf("|	Capacidade Máx: %d 	    |\n",e->capacidade);
	printf("|	Lotacao atual: %d 	    |\n",e->lotacao);
	printf("-------------------------------------\n");
}

