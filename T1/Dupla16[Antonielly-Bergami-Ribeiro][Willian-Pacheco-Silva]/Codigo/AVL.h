// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

// Este arquivo trata-se de uma biblioteca para uma árvore AVL com tipo de dados genérico.
#ifndef __AVL_H__
#define __AVL_H__

//Inclusão das bibliotecas necessárias.
#include <stdio.h>
#include <stdlib.h>

/*A estrutura abaixo é a estrutura da arvore AVL. Cada nó da árvore é declarado com esse tipo de dado.
Na estrutura da árvore AVL, cada nó tem os campos de chave, esq, dir e fb.
esq: campo do tipo struct avl * que armazena um ponteiro para o filho da esquerda do nó.
dir: campo do tipo struct avl * que armazena um ponteiro para o filho da direita do nó.
chave: campo do tipo void * que armazena um dado do tipo genérico.
fb: campo do tipo int que armazena o fator de balanceamento de cada nó.*/
typedef struct avl
{
    struct avl *esq;
    struct avl *dir;
    void *chave;
    int fb;
} AVL;

/* Função que cria um nó da árvore. Ela recebe como parâmetro a chave do tipo void * e retorna 
o nó da árvore que possui como chave o elemento recebido.*/
AVL *criaNo(void *chave);

/*Função recursiva auxiliar utilizada para realizar as rotações na inserção. Ela recebe como parâmetro um 
ponteiro para o nó da árvore que está desbalanceado e um ponteiro para uma variável que controla 
se a altura da árvore foi alterada ou não. Com base nisso, ela realiza as devidas rotações (simples 
ou dupla) para a direita e depois retorna um ponteiro para o novo nó raiz da árvore recebida.*/
AVL *rodaDireita(AVL *v, int *h);

/*Função recursiva auxiliar utilizada para realizar as rotações na inserção. Ela recebe como parâmetro um 
ponteiro para o nó da árvore que está desbalanceado e um ponteiro para uma variável que controla 
se a altura da árvore foi alterada ou não. Com base nisso, ela realiza as devidas rotações (simples 
ou dupla) para a esquerda e depois retorna um ponteiro para o novo nó raiz da árvore recebida.*/
AVL *rodaEsquerda(AVL *v, int *h);

/*Função recursiva auxiliar utilizada para realizar as rotações na remoção. Ela recebe como parâmetro um 
ponteiro para o nó da árvore que está desbalanceado e um ponteiro para uma variável que controla 
se a altura da árvore foi alterada ou não. Com base nisso, ela realiza as devidas rotações (simples 
ou dupla) para a direita e depois retorna um ponteiro para o novo nó raiz da árvore recebida.*/
AVL *rodaDireitaRemover(AVL *v, int *h);

/*Função recursiva auxiliar utilizada para realizar as rotações na remoção. Ela recebe como parâmetro um 
ponteiro para o nó da árvore que está desbalanceado e um ponteiro para uma variável que controla 
se a altura da árvore foi alterada ou não. Com base nisso, ela realiza as devidas rotações (simples 
ou dupla) para a esquerda e depois retorna um ponteiro para o novo nó raiz da árvore recebida.*/
AVL *rodaEsquerdaRemover(AVL *v, int *h);

/*Função recursiva para inserir dados na árvore. Ela recebe como parâmetro um ponteiro para o nó 
raiz da árvore, um ponteiro para uma variável que controla se a altura da árvore foi alterada ou 
não, um ponteiro para a chave a ser inserida na árvore, uma função de callback para realizar a 
comparação entre as chaves para que seja possível inserir os dados na posição correta da árvore. 
Além disso, ela recebe uma função de callback que realiza a liberação da memória alocada para o caso 
da chave recebida já existir na árvore. Essa função retorna um ponteiro para a nova raiz da árvore.*/
AVL *insereAVL(AVL *v, int *h, void *chave, int (*compara)(void *, void *), void (*liberaChave)(void *));

/*Função recursiva para remover dados da árvore. Ela recebe como parâmetro um ponteiro para o nó 
raiz da árvore, um ponteiro para uma variável que controla se a altura da árvore foi alterada ou 
não, um ponteiro para a chave a ser removida da árvore, uma função de callback para realizar a 
comparação entre as chaves para que seja possível encontrar o nó a ser removido e removê-lo da 
árvore. Além disso, ela recebe uma função de callback que realiza a liberação da memória alocada 
para o nó removido. Essa função retorna um ponteiro para a nova raiz da árvore.*/
AVL *remover(AVL *a, int *h, void *chave, int (*compara)(void *, void *), void (*liberachave)(void *));

/*Função recursiva utilizada para buscar uma chave na árvore. Essa função recebe como parâmetro 
um ponteiro para o nó raiz da árvore, um ponteiro para a chave a ser buscada da árvore e uma função 
de callback para realizar a comparação entre as chaves para que seja possível encontrar o nó. O retorno 
dela é a chave buscada caso o elemento seja encontrado e NULL caso o elemento não esteja na árvore.*/
void *buscaChave(AVL *a, void *chave, int (*compara)(void *, void *));

/*Função recursiva que libera a memória alocada para todos os nós da árvore e das respectivas chaves. 
Ela recebe como parâmetro um ponteiro para o nó raiz da árvore e uma função de callback que realiza 
a liberação da memória alocada para cada nó. Essa função não possui retorno.*/
void liberaArvore(AVL *a, void (*liberaChave)(void *));

/*Função recursiva utilizada para imprimir os nós da árvore evidenciando o nível e o fator de 
balanceamento de cada nó. Ela recebe como parâmetro um ponteiro para o nó raiz da árvore, uma 
variável para controlar o nível da árvore em que o nó se encontra e uma função de callback que 
realiza a impressão das chaves do tipo de dado do código do cliente. Essa função não possui retorno.*/
void imprimeArvore(AVL *a, int cont, void (*imprimeChave)(void *));

#endif