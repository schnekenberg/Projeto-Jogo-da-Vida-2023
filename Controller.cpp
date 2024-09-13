/* JVIDA_Main.cpp
Projeto Jogo da vida
22/11/2023

STATUS:
'.' - CELULAS MORTAS
'O' - CELULAS VIVAS
'+' = CELULAS VIZINHAS
*/
#include "JVIDA2_Controller.h"
#include "JVIDA2_View.cpp"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void tamanhoMundo(){
	do{ //enquanto o tamanho do mundo (da matriz) nao pertencer a faixa permitida, mostra uma mensagem e pede outra vez
	tam = ViewTamanhoMundo();
	if ((tam > MaxTam) || (tam < MinTam)) 
		apresentaMensagem("\nTamanho invalido, tente novamente!\n");
	}while ((tam > MaxTam) || (tam < MinTam));
	
	int i, j;
   	for (i = 0; i < tam; i++)
		for (j = 0; j < tam; j++){
			m[i][j] = '.';
		}
}	

int contarVidas(){ //conta quantas celulas estao vivas
	int cont = 0;
	int i, j;
   	for (i = 0; i < tam; i++)
		for (j = 0; j < tam; j++)
			if (m[i][j] == 'O')
				cont++;
	return cont;
}

void criarVida_C(){ //cria ou elimina uma vida
	int i, j, k, opc;
	i = x;
	j = y;
	if ((i == -1) && (j == -1))
		return;
	else if (m[i][j] != 'O'){ //se a c?lula n?o estiver viva
		m[i][j] = 'O'; //adiciona a vida na matriz
		if(verificaMorta(i, j) == 1){
			eliminarVMortoLista(i, j);
		}
		carregaVivas(i, j);
		atualizaVizinhasMortas();

		geracaoAtual = 1;
		if (ligarMortas == 1){ //se quiser mostrar, adiciona o '+'
			for (k = j-1; k <= j+1; k++){
				if (m[i-1][k] == '.'){ //se a c?lula vizinha estiver morta e ainda n?o estiver destacada, adiciona o '+'
						m[i-1][k] = '+';
				}
				if (m[i][k] == '.'){
						m[i][k] = '+';
				}
				if (m[i+1][k] == '.'){ 
						m[i+1][k] = '+';
				}
			}
		}
	}		
	else if (m[i][j] == 'O'){ //se estiver viva, pergunta se quer eliminar
		opc = eliminarVida_V();
		if (opc == 1){
			m[i][j] = '.';
			eliminarVidaLista(i, j);
			atualizaVizinhasMortas();	
			//atualizar as vizinhas mortas
			for (k = j-1; k <= j+1; k++){ //for que percorre as vizinhas. se alguma estiver destacada, coloca '.'
									   	  //fazemos isso para "limpar" as vizinhas da c?lula eliminada
				if (m[i-1][k] == '+'){ 
						m[i-1][k] = '.';
				}
				if (m[i][k] == '+'){
						m[i][k] = '.';
				}
				if (m[i+1][k] == '+'){ 
						m[i+1][k] = '.';
				}
			}
			vizinhasMortas();
		}
	}
}

void vizinhasMortas(){ //mostra/esconde as vizinhas mortas
	int i, j, k;

	for (i = 0; i < tam; i++){ 
		for (j = 0; j < tam; j++){ //for que varre a matriz completa
		
			if (m[i][j] == 'O'){
				for (k = j-1; k <= j+1; k++){ //for que varre as coordenadas vizinhas
					if (((k >= 0) && (k < tam))){

						if(ligarMortas == 1){ //se quiser mostrar, coloca '+'
							if (m[i-1][k] == '.'){ 
								m[i-1][k] = '+';
							}
							if (m[i][k] == '.'){
								m[i][k] = '+';
							}
							if (m[i+1][k] == '.'){
								m[i+1][k] = '+';
							}
						}
						
						else if(ligarMortas == 0){ //se nao quiser mostrar, coloca '.'
							if (m[i-1][k] == '+'){
								m[i-1][k] = '.';
							}
							if (m[i][k] == '+'){
								m[i][k] = '.';
							}
							if (m[i+1][k] == '+'){ 
								m[i+1][k] = '.';
							}
						}
						
					}
				}
			}
		}
	}
}

