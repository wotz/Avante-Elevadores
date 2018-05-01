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
int getTime(Elevador* e);

int getPosicao(Elevador* e);

int getCapacidade(Elevador* e);

int getLotacao(Elevador* e);

//-------------Setters-------------//
void setPosicao(Elevador* e, int o);

void setLotacao(Elevador* e, int o);

void setTempo(Elevador* e);

