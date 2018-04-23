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
