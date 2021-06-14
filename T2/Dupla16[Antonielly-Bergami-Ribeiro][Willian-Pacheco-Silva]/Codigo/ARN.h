// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

// Este arquivo se trata de uma biblioteca para uma árvore rubro negra com tipo de dados genérico.
#ifndef __ARN_H__
#define __ARN_H__

//Inclusão das bibliotecas necessárias.
#include <stdio.h>
#include <stdlib.h>

/*A estrutura abaixo é a estrutura da arvore rubro negra. Cada nó da árvore será declarado com esse tipo de dado.
Na estrutura dessa árvore, cada nó tem os campos de esq, dir, pai, chave e cor.
esq: campo do tipo struct arn * que armazena um ponteiro para o filho da esquerda do nó.
dir: campo do tipo struct arn * que armazena um ponteiro para o filho da direita do nó.
pai: campo do tipo struct arn * que armazena o nó pai de um nó.
chave: campo do tipo void * que armazena um dado do tipo genérico.
cor: campo do tipo int que armazena a cor daquele nó, sendo 0 = preto e 1 = vermelho.*/
typedef struct arn
{
    struct arn *esq;
    struct arn *dir;
    struct arn *pai;
    void *chave;
    int cor;
} ARN;

//Definição da variavel global que será o nó sentinela
ARN externo;

/*Função auxiliar utilizada para inicializar a variavel externo. O retorno dela será o endereço da variavel
já inicializada.*/
ARN *criaArvore();

/* Função que cria um nó da árvore. Ela recebe como parâmetro a chave do tipo void * e retorna 
o nó da árvore que possui como chave o elemento recebido.*/
ARN *criaNo(void *chave);

/*Função auxiliar utilizada para realizar as rotações para a esquerda. Essa função recebe como parâmetro 
um ponteiro para o nó raiz da árvore e um ponteiro para o nó da árvore sobre o qual ocorrerá a rotação. 
Com base nisso, ela realiza a rotação para a esquerda e depois retorna um ponteiro para o novo nó raiz da 
árvore.*/
ARN *rotacaoEsquerda(ARN *raiz, ARN *x);

/*Função auxiliar utilizada para realizar as rotações para a direita. Essa função recebe como parâmetro 
um ponteiro para o nó raiz da árvore e um ponteiro para o nó da árvore sobre o qual ocorrerá a rotação. 
Com base nisso, ela realiza a rotação para a direita e depois retorna um ponteiro para o novo nó raiz da 
árvore.*/
ARN *rotacaoDireita(ARN *raiz, ARN *x);

/*Função auxiliar utilizada para realizar as rotações e definições de cores dos nós após a inserção.
Recebe como parâmetro um ponteiro para o nó raiz da árvore e um ponteiro para o nó a ser inserido.
O retorno será um ponteiro para o novo nó raiz.*/
ARN *balanceamentoInsercao(ARN *raiz, ARN *z);

/*Função de inserção de chaves em uma árvore rubro negra. Recebe como parâmetro um ponteiro para o nó raiz da 
árvore, a chave a ser inserida, uma função de callback comparaChave que realiza as comparações entre as chaves
e uma função de callback liberaChave que libera a memória alocada caso a chave recebida já exista na árvore. 
Essa função retorna um ponteiro para a nova raiz da árvore.*/
ARN *insercao(ARN *raiz, void *chave, int (*comparaChave)(void *, void *), void (*liberaChave)(void *));

/*Função utilizada para transferir um pai de um nó de origem para outro nó de destino. Ela recebe um ponteiro 
para a raiz da árvore, um ponteiro para o nó de origem e um ponteiro para o nó de destino. Depois de transferir 
o pai, ela retorna um ponteiro para a nova raiz da árvore.*/
ARN *transferePai(ARN *raiz, ARN *origem, ARN *destino);

/*Função auxiliar utilizada para realizar as rotações de definições de cores dos nós após a remoção.
Recebe como parâmetro um ponteiro para o nó raiz da árvore e um ponteiro para o nó a ser removido.
O retorno será um ponteiro para o novo nó raiz.*/
ARN *balanceamentoRemocao(ARN *raiz, ARN *x);

/*Função auxiliar utilizada para encontrar o sucessor de um nó. Essa função recebe como parâmetro 
um ponteiro para um nó da árvore e percorre essa árvore até encontrar o sucessor desse nó. O retorno 
será o nó sucessor.*/
ARN *sucessor(ARN *a);

/*Função de remoção de chaves em uma árvore rubro negra. Recebe como parâmetro um ponteiro para o nó raiz da 
árvore, um ponteiro para o nó a ser removido, uma função de callback comparaChave para realizar as comparações 
entre as chaves e uma função de callback liberaChave que libera a memória alocada caso a chave recebida já 
exista na árvore. Essa função retorna um ponteiro para a nova raiz da árvore.*/
ARN *remocao(ARN *raiz, ARN *noRemovido, void (*liberaChave)(void *));

/*Função recursiva utilizada para buscar uma chave na árvore. Essa função recebe como parâmetro 
um ponteiro para o nó raiz da árvore, um ponteiro para a chave a ser buscada na árvore e uma função 
de callback para realizar a comparação entre as chaves para que seja possível encontrar o nó. O retorno 
dela é a chave buscada caso o elemento seja encontrado e um ponteiro para o nó "externo" caso o elemento 
não esteja na árvore.*/
ARN *buscaChave(ARN *a, void *chave, int (*comparaChave)(void *, void *));

/*Função auxiliar utilizada para retornar o campo chave de um nó da árvore. Ela recebe um ponteiro para 
um nó da árvore e retorna um ponteiro do tipo void * que contém a chave daquele nó.*/
void *retornaChave(ARN *no);

/*Função recursiva que libera a memória alocada para cada nó da árvore e das respectivas chaves deles. 
Ela recebe como parâmetro um ponteiro para o nó raiz da árvore e uma função de callback que realiza 
a liberação da memória alocada para cada chave. Essa função não possui retorno.*/
void liberaArvore(ARN *a, void (*liberaChave)(void *));

/*Função recursiva utilizada para imprimir os nós da árvore evidenciando o nível e a cor de cada nó. 
Ela recebe como parâmetro um ponteiro para o nó raiz da árvore, uma variável para controlar o nível da
árvore em que o nó se encontra e uma função de callback que realiza a impressão das chaves do tipo de 
dado do código do cliente. Essa função não possui retorno.*/
void imprimeArvore(ARN *a, int cont, void (*imprimeChave)(void *));

#endif