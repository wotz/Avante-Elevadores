#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

//---Lista.h---///
typedef struct solicitacao{
	int origem;
	int destino;
	int id;
	int tempo;//Tempo de ocorrência
	int momentoEmbarque;
	int momentoDesembarque;
	int status;//0: aguardando, 1: em viagem, 2: atendido
	int d;
}Demand;

typedef struct node{
	Demand demand;
	struct node* next;
	struct node* prev;
}Node;

typedef struct lista{
	int size;
	int first;
	Node* head;
	Node* begin;
}Lista;

//-------------Constructor-------------//
Lista* createList();
Node* createNode();

//-------------Gerenciamento básico de Lista-------------//
void push(Lista* l, Demand demand);
void pop(Lista* l,int id);
Node* find(Lista* l,int id);
Lista* copyList(Lista* l);
int isEmpety(Lista* l);

//-------------Gerenciamento Avançado de Lista-------------//
Lista* generateTime(Lista* l);

//-------------Merge Sort-------------//
void merge(Lista* l,int opt);
void mergeSort(Node** beginPointer, int opt);
void frontBackSplit(Node* source,Node** frontRef,Node** backRef);
Node* sortedMerge(Node* a,Node* b, int opt);

#endif //!LISTA_H_INCLUDED