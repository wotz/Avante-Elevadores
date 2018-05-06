#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int andarMin = 0, andarMax, capacidade, quantEventos;
    int tempo, origem, destino;
    int faixaquantEventos,faixaCapacidade,faixaAndarMin,faixaAndarMax;
    int teste=0;

    FILE* arqElevador;
    FILE* arqEventos;

    printf("\nDigite a faixa da quantidade de eventos: ");
    scanf("%d",&faixaquantEventos);
    printf("Digite a faixa de andar máximo e capacidade: ");
    scanf("%d %d", &faixaAndarMax, &faixaCapacidade);
    
    srand ((unsigned)time(NULL));   

    while(teste <= 10){
        char nome_arqElevador [20] = "data/elevador";
        char nome_arqEventos [20] = "data/eventos";
        char numTeste [2];
        
        teste++;
        
        sprintf(numTeste,"%i",teste);

        strcat(nome_arqElevador,numTeste);
        strcat(nome_arqElevador,".txt");
        
        strcat(nome_arqEventos,numTeste);
        strcat(nome_arqEventos,".txt");
        
        arqElevador = fopen(nome_arqElevador,"w");

        quantEventos = 10 + rand() % (faixaquantEventos + 2);
        capacidade = 2 + rand() % (faixaCapacidade + 2);
        andarMax = (andarMin + 1) + rand () % (faixaAndarMax + 1);

        fprintf(arqElevador,"%d %d ",andarMin,andarMax);
        fprintf(arqElevador,"%d",capacidade);

        fclose(arqElevador);
        
        arqEventos = fopen(nome_arqEventos,"w");

        for(int i=0; i<quantEventos;i++){
            tempo = 1 + (rand() % 100);
            origem = (andarMin) + rand() % (andarMax);
            destino = (andarMin) + rand() % (andarMax);
            fprintf(arqEventos,"%d %d %d ",tempo,origem,destino);
        }
        fclose(arqEventos);
    }
    
    return 0;
}