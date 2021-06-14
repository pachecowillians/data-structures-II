// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Importação da biblioteca
#include "ARN.h"

//Função que incializa a variavel externo.
ARN *criaArvore()
{
    externo.chave = 0;
    externo.cor = 0; //Cor preta
    externo.pai = NULL;
    externo.esq = NULL;
    externo.dir = NULL;
    return &externo; //Retorna o campo inicializado.
}

// Função que aloca a memória para um novo nó da árvore
ARN *criaNo(void *chave)
{
    //Alocação de memória
    ARN *novo = (ARN *)malloc(sizeof(ARN));
    if (!novo) //Caso ocorra algum erro de alocação
    {
        printf("Erro de alocacao de memoria!");
        exit(1);
    }
    //Inicialização dos campos do nó
    novo->chave = chave;
    novo->cor = 1;
    novo->dir = &externo;
    novo->esq = &externo;
    novo->pai = &externo;

    return novo; //Retorna o nó inicializado.
}

//Função auxiliar que retorna o campo chave de um nó da árvore.
void *retornaChave(ARN *no)
{
    return no->chave;
}

// Função que realiza a rotação simples à esquerda
ARN *rotacaoEsquerda(ARN *raiz, ARN *x)
{
    //Declaração da variavel
    ARN *filhoDireita;

    //filhoDireita recebe o filho da direita do nó
    filhoDireita = x->dir;

    //O filho a direita de x recebe o filho a esquerda do filho a direita
    x->dir = filhoDireita->esq;

    if (filhoDireita->esq != &externo) //Se o filho da direita tiver filho a esquerda
        filhoDireita->esq->pai = x;    //Atualiza o pai do filho a esquerda do filho a direita

    filhoDireita->pai = x->pai; //O pai do filho a direita recebe o pai de x

    if (x->pai == &externo)  //Caso x seja a raiz
        raiz = filhoDireita; //A nova raiz se torna o filho a direita
    else                     //Caso x não seja a raiz
    {
        if (x == x->pai->esq)           //Se x for o filho a esquerda do pai dele
            x->pai->esq = filhoDireita; //O filho a esquerda do pai de x recebe o filho a direita de x
        else                            //Se x for o filho a direita do pai dele
            x->pai->dir = filhoDireita; //O filho da direita do pai de x recebe o filho a direita de x
    }
    filhoDireita->esq = x; //O filho à esquerda de filhoDireita passa a ser x
    x->pai = filhoDireita; //O pai de x passa a ser filhoDireita

    return raiz; //retorna o novo nó raiz
}

//Função que realiza a rotação simples à direita
ARN *rotacaoDireita(ARN *raiz, ARN *x)
{
    //Declaração da variavel
    ARN *filhoEsquerda;

    //filhoEsquerda recebe o filho a esquerda do nó
    filhoEsquerda = x->esq;

    //O filho a esquerda de x recebe o filho a direita do filho à esquerda
    x->esq = filhoEsquerda->dir;

    if (filhoEsquerda->dir != &externo) //Se o filho a esquerda tiver filho a direita
        filhoEsquerda->dir->pai = x;    //O pai do filho a direita do filho a esquerda recebe x

    filhoEsquerda->pai = x->pai; //O pai do filho à esquerda recebe o pai de x

    if (x->pai == &externo)   //Caso x seja a raiz
        raiz = filhoEsquerda; //A nova raiz se torna o filho à esquerda
    else                      //Caso x não seja a raiz
    {
        if (x == x->pai->dir)            //Se x for o filho à direita do pai dele
            x->pai->dir = filhoEsquerda; //O filho a direita do pai de x recebe o filho à esquerda
        else                             //Se x for o filho à esquerda do pai dele
            x->pai->esq = filhoEsquerda; //O filho a esquerda do pai de x recebe o filho à esquerda
    }
    filhoEsquerda->dir = x; //O filho à direita de filhoEsquerda passa a ser x
    x->pai = filhoEsquerda; //O pai de x passa a ser filhoEsquerda

    return raiz; //Retorna o novo nó raiz
}

//Função que garante a propriedade das cores e as rotações dos nós depois da inserção
ARN *balanceamentoInsercao(ARN *raiz, ARN *z)
{
    //Z é o nó vermelho que foi inserido

    while (z->pai->cor == 1) //Enquanto o pai de z for vermelho
    {
        if (z->pai == z->pai->pai->esq) // Se o pai de z for o filho a esquerda do avô dele
        {
            ARN *tio = z->pai->pai->dir;

            if (tio->cor == 1) //Caso 1
            {
                z->pai->cor = 0;
                tio->cor = 0;
                z->pai->pai->cor = 1;   
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->dir) //Caso 2
                {
                    z = z->pai;
                    raiz = rotacaoEsquerda(raiz, z);
                }
                //Caso3
                z->pai->cor = 0;
                z->pai->pai->cor = 1;
                raiz = rotacaoDireita(raiz, z->pai->pai);
            }
        }
        else // Se o pai de z for o filho a direita do avô dele
        {
            ARN *tio = z->pai->pai->esq;

            if (tio->cor == 1) //Caso 1
            {
                z->pai->cor = 0;
                tio->cor = 0;
                z->pai->pai->cor = 1;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->esq) //Caso 2
                {
                    z = z->pai;
                    raiz = rotacaoDireita(raiz, z);
                }

                //Caso 3
                z->pai->cor = 0;
                z->pai->pai->cor = 1;
                raiz = rotacaoEsquerda(raiz, z->pai->pai);
            }
        }
    }

    raiz->cor = 0; // Define a raiz como preta
    return raiz;   //Retorna o nó raiz
}

