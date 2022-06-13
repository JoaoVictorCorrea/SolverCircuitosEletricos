#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "CalculaMatrizInversa.h"

float **matrizInversa; //declaração da matriz inversa global

//Função que aloca dinamicamente uma matriz
float** AlocaMatriz(float **mat, int ordem){

    int i, j;

    mat = (float**)malloc(sizeof(int*) * ordem);

    for(i = 0; i < ordem; i++){

        mat[i] = (float*)malloc(sizeof(int) * ordem);
    }

    return mat;
}

//Inicializa uma matriz com zeros
void PreencheMatriz(float **mat, int ordem)
{
    for(int i = 0; i < ordem; i++)
    {
        for(int j = 0; j < ordem; j++){
            mat[i][j] = 0.0;
        }
    }
}

//Função que libera uma matriz da memoria
void LiberaMatriz(float **mat, int ordem){

    for(int i = 0; i < ordem; i++){

        free(mat[i]);
    }

    free(mat);
}

//Função que aloca dinamicamente um array
float* AlocaArray(float *arr, int ordem){

    arr = (float*) malloc(sizeof(int) * ordem);

    return arr;
}

//Inicializa um array com zeros
void PreencheArray(float *arr, int ordem){

    for(int i = 0; i < ordem; i++){

        arr[i] = 0.0;
    }
}

//Libera um array
void LiberaArray(float *arr, int ordem){

    free(arr);
}

//Calcula o determinante de uma matriz
float Determinante(float **mat, int ordem)
{
    float **aux;
    float s = 1, det = 0;
    int i, j, m, n, c;

    aux = AlocaMatriz(aux, ordem);

    if (ordem == 1)
        return (mat[0][0]);
    else{
        det = 0;

        for (c = 0; c < ordem; c++){

            m = 0;
            n = 0;
            for (i = 0; i < ordem; i++){

                for (j = 0 ; j < ordem; j++){

                    aux[i][j] = 0;

                    if (i != 0 && j != c){

                        aux[m][n] = mat[i][j];

                        if (n < (ordem - 2))
                            n++;
                        else{
                            n = 0;
                            m++;
                        }
                    }
                }
            }

            det = det + s * (mat[0][c] * Determinante(aux, ordem - 1));
            s = -1 * s;
        }
    }

    LiberaMatriz(aux, ordem);

    return (det);
}

//Essa função calcula a inversa de uma matriz através do seguinte calculo:

// A^-1 = (COF(A))^T / DET(A)

//Então, a matriz inversa (A^-1) é igual a transposta da matriz de cofatores de A ((COF(A))^T)
//dividido pelo determinante de A (DET(A))

void Inversa(float **mat, int ordem)
{
    float **aux, **fac;
    int p, q, m, n, i, j;

    aux = AlocaMatriz(aux, ordem);
    fac = AlocaMatriz(fac, ordem);

    for (q = 0; q < ordem; q++){

        for (p = 0; p < ordem; p++){

            m = 0;
            n = 0;
            for (i = 0; i < ordem; i++){

                for (j = 0; j < ordem; j++){

                    if (i != q && j != p){

                        aux[m][n] = mat[i][j];

                        if (n < (ordem - 2))
                            n++;
                        else{
                            n = 0;
                            m++;
                        }
                    }
                }
            }

            fac[q][p] = pow(-1, q + p) * Determinante(aux, ordem - 1);
        }
    }

    Transposta(mat, fac, ordem);

    LiberaMatriz(aux, ordem);
    LiberaMatriz(fac, ordem);
}

//Calcula a transposta de uma matriz
void Transposta(float **mat, float **fac, int ordem)
{
    int i, j;
    float **aux, **inversa;
    float det;

    aux = AlocaMatriz(aux, ordem);
    inversa = AlocaMatriz(inversa, ordem);

    for (i = 0; i < ordem; i++){

        for (j = 0; j < ordem; j++){

            aux[i][j] = fac[j][i];
        }
    }

    det = Determinante(mat, ordem);

    for (i = 0;i < ordem; i++){

        for (j = 0;j < ordem; j++){

            inversa[i][j] = aux[i][j] / det;
        }
    }

    for (i = 0; i < ordem; i++){

        for (j = 0; j < ordem; j++){

            matrizInversa[i][j] = inversa[i][j];
        }
    }

    LiberaMatriz(aux, ordem);
    LiberaMatriz(inversa, ordem);
}

//Faz a multiplicação de matrizes
void MultiplicaMatrizes(float **matInversa, float *arrayTensoes, int ordem){

    float soma;

    printf("------------------------------- Solução --------------------------------");
    printf("\n\n");

    for(int i = 0; i < ordem; i++){

        soma = 0.0;

        for(int j = 0; j < ordem; j++){

            soma += matInversa[i][j] * arrayTensoes[j];
        }

        printf("I(%d) = %.3f A\n", i+1, soma);

        printf("\n");
    }

    printf("------------------------------------------------------------------------");
}
