#ifndef CALCULAMATRIZINVERSA_H_INCLUDED
#define CALCULAMATRIZINVERSA_H_INCLUDED

float** AlocaMatriz(float **mat, int ordem);
void PreencheMatriz(float **mat, int ordem);
void LiberaMatriz(float **mat, int ordem);

float* AlocaArray(float *arr, int ordem);
void PreencheArray(float *arr, int ordem);
void LiberaArray(float *arr, int ordem);

float Determinante(float **mat, int ordem);
void Transposta(float **mat, float **fac, int ordem);
void Inversa(float **mat, int ordem);
void MultiplicaMatrizes(float **matInversa, float *arrayTensoes, int ordem);

extern float **matrizInversa; //matriz inversa global

#endif // CALCULAMATRIZINVERSA_H_INCLUDED
