//-----Elevador.h-----//
typedef struct elevador{
	int andarMin;
	int andarMax;
	int capacidade;
	int lotacao;
	int posicao;
	int sentido;
	int tempo;
	int operacao;
}Elevador;

//-------------Constructor-------------//
Elevador* newElevador(int min, int max, int c);

//-------------Getters-------------//
int getTempo(Elevador* e);

int getPosicao(Elevador* e);

int getCapacidade(Elevador* e);

int getLotacao(Elevador* e);

//-------------Setters-------------//
void setPosicao(Elevador* e, int o);

void setLotacao(Elevador* e, int o);

void setTempo(Elevador* e);


//-------------Embarque e desembarque-------------//
void embarca(Elevador* e, Lista* l, Lista* est, int id);
void desembarca(Elevador* e, Lista* l, Lista* est, int id);
void stop(Elevador* e, Lista* l, Lista* est);


//-------------Atendimento de Solicitações-------------//
void go(Elevador* e, Lista* l, Lista* est, int destino);
void goUp(Elevador* e, Lista* l, Lista* est, int destino);
void goDown(Elevador* e, Lista* l, Lista* est, int destino);