//Função de inserção na árvore rubro negra
ARN *insercao(ARN *raiz, void *chave, int (*comparaChave)(void *, void *), void (*liberaChave)(void *))
{
    //Criação do novo nó
    ARN *novoNo = criaNo(chave);

    //Declaração de veriaveis
    ARN *x, *pai;

    pai = &externo;
    x = raiz;

    while (x != &externo)
    {
        if (comparaChave(x->chave, novoNo->chave) == 0) //Caso a chave já exista na árvore
        {
            //Libera a memória alocada para a chave e para o nó
            liberaChave(novoNo->chave);
            free(novoNo);
            return raiz; //Retorna o nó raiz
        }

        pai = x;

        if (comparaChave(novoNo->chave, x->chave) == -1) //Caso a chave a ser inserida seja menor do que o elemento atual
            x = x->esq;
        else //Caso a chave a ser inserida seja maior do que o elemento atual
            x = x->dir;
    }

    novoNo->pai = pai;

    if (pai == &externo) //Se a árvore estava vazia
        raiz = novoNo;
    else
    {
        if (comparaChave(novoNo->chave, pai->chave) == -1) //Se o novo nó for o filho a esquerda do pai
            pai->esq = novoNo;
        else //Se o novo nó for o filho a direita do pai
            pai->dir = novoNo;
    }

    //O novo nó não tem filhos e tem cor vermelha
    novoNo->esq = &externo;
    novoNo->dir = &externo;
    novoNo->cor = 1;

    raiz = balanceamentoInsercao(raiz, novoNo); //Chama a função para consertar possíveis desbalanceamentos

    return raiz; //Retorna o nó raiz
}

//Função que transfere o pai de um nó para o outro
ARN *transferePai(ARN *raiz, ARN *origem, ARN *destino)
{
    if (origem->pai == &externo) //Se a origem for a raiz
        raiz = destino;          //A nova raiz é o destino
    else                         //Se a origem não for a raiz
    {
        if (origem == origem->pai->esq) //Se for filho à esquerda
            origem->pai->esq = destino;
        else //Se for filho à direita
            origem->pai->dir = destino;
    }
    //Atualiza o pai
    destino->pai = origem->pai;
    return raiz;
}

//Função que conserta possíveis desbalanceamentos depois da remoção.
ARN *balanceamentoRemocao(ARN *raiz, ARN *x)
{
    while (x != raiz && x->cor == 0) //Laço para mover o nó preto extra pra cima da árvore
    {
        if (x == x->pai->esq) //Se x for o filho à esquerda do pai dele
        {
            ARN *irmao = x->pai->dir; //Inicializa o irmão

            if (irmao->cor == 1) //Caso 1
            {
                irmao->cor = 0;
                x->pai->cor = 1;
                raiz = rotacaoEsquerda(raiz, x->pai); //Necessário rotação
                irmao = x->pai->dir;
            }
            if (irmao->esq->cor == 0 && irmao->dir->cor == 0) //Caso 2
            {
                irmao->cor = 1;
                x = x->pai;
            }
            else
            {
                if (irmao->dir->cor == 0) //Caso 3
                {
                    irmao->esq->cor = 0;
                    irmao->cor = 1;
                    raiz = rotacaoDireita(raiz, irmao); //Necessário rotação
                    irmao = x->pai->dir;
                }
                //Caso 4
                irmao->cor = x->pai->cor;
                x->pai->cor = 0;
                irmao->dir->cor = 0;
                raiz = rotacaoEsquerda(raiz, x->pai); //Necessário rotação
                x = raiz;
            }
        }
        else
        {
            ARN *irmao = x->pai->esq; //Inicializa o irmão

            if (irmao->cor == 1) //Caso 1
            {
                irmao->cor = 0;
                x->pai->cor = 1;
                raiz = rotacaoDireita(raiz, x->pai); //Necessário rotação
                irmao = x->pai->esq;
            }
            if (irmao->dir->cor == 0 && irmao->esq->cor == 0) //Caso 2
            {
                irmao->cor = 1;
                x = x->pai;
            }
            else
            {
                if (irmao->esq->cor == 0) //Caso 3
                {
                    irmao->dir->cor = 0;
                    irmao->cor = 1;
                    raiz = rotacaoEsquerda(raiz, irmao); //Necessário rotação
                    irmao = x->pai->esq;
                }
                //Caso 4
                irmao->cor = x->pai->cor;
                x->pai->cor = 0;
                irmao->esq->cor = 0;
                raiz = rotacaoDireita(raiz, x->pai); //Necessário rotação
                x = raiz;
            }
        }
    }
    x->cor = 0;  //Define a cor da raiz como preta
    return raiz; //Retorna o nó raiz
}

