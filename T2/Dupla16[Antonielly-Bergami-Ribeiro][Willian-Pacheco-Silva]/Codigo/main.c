// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Importação da biblioteca
#include "ARN.h"

//Inclusão da biblioteca para lidar com strings
#include "string.h"

/*Estrutura utilizada para armazenar os dados do artigo. Essa estrutura possui alguns campos, o principal deles é
o id, que é um campo do tipo int que armazena a chave de identificação do artigo. Ele deve ser único na árvore.
Os outros campos são utilizadas para armazenar informações de um dado artigo.*/
typedef struct artigo
{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
} Artigo;

//Função que aloca a memóra para um dado artigo.
Artigo *criaArtigo(Artigo a)
{
    //Alocação de memória
    Artigo *novo = (Artigo *)malloc(sizeof(Artigo));
    if (!novo) //Caso ocorra algum erro
    {
        printf("Erro de alocacao de memoria.");
        exit(1);
    }
    //Caso não haja erros, os campos são inicializados.
    novo->id = a.id;
    novo->ano = a.ano;
    strcpy(novo->autor, a.autor);
    strcpy(novo->titulo, a.titulo);
    strcpy(novo->revista, a.revista);
    strcpy(novo->DOI, a.DOI);
    strcpy(novo->palavraChave, a.palavraChave);
    return novo;
}

//Função de callback que imprime o id do artigo
void imprimeChave(void *a)
{
    if (a) //Caso o ponteiro não seja nulo
    {
        Artigo *art = (Artigo *)a; //Realizando o casting para o tipo artigo
        printf("%d", art->id);     //Imprime o id
    }
    else //Caso o ponteiro seja nulo
    {
        printf("A chave nao pode ser impressa.");
    }
}

//Função de callback utilizada para comparar dois artigos
int comparaChave(void *a1, void *a2)
{
    if (a1 && a2) //Caso os dois artigos não sejam nulos
    {
        //Realizando o casting para o tipo artigo
        Artigo *art1 = (Artigo *)a1;
        Artigo *art2 = (Artigo *)a2;

        if (art1->id > art2->id) //Caso o id do primeiro artigo seja maior do que o do segundo
            return 1;
        else if (art1->id < art2->id) //Caso o id do primeiro artigo seja menor do que o do segundo
            return -1;
        else //Caso os ids sejam iguais
            return 0;
    }
    else //Caso algum dos ponteiros seja nulo
    {
        printf("A chave nao pode ser comparada.");
        return -2;
    }
}

//Função de callback que libera a memória alocada para o artigo
void liberaChave(void *a)
{
    if (a) //Caso o ponteiro não seja nulo
    {
        Artigo *art = (Artigo *)a; //Casting para o tipo artigo
        free(art);                 //Libera a memória
    }
    else //Caso o ponteiro seja nulo
    {
        printf("A chave nao pode ser liberada.");
    }
}

