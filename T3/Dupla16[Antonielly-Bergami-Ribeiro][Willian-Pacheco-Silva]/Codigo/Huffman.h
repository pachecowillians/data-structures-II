// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

// Este arquivo se trata de uma biblioteca para o algoritmo de Huffman.
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

//Inclusão das bibliotecas necessárias.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Definição da estrutura onde irá conter as informações do nó da árvore
typedef struct huffman
{
    unsigned char caractere;           //armazena o caractere
    int frequencia;                    //armazena a frequência do caractere
    int tipoFilho;                     //armazena se o nó é filho a direita (0) ou a esquerda (1) do pai dele
    struct huffman *pai;               //aponta para o nó pai
    struct huffman *subarvoreDireita;  //aponta para o filho da direita
    struct huffman *subarvoreEsquerda; //aponta para o filho da esquerda
} Huffman;

//Definição da estrutura que vai ser gravada no arquivo dentro do heap
typedef struct huffmanArquivo
{
    unsigned char caractere;
    int frequencia;
} HuffmanArquivo;

//Definição da estrutura do cabeçalho que será gravada no aquivo compactado
typedef struct cabecalho
{
    unsigned char tamanhoHeap;
    int tamanhoBinario;
} Cabecalho;

/*Função utilizada para criação de um nó da árvore de Huffman. Recebe como parametro o caractere e a 
frequência dele no arquivo de entrada. O retorno dessa função será o nó já com campos atribuidos.*/
Huffman *criaNo(unsigned char caractere, int frequencia);

/*Função auxiliar utilizada para retornar a posição do pai de um nó do heap em um vetor. Recebe como 
parametro a posição do nó atual no heap*/
int Pai(int i);

/*Função auxiliar utilizada para retornar a posição do filho ầ esquerda de um nó do heap em um vetor. 
Recebe como parametro a posição do nó atual no heap.*/
int FilhoEsquerdo(int i);

/*Função auxiliar utilizada para retornar a posição do filho ầ direita de um nó do heap em um vetor. 
Recebe como parametro a posição do nó atual no heap.*/
int FilhoDireito(int i);

/*Função utilizada para restabelecer as propriedades do heap mínimo. Recebe como parâmetro um heap com os 
nós da árvore, o tamanho do heap e uma variavel de controle da posição. Essa função não possui retorno. */
void MinHeapify(Huffman **vetor, int i, int tamanho);

/*Função utilizada para retirar o menor elemento de um heap. Essa função recebe como parâmetro um heap e 
um ponteiro para a variável que armazena o tamanho dele. O retorno será o menor elemento do heap*/
Huffman *RetiraMinimo(Huffman **a, int *tamanho);

/*Função é utilizada para posicionar a chave de um heap. Recebe como parametro o heap, a posição da chave e 
a nova chave que será inserida nessa posição.*/
void DecrementaChave(Huffman **a, int i, Huffman *chave);

/*Função utilizada para inserir uma chave no heap. Recebe como parametro o heap, a nova chave a ser inserida 
e um ponteiro para a variável que armazena o tamanho do heap. Essa função não possui retorno.*/
void InserirHeapMinimo(Huffman **a, Huffman *chave, int *tamanho);

/*Função utilizada para inserir os elementos do arquivo no heap. Recebe como parâmetro a tabela hash que 
relaciona cada caractere com a quantidade de repetições dele e o número de letras distintas que há no 
arquivo de entrada. Depois disso, ela cria um heap com essas informações e retorna o heap criado. Vale 
ressaltar que esse heap é um heap de ponteiros para os nós da árvore.*/
Huffman **criaHeapMin(int *repeticoes, int letrasDistintas);

/*Função utilizada para copiar as informações do heap, que contém os ponteiros para os nós da árvore, para 
um vetor que posteriormente possa ser armazenado no arquivo. O retorno dessa função será o vetor com as 
informações de cada chave e sua respectiva frequência.*/
HuffmanArquivo *criaHeapEstatico(Huffman **heapMin, int tamanhoHeap);

/*Função utilizada para criar uma tabela hash relacionando o caractere com um ponteiro que aponta para o nó 
que guarda esse caractere na árvore. Ela recebe como parâmetro o heap e uma variável contendo o tamanho do 
heap. Com base nesse heap, a tabela hash é criada e o retorno será a própria tabela hash.*/
Huffman **criaHashHeap(Huffman **heap, int tamanhoHeap);

/*Função utilizada para gerar a árvore de Huffman. Essa função recebe como parâmetro o heap mínimo que 
armazena os nós da árvore e uma variável com o tamanho do heap. O retorno dessa função será um ponteiro 
para o nó raiz da árvore.*/
Huffman *criaArvoreHuffman(Huffman **heapMin, int tamanhoHeap);

/*Função utilizada para criar uma tabela hash que relaciona o caractere com o número de repetições dele 
no arquivo. Ela recebe como parâmetro o nome do arquivo, um ponteiro para a variável que armazena a 
quantidade de letras distintas e outro ponteiro para a variável que armazena a quantidade de caracteres 
presentes no arquivo de texto. O retorno dessa função será a tabela hash. */
int *criaVetorRepeticoes(char *nomeArquivo, int *letrasDistintas, int *quantidadeCaracteres);

/*Função utilizada para preencher o byte através da árvore. Recebe como parâmetro um ponteiro para o nó 
folha de uma árvore que contém o caractere, um vetor de bytes (char) que armazena o código binário, um 
ponteiro que aponta para a váriavel que controla a posição do vetor, um ponteiro para a variável que 
controla o número de bits ocupados daquele byte, um ponteiro que aponta para a variável que controla o 
tamanho do código binário e uma variável que armazena a quantidade de letras distintas presentes no arquivo.*/
void codificaChar(Huffman *arvore, char *codBin, int *posicaoVetor, int *numeroBits, int *tamanhoBinario, int letrasDistintas);

/*Função utilizada para converter os caracteres do arquivo para o código binário. Recebe como parâmetro o 
nome de um arquivo a ser lido, a tabela hash que associa cada caractere com o nó dele da árvore, uma variável 
que contém a quantidade de cada caracteres presentes no arquivo, um ponteiro que aponta para a variável que 
contém o tamanho do código binário e uma variável que contém a quantidade de caracteres distintos do arquivo. 
O retorno dessa função será a codificação dos caracteres do arquivo em um vetor de bytes.*/
char *criaBinario(char *nomeArquivo, Huffman **hashHeap, int numeroLetras, int *tamanhoBinario, int letrasDistintas);

/*Função utilizada para comprimir o arquivo. Recebe como parâmetro o nome do arquivo a ser comprimido, a 
estrutura do cabeçalho, o heap com as informações do caractere e o código binário que foi gerado a partir 
da conversão do texto do arquivo para a sequência de bits.*/
void comprimir(char *nomeArquivo, Cabecalho cab, HuffmanArquivo *heapEstatico, char *codigoBinario);

/*Função utilizada para descomprimir um arquivo. Recebe como parametro o nome do arquivo compactado e 
um nome do arquivo para onde ele será descompactado. */
void descomprimir(char *arquivoCompactado, char *arquivoDestino);

/*Função utilizada para liberar a mamória alocada para uma árvore. Recebe como parametro 
um ponteiro para o nó raiz de uma árvore.*/
void liberaArvore(Huffman *a);

/*Função utilizada para imprimir a sequência binária que representa um caractere com base na árvore de 
Huffman. Recebe como parametro um ponteiro para o nó raiz da árvore e uma váriavel de controle da quantidade 
de letras distintas.*/
void imprimeBinarioCaractere(Huffman *arvore, int letrasDistintas);

#endif