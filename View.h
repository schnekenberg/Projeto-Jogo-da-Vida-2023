/* JVIDA_View.h
Projeto Jogo da vida
22/11/2023
*/

void flush_in(); //limpa o buffer
int ViewMenuPrincipal(); //apresenta o menu principal na tela e capta a opcao escolhida
void apresentaMensagem(char mens[100]); //apresenta uma mensagem a ser definida
void mostraMundo(); //mostra o mundo
int eliminarVida_V(); //elimina uma vida
int qtdGeracoes(); //obtem o valor de geracoes seguidas que o usuario quer ver
void delay_V(); //delay de tempo em segundos entre cada geracao
void printarLista(TipoCel *px, int total); //mostra uma lista
void printarRegrasEvolucao(); //printa as regras basicas de evolucao das celulas