void proximaGeracao(){ //faz a analise de quais celulas vao permanecer vivas ou de quais vao criar vida na proxima geracao e atualiza a matriz atual com a nova geracao
int i, j;

	obliterarMundo(m); //limpa a matriz (ultima geracao)
	atualizaVivasProx(); //atualizar as proximas vivas
	limpaLista(pvivas, totalvivas); //limpa a lista de celulas vivas
	totalvivas = 0;
	limpaLista(pvmortas, totalvmortas);
	totalvmortas = 0;
	pvivas = pvivasprox;
	totalvivas = totalvivasprox;
	
	TipoCel *ap = pvivas; //pega as proximas vivas da lista pvivasprox
	while(ap != NULL){ //varre a lista das proximas celulas vivas ate' chegar no final 
		m[ap->lin][ap->col] = 'O'; //pega as coordenadas guardadas na lista e coloca uma celula viva
		ap = ap->next; //troca pra proxima celula
	}

	pvivasprox = NULL;
	totalvivasprox = 0;
	
	atualizaVizinhasMortas(); //atualiza a lista de mortas
	
	geracaoAtual++;
	vizinhasMortas();
}

void obliterarMundo(char matriz[MaxTam][MaxTam]){ //limpa o mapa e destroi todas as vivas
	int i, j;
	for (i = 0; i < tam; i++){ 
		for (j = 0; j < tam; j++)
			matriz[i][j] = '.';
	}
}

void delay_C(){ //intervalo de tempo utilizado entre as geracoes fornecido pelo usuario
	time_t lt1, lt2; //atraso de tempo
 		lt1 = time(NULL);
 		lt2 = lt1;
 		while (difftime(lt2, lt1) < atraso)
 			lt2 = time(NULL);
}

void menuPrincipal(){ //funcao das opcoes do menu principal
	
int opc = ViewMenuPrincipal(); //opcao escolhida

switch(opc){

	case 1: mostraMundo();
			break; //mostra o mapa
	
	case 2: obliterarMundo(m);
			limpaLista(pvivas, totalvivas);
			limpaLista(pvmortas, totalvmortas);
			limpaLista(pvivasprox, totalvivasprox);
			totalvivas = 0;
			totalvivasprox = 0;
			totalvmortas = 0;
			geracaoAtual = 0;
			mostraMundo();
			break; //limpar o mapa
	
	case 3: mostraMundo();
			do{
				do{ //pede as coordenadas ate que sejam validas, OBS: x = -1 e y = -1 sao coordenadas validas usadas para sair do menu de criar/eliminar vida
					criarVida_V();
					if ((x >= tam) || (y >= tam) || (x < -1) || (y < -1) || (x == -1 && y != -1) || (x != -1 && y == -1)){
						apresentaMensagem ("\n\nCoordenada invalida!\n\n");
						mostraMundo();
					}
				}	while((x >= tam) || (y >= tam) || (x < -1) || (y < -1) || (x == -1 && y != -1) || (x != -1 && y == -1));
				criarVida_C();
				mostraMundo();
			} while ((x != -1) && (y != -1));
			break; //incluir/excluir celulas vivas
	
	case 4:	if (ligarMortas == 0)
				ligarMortas = 1;
			else if (ligarMortas == 1)
				ligarMortas = 0;
			vizinhasMortas();
			mostraMundo();
			break; //mostrar/esconder os mortos/vizinhos
	
	case 5:	if (geracaoAtual > 0){
				int k;
				int g = qtdGeracoes();
				if (g > 0){
					do{
						delay_V();
						if ((atraso < 0) || (atraso > 100))
							apresentaMensagem("\nIntervalo de tempo invalido!\n");
					}
					while ((atraso < 0) || (atraso > 100));
					
					for (k = 1; k <= g; k++){
						if (atraso == 0){
							apresentaMensagem("\nAperte uma tecla para passar a geracao!");
							getchar();
						}
						else{
							delay_C();
						}
						proximaGeracao();
						mostraMundo();
					}
				}
				else
					apresentaMensagem("\nDigite um numero valido!\n");
			}
			else
				apresentaMensagem("\nNao e' possivel suceder geracoes sem vidas!\n");
			break; //iniciar o processo
	
	case 6: gravaCelulas();
			break;//gravar uma geracao inicial 
	
	case 7:	obliterarMundo(m);
			geracaoAtual = 1;
			recuperarCelulas();
			carregaConf();
			vivasMatriz();
			atualizaVizinhasMortas();
			mostraMundo();
			break;//recuperar uma geracao inicial cadastrada
	
	case 8: limpaGeracoes();
			obliterarMundo(m);
			qtdgeracoes = 0;
			limpaLista(pvivas, totalvivas);
			limpaLista(pvmortas, totalvmortas);
			limpaLista(pvivasprox, totalvivasprox);
			totalvivas = 0;
			totalvivasprox = 0;
			totalvmortas = 0;
			geracaoAtual = 0;
			break; //limpar o cadastro de geracoes iniciais cadastradas (n geracoes)
	
	case 9: printarRegrasEvolucao();
			break;//regras de evolucao das celulas
	
	case 0: sair = 0;
			return; //sair
		
	}
}

