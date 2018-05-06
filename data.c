#include "headers/lista.h"
#include "headers/elevador.h"
#include "headers/data.h"
#include "headers/estatistica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MÓDULO DE ENTRADA E SAÍDA DE DADOS

/*	
	Função que recebe os parâmetros lidos por linha de comando e armazena os dados nas variáveis que precisam recebê-los
	Parâmetros:
		(int) @argc -> quantidade de parâmetros passados por linha de comando
		(char**) @argv -> vetor de strings de tamanho igual a @argc
	Variáveis locais:
		(Dados*) @conjuntoentrada -> nó que percorre toda a lista @l
		(int) @andarMin -> andar mínimo que o elevador pode descer
		(int) @andarMax -> andar máximo que o elevador pode subir
		(int) @capacidade -> lotação máxima do elevador
		(int) @tempo -> tempo em que o evento ocorre
		(int) @origem -> origem da solicitação
		(int) @destino -> destino da solicitação
		(int) @id -> codigo que distingue as solicitações umas das outras
		(FILE*) @arqElevador -> arquivo do ambiente de elevador
		(FILE*) @arqEventos -> arquivo dos eventos
		(int) @linha -> contador de linhas do arquivo @arqEventos
		(Lista*) @evento -> lista de eventos (solicitações)
		(Demand) @demand -> conteúdo que será inserido nos nós da lista @evento
	Retorna:
		Um conjunto de dados de entrada @conjuntoentrada. O que inclui um elevador e uma lista de solciitações.
*/
Dados recebedados(int argc, char** argv){
	//Declaração de variáveis
	Dados conjuntoentrada;
	int andarMin, andarMax, capacidade;
	int tempo, origem, destino, id = 0;

	FILE* arqElevador;
	FILE* arqEventos;

	Elevador* elevador;
	Lista* evento;
	Demand demand;

	//Desenvolvimetno da função
	arqElevador = fopen(argv[1], "r");
	if (arqElevador == NULL)
		printf("\nERRO 3: Nao foi possivel abrir o arquivo do ambiente de elevador\n");
	else {
		fscanf(arqElevador, "%d %d\n", &andarMin, &andarMax);
		fscanf(arqElevador, "%d\n", &capacidade);
	}
	elevador = newElevador(andarMin, andarMax, capacidade);
	
	fclose(arqElevador);
	
	evento = createList();

	int linha = 0;//contador de linhas de arquivo
	arqEventos = fopen(argv[3], "r");
	if (arqEventos == NULL)
		printf("\nERRO 4: Nao foi possivel abrir o arquivo que descreve os eventos\n");
	else {
		while (fscanf(arqEventos, "%d %d %d\n", &tempo, &origem, &destino) != EOF) {
			linha++;
			if(origem < andarMin || origem > andarMax || destino < andarMin || destino > andarMax){
				printf("ERRO 5: A origem ou o destino estão fora do intervalo [andar mínimo, andar máximo].\n");
				printf("Altere a linha %d do arquivo %s\n",linha,argv[3]);
				exit(1);
			}
			if(origem != destino){
				id++;
				demand.status = 0;
				demand.id = id;
				demand.origem = origem;
				demand.destino = destino;
				demand.tempo = tempo;
				demand.momentoEmbarque = 0;
				demand.momentoDesembarque = 0;
				demand.d = 0;
				
				//Insere na lista @evento a solicitação @demand
				push(evento, demand);
			}
		}
		if(isEmpety(evento)){
			printf("ERRO 6: Nenhuma entrada válida. Entradas do tipo origem igual destino não são válidas\n");
			printf("Corrija o arquivo %s\n",argv[3]);
			exit(1);
		}
	}
	fclose(arqEventos);

	//Atribuição à variável de retorno da função
	conjuntoentrada.elevador = elevador;
	conjuntoentrada.evento = evento;

	return conjuntoentrada;
}

void saida_dados(Elevador* e, Lista* est){
	Output output = calculaDP(est);
	printLogo();
	//printList(est);
	
	printf("\nQuantidade de eventos: %d\n",est->size);
	if(e->deslocamento > 1)
		printf("- Deslocamento do elevador: %d andares\n",e->deslocamento);
	else
		printf("- Deslocamento do elevador: %d andar\n",e->deslocamento);
	printf("- Tempo de simulação: %d Z\n",e->tempo);
	printf("- Tempo médio de espera: %lf Z\n",output.TeMedio);
	printf("- Desvio padrão do tempo médio de espera: %lf\n", output.TeDP);
	printf("- Tempo médio de viagem: %lf Z\n",output.TaMedio);
	printf("- Desvio padrão do tempo médio de viagem: %lf\n", output.TaDP);
}

