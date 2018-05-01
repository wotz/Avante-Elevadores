#include "elevador.h"

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

