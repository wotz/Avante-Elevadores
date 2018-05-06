#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

struct dados {
	Elevador* elevador;
	Lista* evento;
};
typedef struct dados Dados;

struct output {
	double TeMedio;//tempo de espera médio
	double TaMedio;//tempo médio de viagem
	double TeDP;//desvio padrão do tempo de espera
	double TaDP;//desvio padrão do tempo de viagem
};
typedef struct output Output;

Dados recebedados(int argc,char **argv);
void saida_dados(Elevador* e, Lista* est);
void saidaTempo(long int timeInput, long int timeLogic, long int timeOutput);
void printList(Lista* l);
void printNode(Node* node);
void printStatus (Elevador* e);
void printLogo();

#endif// !DATA_H_INCLUDED