//Função de menu que realiza as operações de acordo com a opção escolhida
ARN *menu(ARN *a, int op)
{
    //Declaração das variáveis auxiliares
    Artigo artigoAuxiliar, *artigoBuscado;
    ARN *noBuscado;
    char enter;

    switch (op) //Estrutura de decisão para cada caso do menu
    {
    case 1: //Inserir elemento
        //Leitura dos dados
        printf("\nA opcao selecionada foi: Inserir Artigo.\n\n");
        printf("Digite o id do novo Artigo: ");
        scanf("%d", &artigoAuxiliar.id);
        printf("Digite o ano do novo Artigo: ");
        scanf("%d", &artigoAuxiliar.ano);

        //Lê o enter para limpar o buffer do teclado e permitir a leitura da string a seguir
        scanf("%c", &enter);

        printf("Digite o autor do novo Artigo: ");
        //Esse tipo de scanf permite a leitura de uma string com mais de uma palavra
        scanf("%[^\n]", artigoAuxiliar.autor);

        //Lendo o buffer do teclado
        scanf("%c", &enter);

        printf("Digite o titulo do novo Artigo: ");
        scanf("%[^\n]", artigoAuxiliar.titulo);

        //Lendo o buffer do teclado
        scanf("%c", &enter);

        printf("Digite a revista do novo Artigo: ");
        scanf("%[^\n]", artigoAuxiliar.revista);

        //Lendo o buffer do teclado
        scanf("%c", &enter);

        printf("Digite o DOI do novo Artigo: ");
        scanf("%[^\n]", artigoAuxiliar.DOI);

        //Lendo o buffer do teclado
        scanf("%c", &enter);

        printf("Digite a palavra chave do novo Artigo: ");
        scanf("%[^\n]", artigoAuxiliar.palavraChave);

        //Realizando a busca da chave a ser inserida
        noBuscado = buscaChave(a, &artigoAuxiliar, comparaChave);

        if (noBuscado == &externo) //Caso a chave ainda não exista na árvore
        {
            //Realiza a inserção do elemento na árvore
            a = insercao(a, criaArtigo(artigoAuxiliar), comparaChave, liberaChave);

            //Imprime o elemento inserido
            printf("\nO seguinte Artigo foi cadastrado:\n");
            printf("\nId: %d\n", artigoAuxiliar.id);
            printf("Ano: %d\n", artigoAuxiliar.ano);
            printf("Autor: %s\n", artigoAuxiliar.autor);
            printf("Titulo: %s\n", artigoAuxiliar.titulo);
            printf("Revista: %s\n", artigoAuxiliar.revista);
            printf("DOI: %s\n", artigoAuxiliar.DOI);
            printf("Palavra chave: %s\n", artigoAuxiliar.palavraChave);
        }
        else //Caso a chave já exista na árvore
            printf("\nNao foi possivel cadastrar. O Artigo com chave %d ja foi cadastrado.\n", artigoAuxiliar.id);
        break;

    case 2: //Remover elemento
        //Realizando a leitura dos dados
        printf("\nA opcao selecionada foi: Remover Artigo.\n\n");
        printf("Digite a chave do Artigo a ser removido: ");
        scanf("%d", &artigoAuxiliar.id);

        //Buscando pela chave a ser removida
        noBuscado = buscaChave(a, &artigoAuxiliar, comparaChave);

        if (noBuscado != &externo) //Caso a chave exista na árvore
        {
            // Armazena o artigo a ser removido
            artigoBuscado = (Artigo *)retornaChave(noBuscado);
            artigoAuxiliar.id = artigoBuscado->id;
            artigoAuxiliar.ano = artigoBuscado->ano;
            strcpy(artigoAuxiliar.autor, artigoBuscado->autor);
            strcpy(artigoAuxiliar.titulo, artigoBuscado->titulo);
            strcpy(artigoAuxiliar.revista, artigoBuscado->revista);
            strcpy(artigoAuxiliar.DOI, artigoBuscado->DOI);
            strcpy(artigoAuxiliar.palavraChave, artigoBuscado->palavraChave);

            //Realiza a remoção
            a = remocao(a, noBuscado, liberaChave);

            //Imprime a Artigo removido
            printf("\nO seguinte Artigo foi removido:\n");
            printf("\nId: %d\n", artigoAuxiliar.id);
            printf("Ano: %d\n", artigoAuxiliar.ano);
            printf("Autor: %s\n", artigoAuxiliar.autor);
            printf("Titulo: %s\n", artigoAuxiliar.titulo);
            printf("Revista: %s\n", artigoAuxiliar.revista);
            printf("DOI: %s\n", artigoAuxiliar.DOI);
            printf("Palavra chave: %s\n", artigoAuxiliar.palavraChave);
        }
        else //Caso a chave não esteja na árvore
            printf("\nNao foi possivel remover. O Artigo com chave %d nao foi encontrado.\n", artigoAuxiliar.id);
        break;

    case 3: //Buscar elemento
        //Leitura dos dados
        printf("\nA opcao selecionada foi: Procurar Artigo.\n\n");
        printf("Digite a chave do Artigo a ser buscado: ");
        scanf("%d", &artigoAuxiliar.id);

        //Realizando a busca da chave
        noBuscado = buscaChave(a, &artigoAuxiliar, comparaChave);

        if (noBuscado != &externo) //Caso a chave seja encontrada
        {
            //Obtém a chave do nó
            artigoBuscado = (Artigo *)retornaChave(noBuscado);
            //Imprime as informações do artigo
            printf("\nId: %d\n", artigoBuscado->id);
            printf("Ano: %d\n", artigoBuscado->ano);
            printf("Autor: %s\n", artigoBuscado->autor);
            printf("Titulo: %s\n", artigoBuscado->titulo);
            printf("Revista: %s\n", artigoBuscado->revista);
            printf("DOI: %s\n", artigoBuscado->DOI);
            printf("Palavra chave: %s\n", artigoBuscado->palavraChave);
        }
        else //Caso a chave não esteja na árvore
            printf("\nO Artigo buscado nao foi encontrado.\n");
        break;

    case 4: //Imprimir a árvore
        printf("\nA opcao selecionada foi: Imprimir arvore.\n\n");

        if (a == &externo) //Caso a árvore esteja vazia
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

int main()
{
    //Criação de uma árvore vazia que aponta para o nó externo
    ARN *a = criaArvore();

    int op = 0;
    do
    {
        //Opções do menu
        printf("\n-------Menu-------\n");
        printf("1 - Inserir Artigo\n"); 
        printf("2 - Remover Artigo\n");
        printf("3 - Procurar Artigo\n");
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