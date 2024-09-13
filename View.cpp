/* JVIDA_View.cpp
Projeto Jogo da vida
22/11/2023
*/
#include <stdio.h>
#include "JVIDA2_View.h"


void flush_in(){ //limpa o buffer de entrada
	int ch;
	while((ch= fgetc(stdin)) != EOF && ch !='\n');
}

void apresentaMensagem(char mens[100]){ //apresenta uma mensagem a ser definida
	printf("%s", mens);
}

int ViewTamanhoMundo(){
	int op;
	printf("Escolha o tamanho do mundo (entre 10 e 60): ");
	scanf("%d", &op);
	return op;
}

void mostraMundo(){ //mostra na tela a matriz Hotel
    int i, j;
    printf ("\n   ");
	for (j = 0; j < tam; j++)
		printf (" %02d", j);
	printf("\n");
	for (i = 0; i < tam; i++){
		printf ("\n  %02d", i);
		for (j = 0; j < tam; j++)
			printf (" %c ", m[i][j]);
	}
	int nvidas = contarVidas();
	printf("\n\n%d celula(s) vivas\n", nvidas);
	printf ("Geracao atual: %d\n", geracaoAtual);
	printf("\nLista da(s) %d celula(s) viva(s): ", totalvivas);
	printarLista(pvivas, totalvivas);
	printf("\nLista da(s) %d celula(s) vizinha(s) morta(s): ", totalvmortas);
	printarLista(pvmortas, totalvmortas);
    printf ("\nLEGENDA:\n '.' - Celula morta \n 'O' - Celula viva \n '+' - Celula vizinha morta\n\n");
}

void criarVida_V(){
	printf("\nDigite as coordenadas (linha e coluna)\n");
	printf("Digite -1 em ambas para sair\n");
	
	flush_in();
	printf("\nDigite a linha: ");
	scanf("%d", &x);
	
	flush_in();
	printf("\nDigite a coluna: ");
	scanf("%d", &y);
}

int eliminarVida_V(){ //elimina uma vida
	int op;
	printf("\nDeseja eliminar a vida da celula [%d][%d]?\n1 para SIM, 0 para NAO\n", x, y);
	printf("\nResposta: ");
	flush_in();
	scanf("%d", &op);
	return op;
}

int qtdGeracoes(){ //obtem o valor de geracoes seguidas que o usuario quer ver
	int op;
	printf("\nQuantas geracoes voce deseja ver?\n");
	printf("\nResposta: ");
	flush_in();
	scanf("%d", &op);
	return op;
}

void delay_V(){ //delay de tempo em segundos entre cada geracao
	int op;
	printf("\nQual o intervalo de tempo em segundos entre as geracoes?\n");
	printf("(0 para passagem manual; no modo manual, basta apertar uma tecla para passar as geracoes");
	printf("\nResposta: ");
	flush_in();
	scanf("%d", &atraso);
}

int ViewMenuPrincipal(){ //apresenta o menu principal na tela e capta a opcao escolhida
	int op;
	flush_in();
	printf("\nEscolha uma opcao do menu:");
	printf("\nMENU DE OPCOES");
	printf("\n1. Apresentar o mapa");
	printf("\n2. Limpar o mapa");
	printf("\n3. Incluir/excluir celulas vivas");
	printf("\n4. Mostrar/esconder os mortos-vizinhos");
	printf("\n5. Iniciar o processo");
	printf("\n6. Gravar uma geracao inicial");
	printf("\n7. Recuperar uma geracao inicial cadastrada");
	printf("\n8. Limpar o cadastro de geracoes iniciais cadastradas");
	printf("\n9. Regras de evolucao das celulas");
	printf("\n0. Sair\n");
	printf("\nResposta: ");
	scanf("%d",&op);
	return op;
}

void printarLista(TipoCel *px, int total){ //mostra as celulas de uma determinada lista
	TipoCel *ap = px;
	int tot = total;
	if((ap == NULL) || (tot == 0)){
		printf("A lista esta' vazia!\n");
	}
	else{
		printf("[lin, col]");//legenda
		while(tot > 0){
			printf("[%d, %d] ", ap->lin, ap->col);
			ap = ap->next;
			tot--;
		}
	}
}

void printarRegrasEvolucao(){ //printa as regras basicas de evolucao das celulas
	printf("-----------------------------------------------------------------------------------------------------------------------");
	printf("\nRegras de evolucao:\n");
	printf("\n1. O nascimento de um organismo ocorre em uma celula desocupada quando existem exatamente tres seres vivos vizinhos.\n");
	printf("\n2. Um organismo que possui dois ou tres vizinhos vivos sobrevive para a proxima geracao, refletindo a importancia da\ninteracao em grupo.\n");
	printf("\n3. Organismos com quatro ou mais vizinhos enfrentam a morte, uma vez que a superpopulacao resulta em escassez de\nalimentos, comprometendo sua sobrevivencia.\n");
	printf("\n4. A solidao tambem e' prejudicial, levando 'a morte de um organismo vivo que possui zero ou apenas um vizinho,\ndestacando a necessidade de interacoes sociais para a preservacao da vida.\n");
	printf("-----------------------------------------------------------------------------------------------------------------------");
}
