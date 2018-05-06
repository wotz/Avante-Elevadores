#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/data.h"
#include "headers/estatistica.h"

/*	
	Função que calcula a média dos valores estatísticos medidos durante a simulação
	Parâmetros:
		(List*) @est -> lista para cálculos estatísticos
	Variáveis locais:
		(Output) @output -> struct que guarda os dados estatísticos
        (Node*) @node -> nó que percorre a lista @est
        (int) @n -> tamanho da lista @est
        (double) @TeMedio -> tempo médio de espera
        (double) @TaMedio -> tempo médio de viagem
	Retorna:
		struct @output que guarda os dados estatísticos
*/
Output calculaMedia (Lista* est){
    Output output;
    int n = est->size;
    int tempoEspera, tempoAtendimento;
    double TeMedio = 0, TaMedio =0;
    Node* node = createNode();
    node = est->begin;
    
    //calcula o somatório de cada variável de tempo
    while(node != NULL){
        tempoEspera = node->demand.momentoEmbarque - node->demand.tempo;
        tempoAtendimento = node->demand.momentoDesembarque - node->demand.tempo - tempoEspera;
        TeMedio = TeMedio + (double)tempoEspera;
        TaMedio = TaMedio + (double)tempoAtendimento;
        node = node->next;
    }
    
    //divide o somatório de cada variável de tempo por n
    TeMedio = TeMedio/n;
    TaMedio = TaMedio/n;
    
    //insere na variável de retorno
    output.TeMedio = TeMedio;
    output.TaMedio = TaMedio;

    return output;
}

/*	
	Função que calcula a média dos valores estatísticos medidos durante a simulação
	Parâmetros:
		(List*) @est -> lista para cálculos estatísticos
	Variáveis locais:
		(Output) @output -> struct que guarda os dados estatísticos
        (Node*) @node -> nó que percorre a lista @est
        (int) @n -> tamanho da lista @est
        (double) @TeDP -> desvio padrão da médio do tempo de espera
        (double) @TaDP -> desvio padrão da médio do tempo de viagem
	Retorna:
		struct @output que guarda os dados estatísticos
*/
Output calculaDP (Lista* est){
    Output output = calculaMedia(est);
    Node* node = createNode();
    int n = est->size;
    double tempoEspera, tempoAtendimento;
    double TaDP=0, TeDP=0;
    node = est->begin;

    //somatório do quadrado da diferença
    while(node != NULL){
        tempoEspera = (double)(node->demand.momentoEmbarque - node->demand.tempo);
        tempoAtendimento = (double)(node->demand.momentoDesembarque - node->demand.tempo - tempoEspera);
        
        TeDP = pow(tempoEspera - output.TeMedio,2);
        TaDP = pow(tempoAtendimento - output.TaMedio,2);

        node = node->next;
    }

    //desvio padrão amostral
    TeDP = sqrt(TeDP/(n));
    TaDP = sqrt(TeDP/(n));

    output.TeDP = TeDP;
    output.TaDP = TaDP;

    return output;
}