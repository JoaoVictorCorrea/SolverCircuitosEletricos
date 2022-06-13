#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<locale.h>
#include "CalculaMatrizInversa.h"

int main()
{
    setlocale(LC_ALL, "Portuguese"); //conversão para digitação em Português(BR)

    int i, j, k;

    int qtd_malhas, qtd_malhasCompartilhada,  n_malhaCompartilhada;

    float *arrayTensoes; //declaração do array das tensões
    float **matResistores; //declaração da matriz composta pelos resistores

    float somaResistores = 0.0, somaCompartilhada = 0.0, somaTensoes = 0.0;
    float det;

    printf("Insira a quantidade de malhas presentes no circuito: "); //Leitura da quantidade de malhas do usuario
    scanf("%d", &qtd_malhas);
    printf("\n");

    matResistores = AlocaMatriz(matResistores, qtd_malhas);//Alocação dinâmica da matriz de resistores
    PreencheMatriz(matResistores, qtd_malhas); //Função que inicializa a matriz de resistores com 0

    arrayTensoes = AlocaArray(arrayTensoes, qtd_malhas); //Alocação dinâmica do array de tensões
    PreencheArray(arrayTensoes, qtd_malhas); //Função que inicializa o array de tensões com 0

    //iteração que pergunta as informações do circuito ao usuario
    for(i = 0; i < qtd_malhas; i++){

        printf("------------------------------- %d malha --------------------------------", i + 1);
        printf("\n\n");

        somaResistores = 0.0;
        somaTensoes = 0.0;

        printf("Qual é a soma dos resistores da malha %d? ", i+1);
        scanf("%f", &somaResistores);

        matResistores[i][i] = somaResistores; //insere o valor da soma dos resistores da malha i na matriz (sempre na diagonal principal)

        printf("\nCom quantas malhas a malha %d compartilha seus resistores? ", i+1);
        scanf("%d", &qtd_malhasCompartilhada);

        //iteração que pergunta sobre as malhas compartilhadas no circuito do usuário
        for(j = 0; j < qtd_malhasCompartilhada; j++){

            printf("\nQual é a %dª malha? ", j+1);
            scanf("%d", &n_malhaCompartilhada);

            printf("Qual é a soma dos resistores que a malha %d compartilha com a malha %d? ", n_malhaCompartilhada, i+1);
            scanf("%f", &somaCompartilhada);

            //insere os valores dos resistores compartilhados com a malha i na matriz
            matResistores[i][n_malhaCompartilhada - 1] = somaCompartilhada * (-1);
        }

        printf("\nQual é a soma das tensões da malha %d (sentido horário)? ", i+1);
        scanf("%f", &somaTensoes);

        arrayTensoes[i] = somaTensoes; //insere a soma das tensões da malha i no array de tensões

        printf("\n");
        printf("------------------------------------------------------------------------");
        printf("\n\n");
    }

    //caclula o determinante da matriz de resistores
    det = Determinante(matResistores, qtd_malhas);

    //se o determinante for == 0, logo a matriz não tem inversa, portanto, não tem solução
    if(det == 0)
        printf("\n Não tem solução! \n");
    else{

        matrizInversa = AlocaMatriz(matrizInversa, qtd_malhas); //Alocação dinâmica da matriz inversa de resistores
        Inversa(matResistores, qtd_malhas); //calcula a inversa da matriz de resistors

        MultiplicaMatrizes(matrizInversa, arrayTensoes, qtd_malhas); //faz a multiplicação da matriz inversa dos resistores com o array de tensões

        LiberaMatriz(matResistores, qtd_malhas);//libera a matriz de resistores da memoria
        LiberaMatriz(matrizInversa, qtd_malhas);//libera a matriz inversa de resistores da memoria
        LiberaArray(arrayTensoes, qtd_malhas); //libera o array da memoria
    }
}
