// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Importação da biblioteca
#include "AVL.h"

// Função que aloca a memória para um novo nó da árvore
AVL *criaNo(void *chave)
{
    //Alocação de memória
    AVL *novo = (AVL *)malloc(sizeof(AVL));

    if (!novo) //Caso ocorra algum erro de alocação
    {
        printf("Erro de alocacao de memoria!");
        exit(1);
    }

    //Inicialização das variáveis
    novo->chave = chave;
    novo->fb = 0;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

//Função que realiza as rotações simples e dupla para a direita ao inserir na árvore
AVL *rodaDireita(AVL *v, int *h)
{
    //Declaração das variáveis
    AVL *u, *z;

    //Filho a esquerda do nó desbalanceado
    u = v->esq;

    if (u->fb == 1) // Rotação simples a direita
    {
        //Realizando os reapontamentos
        v->esq = u->dir;
        u->dir = v;

        //Alterando o fator de balanceamento
        v->fb = 0;
        //Atualizando a raiz
        v = u;
    }
    else //Rotação dupla a direita
    {
        //Filho a direita do filho a esquerda do nó desbalanceado
        z = u->dir;

        //Realizando os reapontamentos
        u->dir = z->esq;
        z->esq = u;
        v->esq = z->dir;
        z->dir = v;

        //Alterando o fator de balanceamento para cada caso
        if (z->fb == 1)
            v->fb = -1;
        else
            v->fb = 0;

        if (z->fb == -1)
            u->fb = 1;
        else
            u->fb = 0;

        //Atualizando a raiz
        v = z;
    }

    //Atualizando o fator de balanceamento do nó desbalanceado para 0
    v->fb = 0;
    //Indicando que não há mais alteração na altura
    *h = 0;
    return v;
}

//Função que realiza as rotações simples e dupla para a esquerda ao inserir na árvore
AVL *rodaEsquerda(AVL *v, int *h)
{
    AVL *u, *z;

    //Filho a direita do nó desbalanceado
    u = v->dir;

    if (u->fb == -1) //Rotação simples a esquerda
    {
        //Realizando os reapontamentos
        v->dir = u->esq;
        u->esq = v;

        //Atualizando o fator de balanceamento
        v->fb = 0;
        //Atualizando a raiz
        v = u;
    }
    else //Rotação dupla a esquerda
    {
        //Filho a esquerda do filho a direita do nó desbalanceado
        z = u->esq;

        //Realizando os reapontamentos para a rotação
        u->esq = z->dir;
        z->dir = u;
        v->dir = z->esq;
        z->esq = v;

        //Alterando o fator de balanceamento para cada caso
        if (z->fb == 1)
            u->fb = -1;
        else
            u->fb = 0;

        if (z->fb == -1)
            v->fb = 1;
        else
            v->fb = 0;

        //Atualizando a raiz
        v = z;
    }

    //Zerando o fator de balanceamento da raiz
    v->fb = 0;
    //Indicando que não houve mais alteração de altura
    *h = 0;
    return v;
}

//Função que realiza as rotações simples e dupla a direita ao remover um nó
AVL *rodaDireitaRemover(AVL *v, int *h)
{
    //Declaração das variáveis
    AVL *u, *z;

    //Filho a esquerda do nó desbalanceado
    u = v->esq;

    if (u->fb >= 0) // Rotação simples a direita
    {
        //Realizando os reapontamentos
        v->esq = u->dir;
        u->dir = v;

        //Alterando o fator de balanceamento para cada caso
        if (u->fb == 0)
        {
            v->fb = 1;
            u->fb = -1;
            //Indicando que a altura não foi alterada
            *h = 0;
        }
        else
        {
            v->fb = 0;
            u->fb = 0;
        }

        //Atualizando a raiz
        v = u;
    }
    else //Rotação dupla a direita
    {
        //Filho a direita do filho a esquerda do nó desbalanceado
        z = u->dir;

        //Realizando os reapontamentos
        u->dir = z->esq;
        z->esq = u;
        v->esq = z->dir;
        z->dir = v;

        //Alterando o fator de balanceamento para cada caso
        if (z->fb == 1)
        {
            v->fb = -1;
            u->fb = 0;
            z->fb = 0;
        }
        else if (z->fb == -1)
        {
            v->fb = 0;
            u->fb = 1;
            z->fb = 0;
        }
        else
        {
            v->fb = 0;
            u->fb = 0;
            z->fb = 0;
        }

        //Atualizando a raiz
        v = z;
    }
    return v;
}

//Função que realiza as rotações simples e dupla a esquerda ao remover um nó
AVL *rodaEsquerdaRemover(AVL *v, int *h)
{
    AVL *u, *z;

    //Filho a direita do nó desbalanceado
    u = v->dir;

    if (u->fb <= 0) //Rotação simples a esquerda
    {
        //Realizando os reapontamentos
        v->dir = u->esq;
        u->esq = v;

        //Atualizando o fator de balanceamento pra cada caso
        if (u->fb == 0)
        {
            v->fb = -1;
            u->fb = 1;
            //Indicando que não houve alteração na altura
            *h = 0;
        }
        else
        {
            u->fb = 0;
            v->fb = 0;
        }

        //Atualizando a raiz da árvore
        v = u;
    }
    else //Rotação dupla a esquerda
    {
        //Filho a esquerda do filho a direita do nó removido
        z = u->esq;

        //Realizando os reapontamentos
        u->esq = z->dir;
        z->dir = u;
        v->dir = z->esq;
        z->esq = v;

        //Atualizando os fatores de balanceamento para cada caso
        if (z->fb == 1)
        {
            v->fb = 0;
            u->fb = -1;
            z->fb = 0;
        }
        else if (z->fb == -1)
        {
            v->fb = 1;
            u->fb = 0;
            z->fb = 0;
        }
        else
        {
            v->fb = 0;
            u->fb = 0;
            z->fb = 0;
        }

        //Atualizando a raiz da árvore
        v = z;
    }
    return v;
}

//Função recursiva que realiza a inserção em uma árvore AVL mantendo o balanceamento
AVL *insereAVL(AVL *v, int *h, void *chave, int (*compara)(void *, void *), void (*liberaChave)(void *))
{
    if (!v) //Caso a árvore esteja vazia
    {
        //Aloca memória para um novo nó
        v = criaNo(chave);
        //Indica que a altura foi alterada
        *h = 1;
    }
    else //Caso a árvore não seja vazia
    {
        if (compara(chave, v->chave) == 0) //Se o elemento a ser inserido já existe na árvore
        {
            //Libera a memória alocada para o elemento
            liberaChave(chave);
            return v;
        }
        if (compara(chave, v->chave) == -1) //Se o elemento a ser inserido é menor do que o elemento atual
        {
            //Chama a inserção recursivamente na subarvore esquerda
            v->esq = insereAVL(v->esq, h, chave, compara, liberaChave);

            if (*h != 0) //Caso haja alteração na altura durante a inserção
            {
                switch (v->fb) //Altera o fator de balanceamento de acordo com cada caso
                {
                case -1:
                    v->fb = 0;
                    //Inserção nesse caso não altera a altura
                    *h = 0;
                    break;

                case 0:
                    v->fb = 1;
                    break;

                case 1:
                    //Houve necessidade de rotação
                    v = rodaDireita(v, h);
                    break;

                default:
                    break;
                }
            }
        }
        else //Se o elemento a ser inserido é maior do que o elemento atual
        {
            //Chama a função de inserção recursivamente na subarvore direita
            v->dir = insereAVL(v->dir, h, chave, compara, liberaChave);

            if (*h != 0) //Caso ocorra alteração na altura após a inserção
            {
                switch (v->fb) //Altera o fator de balanceamento de acordo com cada caso
                {
                case 1:
                    v->fb = 0;
                    //Nesse caso não houve alteração na altura
                    *h = 0;
                    break;

                case 0:
                    v->fb = -1;
                    break;

                case -1:
                    //Houve necessidade de rotação
                    v = rodaEsquerda(v, h);
                    break;

                default:
                    break;
                }
            }
        }
    }
    return v;
}

//Função recursiva que busca uma chave na árvore
void *buscaChave(AVL *a, void *chave, int (*compara)(void *, void *))
{
    if (a) //Caso a árvore não esteja vazia
    {
        if (compara(chave, a->chave) == -1) //Se a chave buscada for menor do que a chave atual
            //Realiza a busca na subárvore da esquerda
            return buscaChave(a->esq, chave, compara);
        else if (compara(chave, a->chave) == 1) //Se a chave buscada for maior do que a chave atual
            //Realiza a busca na subárvore da direita
            return buscaChave(a->dir, chave, compara);
        else //Caso a chave for encontrada
            //Retorna a chave encontrada
            return a->chave;
    }
    else //Se a árvore está vazia ou o elemento não está na árvore
        return NULL;
}

//Função recursiva que realiza a remoção de um elemento da árvore mantendo o balanceamento
AVL *remover(AVL *a, int *h, void *chave, int (*compara)(void *, void *), void (*liberachave)(void *))
{
    if (a) //Se a árvore não está vazia
    {
        if (compara(chave, a->chave) > 0) //Se a chave a ser removida é maior do que a chave atual
        {
            //Chama a função de remoção recursivamente na subarvore direita
            a->dir = remover(a->dir, h, chave, compara, liberachave);

            if (*h != 0) //Caso a altura da árvore seja alterada após a remoção
            {
                switch (a->fb) //Altera o fator de balanceamento de acordo com cada caso
                {
                case -1:
                    a->fb = 0;
                    //Houve alteração na altura
                    *h = 1;
                    break;

                case 0:
                    a->fb = 1;
                    //Não houve alteração na altura
                    *h = 0;
                    break;

                case 1:
                    //Houve necessidade de rotação
                    a = rodaDireitaRemover(a, h);
                    break;

                default:
                    break;
                }
            }
            return a;
        }
        else if (compara(chave, a->chave) < 0) //Se o elemento a ser removido é menor do que a chave atual
        {
            //Chama a função de remoção recursivamente na subarvore esquerda
            a->esq = remover(a->esq, h, chave, compara, liberachave);

            if (*h != 0) //Se houve alteração na altura após a remoção
            {
                switch (a->fb) //Altera o fator de balanceamento de acordo com cada caso
                {
                case 1:
                    a->fb = 0;
                    //Houve alteração na altura
                    *h = 1;
                    break;

                case 0:
                    a->fb = -1;
                    //Não houve alteração na altura
                    *h = 0;
                    break;

                case -1:
                    //Houve necessidade de rotação
                    a = rodaEsquerdaRemover(a, h);
                    break;

                default:
                    break;
                }
            }

            return a;
        }
        else //Se o elemento for encontrado
        {
            if (!a->dir && !a->esq) //Se o elemento for uma folha
            {
                //Libera a memória alocada para a chave
                liberachave(a->chave);
                //Libera a memória alocada para o nó
                free(a);
                //Indica que houve alteração na altura
                *h = 1;
                //Retorna NULL para a chamada recursiva anterior
                return NULL;
            }
            else if (a->dir && a->esq) //Se o elemento tiver a subarvore esquerda e a direita
            {
                //Buscando o predecessor (elemento mais a direita da subarvore esquerda)
                AVL *predecessor = a->esq;

                while (predecessor->dir)
                    predecessor = predecessor->dir;

                //Realizando a troca da chave a ser removida pela chave do predecessor
                void *aux = predecessor->chave;
                predecessor->chave = a->chave;
                a->chave = aux;

                //Chama a função recursivamente na subarvore esquerda
                a->esq = remover(a->esq, h, predecessor->chave, compara, liberachave);

                if (*h != 0) //Caso haja alteração na altura após a remoção
                {
                    switch (a->fb) //Altera o fator de balanceamento de acordo com cada caso
                    {
                    case 1:
                        a->fb = 0;
                        //Houve alteração na altura
                        *h = 1;
                        break;

                    case 0:
                        a->fb = -1;
                        //Não houve alteração na altura
                        *h = 0;
                        break;

                    case -1:
                        //Houve necessidade de rotação
                        a = rodaEsquerdaRemover(a, h);
                        break;

                    default:
                        break;
                    }
                }
                return a;
            }
            else if (a->dir) //Se a árvore tem apenas subarvore direita
            {
                AVL *proximo = a->dir;
                //Libera a memória alocada para a chave
                liberachave(a->chave);
                //Libera a memória alocada para o nó
                free(a);
                //Indica que houve alteração na altura
                *h = 1;
                return proximo;
            }
            else //Se a árvore tem apenas subarvore esquerda
            {
                AVL *proximo = a->esq;
                //Libera a memória alocada para a chave
                liberachave(a->chave);
                //Libera a memória alocada para o nó
                free(a);
                //Indica que a altura foi alterada
                *h = 1;
                return proximo;
            }
        }
    }
    else //Se a árvore está vazia ou não encontrou o elemento
    {
        //Não houve alteração na árvore nem na altura
        *h = 0;
        return NULL;
    }
}

//Função recursiva que libera a memória alocada para cada nó da árvore e suas respectivas chaves
void liberaArvore(AVL *a, void (*liberaChave)(void *))
{
    if (a) //Caso a árvore não esteja vazia
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

/*Função recursiva que realiza a impressão de cada nó da árvore e do seu fator de balanceamento 
aplicando a tabulação de acordo com o nível de cada nó*/
void imprimeArvore(AVL *a, int cont, void (*imprimeChave)(void *))
{
    if (a) //Caso a árvore não esteja vazia
    {

        //Chama a função recursivamente para imprimir a subarvore esquerda
        imprimeArvore(a->esq, cont + 1, imprimeChave);

        //Realiza a tabulação de acordo com o nível
        for (int i = 0; i < cont; i++)
            printf("\t");

        //Utiliza a função de callback para imprimir a chave
        imprimeChave(a->chave);
        //Imprime o fator de balanceamento
        printf(":%d\n", a->fb);
        
        //Chama a função recursivamente para imprimir a subarvore direita
        imprimeArvore(a->dir, cont + 1, imprimeChave);
    }
}