void vivasMatriz(){ //carrega as celulas na lista de vivas para a matriz
	if (totalvivas == 0)
		return;
	else{
		TipoCel *lv = pvivas; //lv = lista vivas
			while(lv != NULL){ //atualizar a matriz
				m[lv->lin][lv->col] = 'O';
				lv = lv->next;
		}
	}
}

void iniciaListas(){ //inicia todas as listas
	limpaLista(pvivas, totalvivas);
	limpaLista(pvmortas, totalvmortas);
	limpaLista(pvivasprox, totalvivasprox);
	pvivas = pvmortas = pvivasprox = NULL; //ponteiros vazios
}

void carregaVivas(int ii, int jj){ //carrega celulas vivas para a lista pvivas
	TipoCel *aux = (TipoCel*) malloc(sizeof(TipoCel)); //define o ponteiro e aloca memoria para uma celula
	if (aux == NULL){
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva\n");
 		return;
 	}
	aux->lin = ii;
 	aux->col = jj;
 	if (totalvivas == 0){
 		pvivas = aux; //carrega a auxiliar, adicionando uma celula
 		pvivas->next = NULL; //a nova celula aponta pro nada, pois e' a ultima da lista
 	}
 	else {
 		aux->next = pvivas; //a nova celula aponta para a que era a primeira
 		pvivas = aux; //o inicio da lista passa a ser a nova celula
 	}
 	totalvivas++; //incrementa a quantidade total de celulas vivas
}


void carregaVMortas(int ii, int jj){ //carrega celulas vizinhas mortas para a lista pvmortas
	if ((ii < 0) || (jj < 0)) //se estiver fora dos limites da matriz, retorna
		return;
	if ((ii >= tam) || (jj >= tam))
		return;
	if (m[ii][jj] == 'O') //se estiver viva, retorna
		return;
	
	if (verificaMorta(ii, jj) == 1) //se ja estiver na lista de mortas, retorna
		return;

	TipoCel *aux = (TipoCel *) malloc(sizeof(TipoCel)); 
	if (aux == NULL){
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva\n");
 		return;
 	}
	aux->lin = ii; 
 	aux->col = jj;
 	if (totalvmortas == 0){ 
 		pvmortas = aux; 
 		pvmortas->next = NULL; 
 	}
 	else { 
 		aux->next = pvmortas;
 		pvmortas = aux; 
 	}
 	totalvmortas++;
 	
 	if (ligarMortas == 1)
		m[ii][jj] = '+';
 	else
 		m[ii][jj] = '.';
}


void carregaVivasProx(int ii, int jj){ //carrega celulas que vao sobreviver ou nascer na proxima geracao para a lista pvivasprox
	TipoCel *aux = (TipoCel*) malloc(sizeof(TipoCel)); 
	if (aux == NULL){
		apresentaMensagem("Sem espaco na memoria para inclusao de celula viva\n");
 		return;
 	}
	aux->lin = ii; 
 	aux->col = jj;
 	if (totalvivasprox == 0){ 
 		pvivasprox = aux; 
 		pvivasprox->next = NULL; 
 	}
 	else {
 		aux->next = pvivasprox; 
 		pvivasprox = aux; 
 	}
 	totalvivasprox++;
}

void limpaLista(TipoCel *aux, int total){ //limpar uma lista
	if(aux == NULL || total == 0) 
 		return;
 	TipoCel *aux2;
 	do{
 		aux2 = aux;
 		aux = aux->next;
 		free(aux2); //libera memoria
 	}
	while(aux != NULL);
}

