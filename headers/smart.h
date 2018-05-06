#ifndef SMART_H_INCLUDED
#define SMART_H_INCLUDED

void fcfs(Elevador* e, Lista* l, Lista* est);
void calculaDistancia(Elevador* e, Lista* l);
void sjf(Elevador* e, Lista* l, Lista* est); 
void sjf_funny(Elevador* e, Lista* l, Lista* est);
void sjf_boring(Elevador* e, Lista* l, Lista* est);
Node* shortest(Elevador* e, Lista* l);

#endif// !SMART_H_INCLUDED