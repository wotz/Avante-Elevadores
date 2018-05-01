#ifndef DATAINPUT_H_INCLUDED
#define DATAINPUT_H_INCLUDED
struct dados {
	Elevador* elevador;
	Lista* evento;
};
typedef struct dados Dados;

Dados recebedados(int argc,char **argv);
#endif // !DATAINPUT_H_INCLUDED