void eliminarVidaLista(int ii, int jj){ //elimina uma celula da lista de vivas
	TipoCel *aux2, *aux3;
	aux2 = pvivas;
	aux3 = aux2;
 	if (totalvivas > 0){
 		while (aux2->lin != ii || aux2->col != jj){
 			aux3 = aux2;
 			aux2 = aux2->next;
 		}
 		if (aux2->lin == ii && aux2->col == jj){
 			if (aux3 == aux2) //se e' o primeiro da lista
 				pvivas = aux2->next;
 			else
 				aux3->next = aux2->next;
 			free(aux2);
			}
 	totalvivas--;
	}
}

void eliminarVMortoLista(int ii, int jj){ //elimina uma celula da lista de mortas
	TipoCel *aux2, *aux3; //define 2 ponteiros auxiliares
	aux2 = pvmortas;
	aux3 = aux2; //guarda a celula como sendo a anterior
 	if (totalvmortas > 0){
 		while (aux2->lin != ii || aux2->col != jj){
 			aux3 = aux2;
 			aux2 = aux2->next;
 		}
 		if (aux2->lin == ii && aux2->col == jj){
 			if (aux3 == aux2) //se e' o primeiro da lista
 				pvmortas = aux2->next;
 			else
 				aux3->next = aux2->next;
 			free(aux2);
			}
 	totalvmortas--;
	}
}

int verificaMorta(int ii, int jj){ //verifica se uma celula ja esta na lista das vizinhas mortas
	TipoCel *aux;
	aux = pvmortas;
	if (totalvmortas == 0)
		return 0; //nao esta na lista de mortas
	do{
		if (aux->lin == ii && aux->col == jj)
		return 1; //se encontrar na lista de mortas, retorna 1
		aux = aux->next;
	} while (aux != NULL);
	
 	return 0; //se passou por toda a verificacao e nao foi encontrada, entao nao esta na lista de mortas
}


void atualizaVizinhasMortas(){ //verifica se as vizinhas de uma celula viva estao mortas, e se sim, as carrega na lista de mortas
	int k, i, ii, jj;
	struct{
		int li, co; //linha e coluna
 	} a,b,c,d,e,f,g,h; //celulas vizinhas
 	//libera lista de mortos
 	totalvmortas = 0;
 	TipoCel *aux;
 	aux = pvivas;
 	if (totalvivas == 0)
 		return;
 	do{
 		ii = aux->lin;
 		jj = aux->col;
 		a.li = ii-1; a.co = jj-1;
 		b.li = ii-1; b.co = jj;
 		c.li = ii-1; c.co = jj+1;
 		d.li = ii; d.co = jj-1;
		e.li = ii; e.co = jj+1;
		f.li = ii+1; f.co = jj-1;
		g.li = ii+1; g.co = jj;
		h.li = ii+1; h.co = jj+1;
		
		carregaVMortas(a.li, a.co);
 		carregaVMortas(b.li, b.co);
 		carregaVMortas(c.li, c.co);
 		carregaVMortas(d.li, d.co);
 		carregaVMortas(e.li, e.co);
 		carregaVMortas(f.li, f.co);
 		carregaVMortas(g.li, g.co);
 		carregaVMortas(h.li, h.co); //verifica todas as celulas vizinhas
 		if(aux->next == NULL)
 			break;
 		aux = aux->next;
	}
 	while(1);
}

void atualizaVivasProx(){ //gera e atualiza a lista das celulas que estarao vivas na proxima geracao
	int i, j, ii, jj, vii, vjj, ct;
	limpaLista(pvivasprox, totalvivasprox);
	pvivasprox = NULL; //ponteiros vazios
 	if (pvivas == NULL)
 		return;
 	//vizinhos vivos das celulas vivas
 	TipoCel *aux, *aux2;
 	aux = pvivas;
 	do{
 		ct = 0; //contador de vizinhos da celula (ii, jj)
 		ii = aux->lin;
 		jj = aux->col;
 		aux2 = pvivas;
 		do{
 			vii = aux2->lin;
 			vjj = aux2->col;
 			if (vii != ii || vjj != jj) //se nao for a mesma celula
 				if(abs(ii-vii)<=1 && abs(jj-vjj)<=1) //se e' vizinho
 					ct++;
 			aux2 = aux2->next;
 		} while(aux2 != NULL);
 		if (ct == 2 || ct == 3)
 			carregaVivasProx(ii,jj); //se tiver 2 ou 3 vizinhos vivos, sobrevive na proxima geracao
 		aux = aux->next;
 	} while(aux != NULL);
 
 	if (pvmortas == NULL)
		return;
	//vizinhos vivos das celulas mortas
 	aux = pvmortas;
 	do{
 		ct = 0; //contador de vizinhos da celula (ii, jj)
 		ii = aux->lin;
 		jj = aux->col;
 		aux2 = pvivas;
 		do{
 			vii = aux2->lin;
 			vjj = aux2->col;
 			if(abs(ii-vii)<=1 && abs(jj-vjj)<=1) //se e' vizinho
 				ct++;
 			aux2 = aux2->next;
 		} while(aux2 != NULL);
 	if (ct == 3)
 		carregaVivasProx(ii,jj); //se tiver exatamente 3 vizinhas vivas, nasce na proxima geracao
 	aux = aux->next;
 	} while(aux != NULL);
}