/*	
	Função que imprime na tela todo o contéudo da lista.
		Se a lista está vazia, encerra a função.
	Parâmetros:
		(Lista*) @l-> lista qualquer
	Variáveis locais:
		(Node*) @pointer -> nó para percorrer a lista @l recebida como parâmetro
	Retorna:
		Função do tipo vazio
*/
void printList(Lista* l){
	if(isEmpety(l))//verifica se a lista está vazia
		return;
	Node* pointer = createNode();
	pointer = l->begin;
	while(pointer != NULL){
		//Imprime o nó @pointer
		printNode(pointer);
		pointer = pointer->next;
	}
}

/*	
	Função que imprime na tela o conteúdo de um nó
	Parâmetros:
		(Node*) node -> nó que será impresso 
	Variáveis locais:
		(int*) @tempoEspera -> tempo de espera até o passageiro representado pelo nó embarcar
		(int*) @tempoAtendimento -> tempo que o passageiro representado pelo nó permanece dentro do elevador
		(int*) @tempoTotal -> tempo que o passageiro representaod pelo nó aguarda até chegar no destino
	Retorna:
		Função do tipo vazio
*/
void printNode(Node* node){
	if(node != NULL){
		int tempoEspera = 0, tempoAtendimento = 0, tempoTotal = 0;
		/*
			Por Definição uma solicitação demora pelo menos duas unidade de tempo
			para ser atendida
		*/
		if(node->demand.momentoDesembarque != 0){
			tempoEspera = node->demand.momentoEmbarque - node->demand.tempo; 
			tempoTotal = node->demand.momentoDesembarque - node->demand.tempo;
			tempoAtendimento = tempoTotal - tempoEspera;
		}
		else if(node->demand.momentoEmbarque != 0){
			tempoEspera = node->demand.momentoEmbarque - node->demand.tempo; 
		}
		printf("Id: %.3d ", node->demand.id);
		printf("Origem: %.3d ", node->demand.origem);
		printf("Destino: %.3d ", node->demand.destino);
		printf("TO: %.3d ", node->demand.tempo);
		printf("TE: %.3d ", tempoEspera);
		printf("TA: %.3d ", tempoAtendimento);
		printf("TT: %.3d ", tempoTotal);
		printf("d: %d ", node->demand.d);
		printf("Status: %d \n", node->demand.status);
	}
	else
		exit(1);
}

/*	
	Função que imprime na tela os valores de tempo de execução para entrada, processamento e saída do programa
	Parâmetros:
		(long int) timeInput -> tempo de leitura de dados
		(long int) timeLogic -> tempo de processamento de dados
		(long int) timeOutput -> tempo de saída de dados
	Variáveis locais:
		Não há
	Retorna:
		Função do tipo vazio
*/
void saidaTempo(long int timeInput, long int timeLogic, long int timeOutput){
	printf("\n----------------------------------------------\n");
	printf("Informações do tempo de execução do programa:\n");
	printf("   Tempo de entrada de dados: %ld ms\n",timeInput);
	printf("   Tempo de processamento: %ld ms\n",timeLogic);
	printf("   Tempo de saída de dados: %ld ms\n",timeOutput);
}

/*	
	Função que imprime na tela o status do elevador no instante em que a função é chamada
		O status é composto das seguintes informações:
			-Posição atual do elevador
			-Andar mínimo que o elevador alcança
			-Andar máximo que o elevador alcança
			-Capacidade do elevador
			-Lotação atual
			-Tempo da simulação
			-Distância em andares percorrida pelo elevador
	Parâmetros:
		(Elevador*) @e -> elevador
	Retorna:
		Função do tipo vazio
*/
void printStatus (Elevador* e){
	printf("-------Acima e avante: %.2dº andar----\n", getPosicao(e));
	printf("|      Andar Mín: %.2dº              |\n",getAndarMin(e));
	printf("|      Andar Máx: %.2dº              |\n",getAndarMax(e));
	printf("|      Capacidade Máx: %.2d          |\n",getCapacidade(e));
	printf("|      Lotacao atual: %.2d           |\n",getLotacao(e));
	printf("|      Tempo atual: %.2d             |\n",getTempo(e));
	printf("|      Deslocamento: %.2d            |\n",getDeslocamento(e));
	printf("------------------------------------\n");
}

//Imprime a logo do Acima e Avante Elevadores
void printLogo(){
	printf("-------------------Acima e Avante Elvadores-------------------\n");
	printf("|TO: momento de ocorrencia                                   |\n");
	printf("|TE: tempo ate o elvador chegar na solicitacao               |\n");
	printf("|TA: tempo que a pessoa passsa dentro do elevador            |\n");
	printf("|TT: tempo decorrido desde a solicitacao ate o atendimento   |\n");
	printf("--------------------------------------------------------------\n");
}