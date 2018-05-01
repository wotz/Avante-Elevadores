//-------------Smart-------------//

//-------------Metodos Principais-------------//

void fcfs(Elevador* e, Lista* l, Lista* est);

void sjf(Elevador* e, Lista* l, Lista* est); 

//-------------Metodos Auxiliares FCFS-------------//

void fcfsFull(Elevador* e, Lista* l, Lista* est);

void fcfsNotFull(Elevador* e, Lista* l, Lista* est);

//-------------Metodos Auxiliares SJF-------------//

void sjf_full(Elevador* e, Lista* l, Lista* est);

void sjfNotFull(Elevador* e, Lista* l, Lista* est);

Node* shortest(Elevador* e, Lista* l);

void calculaDistancia(Elevador* e, Lista* l);