void gravaCelulas(){ //salva todas as celulas vivas, uma por uma
	int k, i, v;
 	k = qtdgeracoes;
 	if (totalvivas == 0){
 		apresentaMensagem("\nNao e' possivel salvar uma geracao sem celulas vivas!\n");
 		return;
 	}
 	//carrega o vetor Lvivo com a lista atual de vivas (somente para gravacao)
 	TipoCel *aux;
 	aux = pvivas;
 	v = 0; //indice do vetor L da estrutura Lvivas
 	do{
 		Lvivas.L[v].lin = aux->lin;
 		Lvivas.L[v].col = aux->col;
 		v++;
 		aux = aux->next;
 	} while (aux != NULL);
 	Lvivas.cont = totalvivas;
 	ListasConf[k].TotalListas = Lvivas;
 	
	FILE *fp;
 	if((fp = fopen("CONFIG_INIC", "w")) == NULL){
 		apresentaMensagem("\nERRO: O arquivo CONFIG_INIC nao pode ser aberto para gravacao\n");
 		return;
 	}
 	for(i = 0; i <= qtdgeracoes; i++){
 		if (fwrite(&ListasConf[i], sizeof(TipoLista), 1, fp) != 1){
 			apresentaMensagem("\nErro na gravacao do arquivo CONFIG_INIC\n");
 			fclose(fp);
 			return;
 		}
 	}
 	fclose(fp);
 	qtdgeracoes++;
 	apresentaMensagem("\nGeracao gravada com sucesso!\n");
}

void carregaConf(){ //carrega a configuracao de listas salvas
	int k;
	FILE *fp;
	if((fp = fopen("CONFIG_INIC", "r")) != NULL){ //pesquisa a quantidade de configuracoes cadastradas
 		qtdgeracoes = 0;
 		k = 0;
		while(!feof(fp)){ //enquanto nao for o fim de arquivo
 			if (fread(&ListasConf[k], sizeof(TipoLista), 1, fp) != 1){
 				fclose(fp);
 				return;
 			}
 			qtdgeracoes++;
 			k++;
 		}
 	fclose(fp);
 	}
}

void recuperarCelulas(){ //recupera as celulas da geracao inicial desejada
 	int i, j, k, v;
 	if (qtdgeracoes == 0){
 		apresentaMensagem("\nNao existe geracao a recuperar!\n");
 		return;
 	}
 	k = ultimasalva + 1;
 	if (k >= qtdgeracoes)
 		k = 0; //volta ao primeiro conjunto de celulas
 	Lvivas = ListasConf[k].TotalListas; //obtem a lista das cdlulas a serem recuperadas
 	ultimasalva = k;
	limpaLista(pvivas, totalvivas);
	totalvivas = 0;
	pvivas = NULL;
 	for(v = 0; v < Lvivas.cont; v++)
 		carregaVivas(Lvivas.L[v].lin, Lvivas.L[v].col); 
}

void deletaConf(){ //remove o arquivo de configuracoes iniciais para que nao seja recuperado
	if(remove("CONFIG_INIC") != 0){
 		apresentaMensagem("\nERRO: O arquivo CONFIG_INIC nao pode ser removido\n");
		return;
 	}
	qtdgeracoes = 0;
 	apresentaMensagem("\nO arquivo CONFIG_INIC foi removido com sucesso!\n");
}

void limpaGeracoes(){ //limpa as geracoes iniciais salvas
 	qtdgeracoes = 0;
 	ultimasalva = -1; //ultima geracao salva
	deletaConf();
 	apresentaMensagem("\nO deposito de geracoes iniciais foi limpo e agora esta vazio!\n");
}
