//---Lista Duplamente Encadeada---///
typedef struct solicitacao{
	int origem;
	int destino;
	int id;
	int t;
	int tipo;//embarque ou desembarque
	int status;//pensei em 0: esperando, 1:em viagem, 2: atendido
}Demand;

typedef struct node{
	Demand demand;
	struct node* next;
	struct node* prev;
}Node;

typedef struct lista{
	int size;
	Node* head;
	Node* begin;
}Lista;

Lista* createList();
Lista* copyList(Lista* l);
Node* createNode();
Node* sortedMerge(Node* a,Node* b, int opt);
Node* find(Lista* l,int id);
int findFloor(Lista* l, int );
int isEmpety(Lista* l);
void push(Lista* l, Demand demand);
void printList(Lista *l);
void pop(Lista* l);
void popAt(Lista *l, int id);
void popEnd(Lista* l);
void merge(Lista* l,int opt);
void mergeSort(Node** beginPointer, int opt);
void frontBackSplit(Node* source,Node** frontRef,Node** backRef);
void generateUp(Lista* l, int p);
void generateDown(Lista* l, int p);


//---Controle Analogico do Elevador---//
typedef struct elevador{
	int andarMin;
	int andarMax;
	int capacidade;
	int lotacao;
	int posicao;
	int sentido;
	int t;
}Elevador;


Elevador createElevador(int min, int max, int c);
int subir(Elevador *e);
int descer(Elevador *e);
int isLotado(Elevador e);
int embarca(Elevador *e);
void desembarca(Elevador *e);
void printStatus(Elevador *e);
void atende(Elevador *e, Lista* l, int destino);

//---Funções do controle---//
void oneTime(Lista *l, Elevador *e);
void sjf(Elevador* e, Lista* l);