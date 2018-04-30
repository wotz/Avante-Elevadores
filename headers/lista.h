//---Lista.h---///
typedef struct solicitacao{
	int origem;
	int destino;
	int id;
	int tempo;//Tempo de ocorrência
	int tempoEspera;
	int tempoAtendimento;
	int tipo;//embarque ou desembarque
	int status;//pensei em 0: esperando, 1:em viagem, 2: atendido
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

Lista* createList();
Lista* copyList(Lista* l);
Node* createNode();
Node* sortedMerge(Node* a,Node* b, int opt);
Node* find(Lista* l,int id);
Node* createNode();
int isEmpety(Lista* l);
void pop(Lista* l,int id);
void push(Lista* l, Demand demand);
void printList(Lista *l);
void printNode(Node* node);

