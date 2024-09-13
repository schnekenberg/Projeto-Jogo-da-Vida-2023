/* JVIDA_Model.cpp
Projeto Jogo da vida
22/11/2023
*/

#include "JVIDA2_Model.h"

char m[MaxTam][MaxTam]; //matriz mundo do tipo mun

typedef struct cel{
 int lin, col; //as 2 coordenadas da celula
 struct cel *next; //ponteiro (endereco) para a proxima celula
} TipoCel;

TipoCel *pvivas, *pvmortas, *pvivasprox; //inicia o ponteiro de cada caso

typedef struct c{
 int lin, col;
} Cel;

typedef struct lista{
 int cont; //conta quantas celulas vivas tem
 Cel L[400]; //tamanho maximo: 400 celulas vivas
} TipoLista;

TipoLista Lvivas;

struct arquivo{
	TipoLista TotalListas; //listas totais
} ListasConf[50]; //numero maximo de "listas das listas" e' 50
