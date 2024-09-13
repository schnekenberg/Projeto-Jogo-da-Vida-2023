/* JVIDA_Controller.h
Projeto Jogo da vida
22/11/2023
*/
void menuPrincipal(); //funcao das opcoes do menu principal
void tamanhoMundo(); //pede o tamanho do mundo e o cria
void criarVida_C(); //cria ou elimina uma vida
void vizinhasMortas(); //mostra e esconde as vizinhas mortas
void obliterarMundo(char matriz[MaxTam][MaxTam]); //limpa o mapa e destroi todas as vivas
int contarVidas(); //conta quantas celulas estao vivas
void proximaGeracao(); //faz a analise de quais celulas vao permanecer vivas ou de quais vao criar vida na proxima geracao e atualiza a matriz atual com a nova geracao
void delay_C(); //intervalo de tempo utilizado entre as geracoes fornecido pelo usuario

void iniciaListas(); //inicia as listas vazias
void carregaVivas(int ii, int jj); //carrega na lista de vivas
void carregaVMortas(int ii, int jj); //carrega na lista de vizinhas mortas
void carregaVivasProx(int ii, int jj); //carrega na lista de proximas vivas
void limpaLista(TipoCel *aux, int total); //limpa uma lista
void eliminarVidaLista(int ii, int jj); //elimina uma celula da lista de vivas
void eliminarVMortoLista(int ii, int jj); //elimina uma celula da lista de vivas
int verificaMorta(int ii, int jj); //verifica se uma celula ja esta na lista das vizinhas mortas
void atualizaVizinhasMortas(); //ve se as vizinhas de uma celula viva estao mortas, e se sim, as carrega na lista de mortas
void atualizaVivasProx(); //gera e atualiza a lista das celulas que estarao vivas na proxima geracao

void gravaCelulas(); //salva todas as celulas vivas, uma por uma
void carregaConf(); //carrega a configuracao de listas salvas
void recuperarCelulas(); //recupera as celulas da geracao inicial desejada
void vivasMatriz(); //carrega as celulas na lista de vivas para a matriz
void limpaGeracoes(); //limpa as geracoes iniciais salvas
void deletaConf(); //remove o arquivo de configuracoes iniciais para que nao seja recuperado
