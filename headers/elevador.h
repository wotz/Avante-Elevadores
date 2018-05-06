#ifndef ELEVADOR_H_INCLUDED
#define ELEVADOR_H_INCLUDED

//-----Elevador.h-----//
typedef struct elevador{
	int andarMin;
	int andarMax;
	int capacidade;
	int lotacao;
	int posicao;
	int tempo;
	int operacao;
	int deslocamento;
}Elevador;

/*Esclarecimento da significado de algumas variáveis do elevador:
	- tempo: tempo de simulação. É utilizado para verificar se os eventos estão no passado, presente ou futuro durante a simulação
	- operacao: serve para marcar se o elevador sofreu alguma operação de embarque ou desembarque ou se o elevador mudou de andar.
				serve para controlar a passagem do tempo quando nada acontece
	- deslocamento: conta por quantos andares o elevador passa durante o funcionamento
*/

//-------------Constructor-------------//
Elevador* newElevador(int min, int max, int c);

//-------------Getters-------------//
int getAndarMin(Elevador* e);
int getAndarMax(Elevador* e);
int getCapacidade(Elevador* e);
int getOperacao(Elevador* e);
int getTempo(Elevador* e);
int getPosicao(Elevador* e);
int getLotacao(Elevador* e);
int getDeslocamento(Elevador* e);

//-------------Setters-------------//

void setTempo(Elevador* e);
void setOperacao(Elevador* e, int operacao);
void setPosicao(Elevador* e, int o);
void setLotacao(Elevador* e, int o);

//-------------Is Full-------------//
int isFull(Elevador* e);

//-------------Embarque e desembarque-------------//
void embarca(Elevador* e, Lista* l, Lista* est, int id);
void desembarca(Elevador* e, Lista* l, Lista* est, int id);
void stop(Elevador* e, Lista* l, Lista* est);

//-------------Atendimento de Solicitações-------------//
void go(Elevador* e, Lista* l, Lista* est, int destino);
void goUp(Elevador* e, Lista* l, Lista* est, int destino);
void goDown(Elevador* e, Lista* l, Lista* est, int destino);

#endif// !ELEVADOR_H_INCLUDED