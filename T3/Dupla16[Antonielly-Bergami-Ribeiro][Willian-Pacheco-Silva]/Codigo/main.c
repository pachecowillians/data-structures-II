// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Inclusão da biblioteca
#include "Huffman.h"

//Função do menu
void menu(int op)
{
    //Declaração das váriaveis
    char nomeOrigem[100];
    char nomeSaida[100];
    char nomeComprimido[100];
    char nomeDescomprimido[100];
    char enter;
    int letrasDistintas = 0;
    int numeroLetras = 0;
    int tamanhoBinario = 0;

    //switch case para as opções que podem ser escolhidas
    switch (op)
    {
    case 1: //caso 1 - compressão
        //leitura do nome do arquivo que será comprimido
        scanf("%c", &enter);
        printf("\nDigite o nome do arquivo a ser comprimido (txt): ");
        scanf("%[^\n]", nomeOrigem);

        //criação da tabela hash que armazena as repetições dos caracteres
        int *ocorrenciasCaracteres = criaVetorRepeticoes(nomeOrigem, &letrasDistintas, &numeroLetras);

        if (letrasDistintas == 0) //Caso o arquivo não possua letras distintas ele está vazio
        {
            printf("\nO arquivo está vazio!\n");
        }
        else
        {
            //cria o heap mínimo
            Huffman **heapMin = criaHeapMin(ocorrenciasCaracteres, letrasDistintas);
            //cria uma cópia do heap mínimo em forma de vetor estático para mandar para o arquivo
            HuffmanArquivo *heapArquivo = criaHeapEstatico(heapMin, letrasDistintas);
            //cria a tabela hash que relaciona cada caractere com o nó que contém ele na árvore
            Huffman **hashHeap = criaHashHeap(heapMin, letrasDistintas);

            Huffman *arvore = criaArvoreHuffman(heapMin, letrasDistintas); //cria a árvore de Huffman

            printf("\nCódigo de Huffman: \n");
            printf("\nElemento [numero de ocorrencias] : codigo binario\n");

            for (int i = 0; i < 256; i++) //percorre todos os caracteres da tabela ascii
            {
                if (ocorrenciasCaracteres[i] > 0) //caso o caractere possua alguma ocorrência no arquivo
                {
                    //imprime o caractere
                    printf("%c[%d] : ", i, ocorrenciasCaracteres[i]);
                    //imprime o código binário dele extraído da árvore
                    imprimeBinarioCaractere(hashHeap[i], letrasDistintas);
                    printf("\n");
                }
            }

            //converte todo o texto do arquivo de entrada para binário por meio da árvore de Huffman
            char *codigoBinario = criaBinario(nomeOrigem, hashHeap, numeroLetras, &tamanhoBinario, letrasDistintas);

            printf("\n(O codigo de Huffman e a contagem das ocorrencias dos caracteres foram impressos acima)\n");
            //leitura do nome do arquivo de saída
            scanf("%c", &enter);
            printf("\nDigite o nome do arquivo de saida (binario): ");
            scanf("%[^\n]", nomeSaida);

            Cabecalho c;
            c.tamanhoBinario = tamanhoBinario;
            c.tamanhoHeap = letrasDistintas;

            //salva o cabeçalho, o heap e o binário no arquivo compactado
            comprimir(nomeSaida, c, heapArquivo, codigoBinario);

            printf("\nO arquivo %s foi comprimido com sucesso para %s !\n", nomeOrigem, nomeSaida);

            //libera memória alocada
            free(heapMin);
            free(heapArquivo);
            free(codigoBinario);
            liberaArvore(arvore);
        }
        //liberação de memória
        free(ocorrenciasCaracteres);

        break;

    case 2: //caso 2 - descompressão

        //leitura dos nomes dos arquivos
        scanf("%c", &enter);
        printf("\nDigite o nome do arquivo comprimido (binario): ");
        scanf("%[^\n]", nomeComprimido);

        scanf("%c", &enter);
        printf("\nDigite o nome do arquivo resultante (txt): ");
        scanf("%[^\n]", nomeDescomprimido);

        descomprimir(nomeComprimido, nomeDescomprimido); //descomprime o arquivo binário para o arquivo de texto

        printf("\nO arquivo %s foi descomprimido com sucesso para %s !\n", nomeComprimido, nomeDescomprimido);
        break;

    default: //caso a opção escolhida não esteja no menu
        printf("\nA opcao escolhida nao se encontra no menu.\n");
        break;
    }
}

//Função principal
int main()
{
    int op = 0;
    //Laço para escolher a opção do menu
    do
    {
        //Opções do menu
        printf("\n--------- Menu ---------\n\n");
        printf("1 - Comprimir arquivo\n");
        printf("2 - Descomprimir arquivo\n");
        printf("3 - Sair\n");

        //Leitura da opção
        printf("\nEscolha a opcao: ");
        scanf("%d", &op);

        if (op != 3)  //Se a opção selecionada não for a de sair
            menu(op); //chamada do menu

    } while (op != 3); //Permanece no menu enquanto não for selecionada a opção de sair

    return 0;
}
