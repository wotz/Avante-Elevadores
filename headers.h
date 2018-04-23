//---Lista.h---///
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
	int first;
	Node* head;
	Node* begin;
}Lista;

Lista* createList();
Lista* copyList(Lista* l);
Node* createNode();
Node* sortedMerge(Node* a,Node* b, int opt);
Node* find(Lista* l,int id);
int findFloor(Lista* l, int andar);
int isEmpety(Lista* l);
int pop(Lista* l,int id);
void push(Lista* l, Demand demand);
void printList(Lista *l);
void printNode(Node* node);
Node* createNode();


//-----merge.h-----//
void merge(Lista* l,int opt);
void mergeSort(Node** beginPointer, int opt);
void frontBackSplit(Node* source,Node** frontRef,Node** backRef);
void generateUp(Lista* l, int p);
void generateDown(Lista* l, int p);



//-----Elevador.h-----//
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

//-----ListaAdvanced.h-----//
Lista* generate(Lista* l, int posicao, int destino);
Lista* generatePossible(Lista* l,int posicao, int destino);
Lista* generateImpossible(Lista* l, int posicao, int destino);
//-----ElevadorAdvanced.h-----//
void goTo(Elevador *e, int destino);
void atende(Elevador *e, Lista* l, int destino);
