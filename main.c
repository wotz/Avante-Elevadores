#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(){
	Lista* l = createList();
	Lista* laux = createList();
	Elevador e = createElevador(0,10,10);

	Demand demand;
	demand.id=1;
	demand.origem=8;
	demand.destino=2;
	demand.t=5;
	push(l,demand);
	
	demand.id=2;
	demand.origem=6;
	demand.destino=0;
	demand.t=6;
	push(l,demand);

	demand.id=3;
	demand.origem=9;
	demand.destino=5;
	demand.t=6;
	push(l,demand);

	demand.id=4;
	demand.origem=4;
	demand.destino=6;
	demand.t=13;
	push(l,demand);

	demand.id=5;
	demand.origem=9;
	demand.destino=0;
	demand.t=20;
	push(l,demand);

	demand.id=6;
	demand.origem=3;
	demand.destino=1;
	demand.t=21;
	push(l,demand);
	merge(l,&l->begin,0);
	printList(l);
	
}
