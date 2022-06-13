#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<locale.h>
#include "CalculaMatrizInversa.h"

int main()
{
    setlocale(LC_ALL, "Portuguese"); //convers�o para digita��o em Portugu�s(BR)

    int i, j, k;

    int qtd_malhas, qtd_malhasCompartilhada,  n_malhaCompartilhada;

    float *arrayTensoes; //declara��o do array das tens�es
    float **matResistores; //declara��o da matriz composta pelos resistores

    float somaResistores = 0.0, somaCompartilhada = 0.0, somaTensoes = 0.0;
    float det;

    printf("Insira a quantidade de malhas presentes no circuito: "); //Leitura da quantidade de malhas do usuario
    scanf("%d", &qtd_malhas);
    printf("\n");

    matResistores = AlocaMatriz(matResistores, qtd_malhas);//Aloca��o din�mica da matriz de resistores
    PreencheMatriz(matResistores, qtd_malhas); //Fun��o que inicializa a matriz de resistores com 0

    arrayTensoes = AlocaArray(arrayTensoes, qtd_malhas); //Aloca��o din�mica do array de tens�es
    PreencheArray(arrayTensoes, qtd_malhas); //Fun��o que inicializa o array de tens�es com 0

    //itera��o que pergunta as informa��es do circuito ao usuario
    for(i = 0; i < qtd_malhas; i++){

        printf("------------------------------- %d malha --------------------------------", i + 1);
        printf("\n\n");

        somaResistores = 0.0;
        somaTensoes = 0.0;

        printf("Qual � a soma dos resistores da malha %d? ", i+1);
        scanf("%f", &somaResistores);

        matResistores[i][i] = somaResistores; //insere o valor da soma dos resistores da malha i na matriz (sempre na diagonal principal)

        printf("\nCom quantas malhas a malha %d compartilha seus resistores? ", i+1);
        scanf("%d", &qtd_malhasCompartilhada);

        //itera��o que pergunta sobre as malhas compartilhadas no circuito do usu�rio
        for(j = 0; j < qtd_malhasCompartilhada; j++){

            printf("\nQual � a %d� malha? ", j+1);
            scanf("%d", &n_malhaCompartilhada);

            printf("Qual � a soma dos resistores que a malha %d compartilha com a malha %d? ", n_malhaCompartilhada, i+1);
            scanf("%f", &somaCompartilhada);

            //insere os valores dos resistores compartilhados com a malha i na matriz
            matResistores[i][n_malhaCompartilhada - 1] = somaCompartilhada * (-1);
        }

        printf("\nQual � a soma das tens�es da malha %d (sentido hor�rio)? ", i+1);
        scanf("%f", &somaTensoes);

        arrayTensoes[i] = somaTensoes; //insere a soma das tens�es da malha i no array de tens�es

        printf("\n");
        printf("------------------------------------------------------------------------");
        printf("\n\n");
    }

    //caclula o determinante da matriz de resistores
    det = Determinante(matResistores, qtd_malhas);

    //se o determinante for == 0, logo a matriz n�o tem inversa, portanto, n�o tem solu��o
    if(det == 0)
        printf("\n N�o tem solu��o! \n");
    else{

        matrizInversa = AlocaMatriz(matrizInversa, qtd_malhas); //Aloca��o din�mica da matriz inversa de resistores
        Inversa(matResistores, qtd_malhas); //calcula a inversa da matriz de resistors

        MultiplicaMatrizes(matrizInversa, arrayTensoes, qtd_malhas); //faz a multiplica��o da matriz inversa dos resistores com o array de tens�es

        LiberaMatriz(matResistores, qtd_malhas);//libera a matriz de resistores da memoria
        LiberaMatriz(matrizInversa, qtd_malhas);//libera a matriz inversa de resistores da memoria
        LiberaArray(arrayTensoes, qtd_malhas); //libera o array da memoria
    }
}
