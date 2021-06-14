// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Importação da biblioteca
#include "AVL.h"

/*Estrutura utilizada para armazenar os dados. Essa estrutura possui os campos id, altura e largura.
id: Campo do tipo int que armazena a chave de identificação da mesa. Ele deve ser único na árvore.
altura: Campo do tipo float que armazena a altura da mesa.
largura: Campo do tipo float que armazena a largura da mesa.*/
typedef struct mesa
{
    int id;
    float altura;
    float largura;
} Mesa;

//Função de callback utilizada para comparar duas mesas
int compara(void *mesa1, void *mesa2)
{
    if (mesa1 && mesa2) //Caso nenhuma das duas mesas seja nula
    {
        //Realizando o casting de void * para Mesa *
        Mesa *m1 = (Mesa *)mesa1;
        Mesa *m2 = (Mesa *)mesa2;

        if (m1->id > m2->id) //Caso a chave da primeira mesa seja maior do que a da segunda
            return 1;
        else if (m1->id < m2->id) //Caso a chave da primeira mesa seja menor do que a da segunda
            return -1;
        else //Caso a chave da primeira mesa seja igual a da segunda
            return 0;
    }
    else //Caso alguma mesa seja nula, a comparação é inválida
        printf("\nComparacao invalida!\n");

    return 0;
}

//Função de callback que imprime o id da mesa
void imprimeChave(void *chave)
{
    //Realizando o casting de void * para Mesa *
    Mesa *m = (Mesa *)chave;

    if (m) //Caso a mesa não seja nula
        printf("[%d]", m->id);
    else //Caso a mesa seja nula
        printf("Chave nao encontrada.");
}

//Função de callback que libera a memória alocada para a mesa
void liberaChave(void *chave)
{
    //Realizando o casting de void * para Mesa *
    Mesa *m = (Mesa *)chave;
    //Liberando a memória alocada
    free(m);
}

//Função que aloca a memóra para uma mesa
Mesa *criaMesa(Mesa m)
{
    //Alocando a memória para a mesa
    Mesa *nova = (Mesa *)malloc(sizeof(Mesa));

    if (!nova) //Caso ocorra algum erro de alocação
    {
        printf("Erro de alocacao de memoria.");
        exit(1);
    }

    //Inicializando os atributos
    nova->id = m.id;
    nova->altura = m.altura;
    nova->largura = m.largura;

    return nova;
}

//Função de menu que realiza as operações de acordo com a opção escolhida
AVL *menu(AVL *a, int op)
{
    //Declaração das variáveis
    int h = 0;
    Mesa m;
    void *mesa = NULL;
    Mesa *mesaBuscada = NULL;

    switch (op) //Estrutura de decisão para cada caso do menu
    {
    case 1: //Inserir elemento
        //Leitura dos dados
        printf("\nA opcao selecionada foi: Inserir mesa.\n\n");
        printf("Digite a chave da nova mesa: ");
        scanf("%d", &m.id);
        printf("Digite a altura da nova mesa: ");
        scanf("%f", &m.altura);
        printf("Digite a largura da nova mesa: ");
        scanf("%f", &m.largura);

        //Realizando a busca da chave a ser inserida
        mesa = buscaChave(a, &m, compara);
        mesaBuscada = (Mesa *)mesa;

        if (!mesaBuscada) //Caso a chave ainda não exista na árvore
        {
            //Realiza a inserção do elemento na árvore
            a = insereAVL(a, &h, criaMesa(m), compara, liberaChave);

            //Imprime o elemento inserido
            printf("\nA seguinte mesa foi cadastrada:\n");
            printf("\nChave: %d\n", m.id);
            printf("Altura: %.2f\n", m.altura);
            printf("Largura: %.2f\n", m.largura);
        }
        else //Caso a chave já exista na árvore
            printf("\nNao foi possivel cadastrar. A mesa com chave %d ja foi cadastrada.\n", m.id);
        break;

    case 2: //Remover elemento
        //Realizando a leitura dos dados
        printf("\nA opcao selecionada foi: Remover mesa.\n\n");
        printf("Digite a chave da mesa a ser removida: ");
        scanf("%d", &m.id);

        //Buscando pela chave a ser removida
        mesa = buscaChave(a, &m, compara);
        mesaBuscada = (Mesa *)mesa;

        if (mesaBuscada) //Caso a chave já exista na árvore
        {
            Mesa mesaRemovida;
            mesaRemovida.id = mesaBuscada->id;
            mesaRemovida.altura = mesaBuscada->altura;
            mesaRemovida.largura = mesaBuscada->largura;

            //Realiza a remoção
            a = remover(a, &h, &m, compara, liberaChave);

            //Imprime a mesa removida
            printf("\nA seguinte mesa foi removida:\n");
            printf("\nChave: %d\n", mesaRemovida.id);
            printf("Altura: %.2f\n", mesaRemovida.altura);
            printf("Largura: %.2f\n", mesaRemovida.largura);
        }
        else //Caso a chave não esteja na árvore
            printf("\nNao foi possivel remover. A mesa com chave %d nao foi encontrada.\n", m.id);
        break;

    case 3: //Buscar elemento
        //Leitura dos dados
        printf("\nA opcao selecionada foi: Procurar mesa.\n\n");
        printf("Digite a chave da mesa a ser buscada: ");
        scanf("%d", &m.id);

        //Realizando a busca da chave
        mesa = buscaChave(a, &m, compara);
        mesaBuscada = (Mesa *)mesa;

        if (mesaBuscada) //Caso a chave seja encontrada
        {
            printf("\nChave: %d\n", mesaBuscada->id);
            printf("Altura: %.2f\n", mesaBuscada->altura);
            printf("Largura: %.2f\n", mesaBuscada->largura);
        }
        else //Caso a chave não esteja na árvore
            printf("\nA mesa buscada nao foi encontrada.\n");
        break;

    case 4: //Imprimir a árvore

        printf("\nA opcao selecionada foi: Imprimir arvore.\n\n");

        if (!a) //Caso a árvore esteja vazia
            printf("A arvore esta vazia.\n");
        else //Caso a árvore possua algum elemento
            imprimeArvore(a, 1, imprimeChave);
        break;

    default: //Caso a opção escolhida não esteja no menu
        printf("\nA opcao escolhida nao se encontra no menu.\n");
        break;
    }
    return a;
}

//Função principal do programa
int main()
{
    //Inicializando uma árvore vazia
    AVL *a = NULL;

    int op = 0;
    do
    {
        //Opções do menu
        printf("\n-------Menu-------\n");
        printf("1 - Inserir Mesa\n");
        printf("2 - Remover Mesa\n");
        printf("3 - Procurar Mesa\n");
        printf("4 - Imprimir Arvore\n");
        printf("5 - Sair\n");

        //Leitura da opção
        printf("Escolha a opcao: ");
        scanf("%d", &op);

        if (op != 5) //Se a opção selecionada não for a de sair
            a = menu(a, op);

    } while (op != 5); //Permanece no menu enquanto não for selecionada a opção de sair

    //Libera a memória alocada para a árvore
    liberaArvore(a, liberaChave);

    return 0;
}