#include <stdio.h>
#include <stdlib.h>
#include "headers/lista.h"
#include "headers/merge.h"
#include "headers/elevador.h"
#include "headers/gerador.h"
#include "headers/atende.h"

int main(){
	Lista* l = createList();
	Elevador e = createElevador(0, 20,10);
	Demand demand;
	demand.id=1;
	demand.origem=18;
	demand.destino=2;
	demand.t=5;
	push(l,demand);
	
	demand.id=2;
	demand.origem=16;
	demand.destino=1;
	demand.t=6;
	push(l,demand);

	demand.id=3;
	demand.origem=8;
	demand.destino=5;
	demand.t=6;
	push(l,demand);

	demand.id=4;
	demand.origem=20;
	demand.destino=6;
	demand.t=13;
	push(l,demand);

	demand.id=5;
	demand.origem=19;
	demand.destino=13;
	demand.t=20;
	push(l,demand);

	demand.id=6;
	demand.origem=13;
	demand.destino=17;
	demand.t=21;

	demand.id=6;
	demand.origem=7;
	demand.destino=14;
	demand.t=21;
	push(l,demand);

	demand.id=7;
	demand.origem=9;
	demand.destino=18;
	demand.t=21;
	push(l,demand);

	demand.id=8;
	demand.origem=15;
	demand.destino=3;
	demand.t=21;
	push(l,demand);

	demand.id=9;
	demand.origem=17;
	demand.destino=8;
	demand.t=21;
	push(l,demand);

	demand.id=10;
	demand.origem=12;
	demand.destino=20;
	demand.t=21;
	push(l,demand);

	demand.id=11;
	demand.origem=3;
	demand.destino=17;
	demand.t=21;
	push(l,demand);

	demand.id=12;
	demand.origem=4;
	demand.destino=19;
	demand.t=21;
	push(l,demand);

	demand.id=13;
	demand.origem=10;
	demand.destino=16;
	demand.t=21;
	push(l,demand);

	go(&e, l, 18);
	return 0;
}