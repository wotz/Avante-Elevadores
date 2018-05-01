//-------------Lista Simplesmente Encadeada-------------//

//-------------Struct Demand-------------//

typedef struct solicitacao{
	int origem;
	int destino;
	int id;
	int tempo;//Tempo de ocorrência
	int momentoEmbarque;
	int momentoDesembarque;
	int tipo;//embarque ou desembarque
	int status;//pensei em 0: esperando, 1:em viagem, 2: atendido
	int d;
}Demand;

//-------------Struct Node-------------//

typedef struct node{
	Demand demand;
	struct node* next;
	struct node* prev;
}Node;

//-------------Struct Lista-------------//

typedef struct lista{
	int size;
	int first;
	Node* head;
	Node* begin;
}Lista;



//-------------Constructors-------------//
Lista* createList();
Node* createNode();

//-------------Essenciais de Lista-------------//

void pop(Lista* l,int id);

void push(Lista* l, Demand demand);

//-------------Auxiliares-------------//

Lista* copyList(Lista* l);

Node* find(Lista* l,int id);

Lista* generateTime(Lista* l);

int isEmpety(Lista* l);


//-------------Merge Sort-------------//

void merge(Lista* l,int opt);

void mergeSort(Node** beginPointer, int opt);

void frontBackSplit(Node* source,Node** frontRef,Node** backRef);

Node* sortedMerge(Node* a,Node* b, int opt);






