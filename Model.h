/* JVIDA_Model.h
Projeto Jogo da vida
22/11/2023
*/

#define MinTam 10 //dimensao minima da matriz
#define MaxTam 60 //dimensao maxima da matriz

int tam; //tamanho do mundo (da matriz) digitado pelo usuario
int sair = 1; //variavel para sair do loop do jogo
int x, y; //coordenadas globais
int ligarMortas = 0; // 1 para mostrar as vizinhas-mortas, e 0 para esconder as vizinhas-mortas
int vizinhas = 0; //quantidade de vizinhas que uma celula tem
int atraso; 
int geracaoAtual; //contagem de geracoes

int totalvivas = 0; //inicia o numero total de celulas vivas como 0
int totalvmortas = 0; //inicia o numero total de mortas vivas como 0
int totalvivasprox = 0; //inicia o numero total de celulas que estarao vivas na proxima geracao como 0

int qtdgeracoes; //quantidade de geracoes iniciais cadastradas
int ultimasalva = -1; //indice da ultima geracao recuperada (de 0 a 49)