// Função que remove um nó da árvore rubro negra
ARN *remocao(ARN *raiz, ARN *noRemovido, void (*liberaChave)(void *))
{
    ARN *x, *y;
    int corDeY;

    y = noRemovido;
    corDeY = y->cor; //Salvando a cor de y antes que possa haver alguma mudança

    if (noRemovido->esq == &externo) //Se o nó removido só tiver filho à direita ou não tiver filhos
    {
        x = noRemovido->dir; //x aponta pra o filho do nó removido da direita
        raiz = transferePai(raiz, noRemovido, noRemovido->dir);
    }
    else
    {
        if (noRemovido->dir == &externo) //Se o nó removido só tiver filho à esquerda
        {
            x = noRemovido->esq; //x aponta para o filho do nó removido da esquerda
            raiz = transferePai(raiz, noRemovido, noRemovido->esq);
        }
        else //Se o nó removido tiver os dois filhos
        {
            y = sucessor(noRemovido); //Encontra o sucessor
            corDeY = y->cor;          //Salvando a cor de y antes que possa haver alguma mudança
            x = y->dir;
            if (y->pai == noRemovido) //Se o nó removido for pai do sucessor
            {
                x->pai = y;
            }
            else //Se o nó removido não for pai do sucessor
            {
                raiz = transferePai(raiz, y, y->dir);
                y->dir = noRemovido->dir;
                y->dir->pai = y;
            }
            raiz = transferePai(raiz, noRemovido, y);
            y->esq = noRemovido->esq;
            y->esq->pai = y;
            y->cor = noRemovido->cor;
        }
    }
    if (corDeY == 0)
    {
        raiz = balanceamentoRemocao(raiz, x); //Restaurar as propriedades de balanceamento e cor
    }
    //Libera a memória alocada para noRemovido
    liberaChave(noRemovido->chave); //Libera a memória alocada para noRemovido
    free(noRemovido);
    return raiz;
}

//Função auxiliar utilizada para encontrar o sucessor de um nó.
ARN *sucessor(ARN *a)
{
    a = a->dir;
    while (a->esq != &externo) //Percorre a árvore até o nó não ter mais filhos à esquerda
        a = a->esq;

    return a; //retorna o nó sucessor
}

//Função que libera a memória alocada para o nó da árvore e suas respectivas chaves
void liberaArvore(ARN *a, void (*liberaChave)(void *))
{
    if (a != &externo) //Caso a árvore não esteja vazia
    {
        //Chama a função recursivamente para liberar a memória na subárvore esquerda
        liberaArvore(a->esq, liberaChave);
        //Chama a função recursivamente para liberar a memória na subárvore direita
        liberaArvore(a->dir, liberaChave);
        //Utiliza a função de callback para liberar a memória alocada para a chave
        liberaChave(a->chave);
        //Libera a memória alocada para o nó da árvore.
        free(a);
    }
}

/*Função utilizada para imprimir cada nó da árvore e sua cor aplicando a tabulação
de acordo com o nível de cada nó */
void imprimeArvore(ARN *a, int cont, void (*imprimeChave)(void *))
{
    if (a != &externo) //Caso a árvore não esteja vazia
    {
        //Chama a função recursivamente para imprimir a subarvore da direita
        imprimeArvore(a->dir, cont + 1, imprimeChave);

        //Realiza a tabulação por nível
        for (int i = 0; i < cont; i++)
        {
            printf("\t");
        }

        //Define uma variavel cor do tipo char que será utilizada para imprimir a cor do nó
        char cor;
        if (a->cor == 0) //Se o campo cor for 0
            cor = 'P';   //Cor recebe P de preto
        else             //Caso contrário
            cor = 'V';   //Cor recebe V de vermelho

        printf("[");
        //Utiliza a função de callback para imprimir a chave
        imprimeChave(a->chave);
        printf(": %c]\n", cor);

        //Chama a função recursivamente para imprimir a subarvore da esquerda
        imprimeArvore(a->esq, cont + 1, imprimeChave);
    }
}

//Função recursiva que busca uma chave na árvore
ARN *buscaChave(ARN *a, void *chave, int (*comparaChave)(void *, void *))
{
    if (a != &externo) //Caso a árvore não esteja vazia
    {
        if (comparaChave(chave, a->chave) == -1) //Se a chave buscada for menor do que a chave atual
            //Realiza a busca na subárvore da esquerda
            return buscaChave(a->esq, chave, comparaChave);
        else if (comparaChave(chave, a->chave) == 1) //Se a chave buscada for maior do que a chave atual
            //Realiza a busca na subárvore da direita
            return buscaChave(a->dir, chave, comparaChave);
        else //Caso a chave for encontrada
            //Retorna o nó que contém a chave buscada
            return a;
    }
    else //Se a árvore está vazia ou o elemento não está na árvore
        return &externo;
}
