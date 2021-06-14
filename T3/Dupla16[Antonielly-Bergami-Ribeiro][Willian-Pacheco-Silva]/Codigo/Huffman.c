// Integrantes:
// Antonielly Bergami Ribeiro (2018205200)
// Willian Pacheco Silva (2019107753)

//Inclusão da biblioteca
#include "Huffman.h"

//Função utilizada para criar um novo nó da árvore
Huffman *criaNo(unsigned char caractere, int frequencia)
{
    //aloca memória para um novo nó
    Huffman *novo = (Huffman *)malloc(sizeof(Huffman));
    if (!novo) //caso ocorra algum erro na alocação
    {
        printf("Erro na alocacao de memoria.");
        exit(1);
    }
    //caso contrário, inicializa o nó
    novo->caractere = caractere;
    novo->frequencia = frequencia;
    novo->tipoFilho = 0;

    novo->pai = NULL;
    novo->subarvoreDireita = NULL;
    novo->subarvoreEsquerda = NULL;

    return novo; //retorna o nó criado e inicializado.
}

/*Função auxiliar utilizada para retornar a posição 
do pai de um nó do heap em um vetor*/
int Pai(int i)
{
    return i / 2;
}

/*Função auxiliar utilizada para retornar a posição do 
filho à esquerda de um nó do heap em um vetor*/
int FilhoEsquerdo(int i)
{
    return 2 * i;
}

/*Função auxiliar utilizada para retornar a posição do 
filho à direita de um nó do heap em um vetor*/
int FilhoDireito(int i)
{
    return 2 * i + 1;
}

//Função utilizada para restabelecer as propriedades do heap mínimo
void MinHeapify(Huffman **vetor, int i, int tamanho)
{
    int esquerdo, direito, menor;
    Huffman *aux;
    esquerdo = FilhoEsquerdo(i);
    direito = FilhoDireito(i);

    //condicionais para buscar o menor elemento entre o nó atual e os filhos dele
    if (esquerdo <= tamanho && vetor[esquerdo]->frequencia < vetor[i]->frequencia)
        menor = esquerdo;
    else
        menor = i;

    if (direito <= tamanho && vetor[direito]->frequencia < vetor[menor]->frequencia)
        menor = direito;

    //troca o elemento que se encontra na posicao menor como o elemento que se encontra na posicao i
    if (menor != i)
    {
        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;

        //realiza a recursão para consertar as propriedades de heap nos outros nós
        MinHeapify(vetor, menor, tamanho);
    }
}

///Função para retirar o menor elemento do heap
Huffman *RetiraMinimo(Huffman **a, int *tamanho)
{
    //variavel auxiliar para armazenar o menor elemento do heap
    Huffman *min = 0;
    if (*tamanho < 1) //se o tamanho do heap for menor que 1, apresenta o erro de underflow
    {
        printf("Underflow");
        exit(1);
    }
    //troca o primeiro elemento com o último
    min = a[1];
    a[1] = a[*tamanho];
    //decrementa o tamanho do heap
    *tamanho = *tamanho - 1;
    //restabelece as propriedades do heap mínimo
    MinHeapify(a, 1, *tamanho);
    //retorna o menor elemento do heap
    return min;
}

//Função utilizada para reposicionar a chave
void DecrementaChave(Huffman **a, int i, Huffman *chave)
{
    if (a[i] && chave->frequencia > a[i]->frequencia) //caso a chave armazenada no heap seja maior que a chave atual
    {
        printf("A chave é maior do que a chave atual.");
        exit(1);
    }
    free(a[i]);   //libera a memória antiga da chave atual
    a[i] = chave; //recebe a chave

    /*enquanto a posição do heap for maior do que 1 e a frequencia do pai do elemento atual for menor do que  
    a frequencia dele, o laço é executado*/
    while (i > 1 && a[Pai(i)]->frequencia > a[i]->frequencia)
    {
        //troca o elemento de posição com o pai dele
        Huffman *aux = a[i];
        a[i] = a[Pai(i)];
        a[Pai(i)] = aux;
        //continua o laço, mas agora com o pai do nó atual
        i = Pai(i);
    }
}

//Função para inserir um elemento em um heap
void InserirHeapMinimo(Huffman **a, Huffman *chave, int *tamanho)
{
    //incrementa o tamanho do heap
    *tamanho = *tamanho + 1;

    //aloca memória para o nó na nova posição
    a[*tamanho] = (Huffman *)malloc(sizeof(Huffman));

    if (!a[*tamanho]) //caso ocorra erro de alocação de memória
    {
        printf("Erro de alocacao de memoria.");
        exit(1);
    }

    //atribui ao novo espaço vazio no vetor o maior valor possível
    a[*tamanho]->frequencia = INT_MAX;

    //chama função DecrementaChave
    DecrementaChave(a, *tamanho, chave);
}

//Função para inserir os elementos distintos, obtidos do arquivo, no heap
Huffman **criaHeapMin(int *repeticoes, int letrasDistintas)
{
    //aloca memória para um vetor de ponteiros do tipo huffman, que será o heap mínimo
    Huffman **heapMin = (Huffman **)calloc((letrasDistintas + 1), sizeof(Huffman *));
    int tamanhoFila = 0;
    for (int i = 0; i < 256; i++) //percorre todas os 256 caracteres da tabela ascii
    {
        if (repeticoes[i] > 0) //caso o caractere esteja no txt
        {
            //cria um novo nó da árvore com o caractere e o número de repetições dele
            Huffman *novoNo = criaNo((unsigned char)i, repeticoes[i]);
            if (!novoNo) //caso ocorra erro de alocação de memória
            {
                printf("Erro de alocacao de memoria");
                exit(1);
            }

            //insere o novo nó criado no heap mínimo
            InserirHeapMinimo(heapMin, novoNo, &tamanhoFila);
        }
    }
    //retorna o heap criado
    return heapMin;
}

/*Função que copia as informações dos nós da árvore armazenados no heap por meio de ponteiros 
para um vetor estático (que não seja um vetor de ponteiros) que possa ser armazenado no arquivo*/
HuffmanArquivo *criaHeapEstatico(Huffman **heapMin, int tamanhoHeap)
{
    //aloca a memória para o vetor que será o heap
    HuffmanArquivo *heapArquivo = (HuffmanArquivo *)malloc((tamanhoHeap + 1) * sizeof(HuffmanArquivo));
    for (int i = 1; i <= tamanhoHeap; i++) //percorre todo o heap
    {
        //atribui os valores ao heap
        heapArquivo[i].caractere = heapMin[i]->caractere;
        heapArquivo[i].frequencia = heapMin[i]->frequencia;
    }
    //retorna o heap com os dados dos caracteres pronto para ser inserido no arquivo
    return heapArquivo;
}

/*Função utilizada para criar uma tabela hash que relaciona cada caractere com um 
ponteiro que aponta para o nó que guarda aquele caractere na árvore*/
Huffman **criaHashHeap(Huffman **heap, int tamanhoHeap)
{
    //aloca memória para a tabela hash
    Huffman **hashHeap = (Huffman **)calloc(256, sizeof(Huffman *));

    for (int i = 1; i <= tamanhoHeap; i++) //laço para percorrer o heap
    {
        //para cada caractere no heap, armazena na tabela o ponteiro que aponta para o nó dele na árvore
        hashHeap[heap[i]->caractere] = heap[i];
    }
    //retorna a tabela hash
    return hashHeap;
}

//Função utilizada para gerar a árvore de huffman
Huffman *criaArvoreHuffman(Huffman **heapMin, int tamanhoHeap)
{
    while (tamanhoHeap > 1) //enquanto o tamanho do heap for maior do que 1
    {
        //retira os dois elementos de menor frequência do heap
        Huffman *m1 = RetiraMinimo(heapMin, &tamanhoHeap);
        Huffman *m2 = RetiraMinimo(heapMin, &tamanhoHeap);

        //aloca memória para um novo nó para unir m1 e m2
        Huffman *novoNo = criaNo((unsigned char)0, m1->frequencia + m2->frequencia);

        //realiza os apontamentos
        novoNo->pai = NULL; //garante que o novo nó não terá pai (pois a raiz não tem pai)

        m1->tipoFilho = 0;              //m1 será o filho á esquerda do novo nó (0)
        m1->pai = novoNo;               //atualiza o pai de m1
        novoNo->subarvoreEsquerda = m1; //faz m1 ser o filho à esquerda do novo nó

        m2->tipoFilho = 1;             //m2 será o filho à direita do novo nó (1)
        m2->pai = novoNo;              //atualiza o pai de m2
        novoNo->subarvoreDireita = m2; //faz m2 ser o filho à direita do novo nó

        //Insere o novo nó no heap
        InserirHeapMinimo(heapMin, novoNo, &tamanhoHeap);
    }
    //retorna a raiz da árvore caso o heap só tenha um elemento (a raiz)
    return RetiraMinimo(heapMin, &tamanhoHeap);
}

//Função utilizada para criar uma tabela hash que relaciona o caractere com o número de repetições dele no arquivo
int *criaVetorRepeticoes(char *nomeArquivo, int *letrasDistintas, int *quantidadeCaracteres)
{
    char ch;
    //aloca a memória para a tabela hash com os 256 caracteres da tabela ascii
    int *repeticoes = (int *)calloc(256, sizeof(int));

    //leitura do arquivo
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) //caso não encontre o arquivo
    {
        printf("\nErro ao abrir o arquivo. Esse arquivo nao foi encontrado.\n");
        exit(1);
    }
    while ((ch = fgetc(fp)) != EOF) //lê o arquivo caractere por caractere
    {
        unsigned char c = ch;      //utilização do unsigned para garantir que os caracteres tenham apenas códigos positivos
        if (repeticoes[c] == 0)    //caso esse caractere ainda não tenha sido encontrado no arquivo
            (*letrasDistintas)++;  //incrementa o número de caracteres distintos
        repeticoes[c]++;           //incrementa o número de repetições daquele caractere na tabela hash
        (*quantidadeCaracteres)++; //incrementa o contador da quantidade de caracteres do arquivo
    }
    fclose(fp);        //fecha o arquivo
    return repeticoes; //retorna a tabela hash
}

//Função para preencher o byte através da árvore
void codificaChar(Huffman *arvore, char *codBin, int *posicaoVetor, int *numeroBits, int *tamanhoBinario, int letrasDistintas)
{
    if (arvore->pai) //enquanto o nó da árvore tiver pai
    {
        //chama a função recursivamente percorrendo da folha até a raiz
        codificaChar(arvore->pai, codBin, posicaoVetor, numeroBits, tamanhoBinario, letrasDistintas);
        if (*numeroBits == 8) //se o byte encher
        {
            (*posicaoVetor)++; //desloca para a próxima posição do vetor
            *numeroBits = 0;   //começa o processo novamente no bit 0
        }
        codBin[*posicaoVetor] = codBin[*posicaoVetor] << 1;    //desloca os bits para a esquerda
        if (arvore->tipoFilho)                                 //se for um filho à direita
            codBin[*posicaoVetor] = codBin[*posicaoVetor] ^ 1; //escreve o bit 1 no ultimo bit
        (*numeroBits)++;                                       //numero de bits é incrementado
        (*tamanhoBinario)++;                                   //tamanho do binário é incrementado
    }
    else if (!arvore->pai && letrasDistintas == 1) //caso a árvore só tenha um nó que é a própria raiz
    {
        if (*numeroBits == 8) //caso o byte esteja cheio
        {
            (*posicaoVetor)++; //desloca para a próxima posição do vetor
            *numeroBits = 0;   //rertorna para o primeiro bit
        }
        codBin[*posicaoVetor] = codBin[*posicaoVetor] << 1;    //desloca os bits para a esquerda
        if (arvore->tipoFilho)                                 //se for um filho à direita
            codBin[*posicaoVetor] = codBin[*posicaoVetor] ^ 1; //escreve o bit 1 no ultimo bit
        (*numeroBits)++;                                       //incrementa o numero de bits
        (*tamanhoBinario)++;                                   //incrementa o tamanho do binário
    }
}

//Função para converter os caracteres do arquivo para o código binário
char *criaBinario(char *nomeArquivo, Huffman **hashHeap, int numeroLetras, int *tamanhoBinario, int letrasDistintas)
{
    char ch;
    char *codBin = (char *)calloc(numeroLetras, sizeof(char));
    FILE *fp = fopen(nomeArquivo, "r"); //abre o arquivo para leitura
    if (!fp)                            //caso ocorra erro para abrir o arquivo
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    int bitsOcupados = 0;
    int posicaoVetor = 0;
    while ((ch = fgetc(fp)) != EOF) //lê o arquivo caractere por caractere
    {
        //utilizou-se o unsigned para garantir que os códigos dos caracteres sejam inteiros
        unsigned char c = ch;
        //ponteiro que aponta para a folha que contém aquele caractere
        Huffman *arvore = hashHeap[c];
        //acrescenta em codBin o código binário correspondente ao caractere lido
        codificaChar(arvore, codBin, &posicaoVetor, &bitsOcupados, tamanhoBinario, letrasDistintas);
    }
    fclose(fp);    //fecha o arquivo
    return codBin; //retorna o código binário
}

//Função utilizada para comprimir o arquivo
void comprimir(char *nomeArquivo, Cabecalho cab, HuffmanArquivo *heapEstatico, char *codigoBinario)
{

    //quantidade de bytes necessários para armazenar o binário
    int numeroBytes = cab.tamanhoBinario / 8;
    //se a divisão não for exata, é necessário utilizar mais um byte para armazenar o resto dos bits
    if (cab.tamanhoBinario % 8 > 0)
    {
        numeroBytes++;
    }

    FILE *fp = fopen(nomeArquivo, "wb+");                                  //abre o aquivo para escrever em binário
    fwrite(&cab, sizeof(Cabecalho), 1, fp);                                //escreve o cabeçalho
    fwrite(heapEstatico, sizeof(HuffmanArquivo), cab.tamanhoHeap + 1, fp); //escreve o heap
    fwrite(codigoBinario, sizeof(char), numeroBytes, fp);                  //escreve o código binário
    fclose(fp);                                                            //fecha o arquivo
}

//Função utilizada para descomprimir o arquivo
void descomprimir(char *arquivoCompactado, char *arquivoDestino)
{
    Cabecalho c;

    //Abre o arquivo com o modo de leitura binária
    FILE *fp = fopen(arquivoCompactado, "rb");
    if (!fp) //caso ocorra algum problema para abrir o arquivo
    {
        printf("\nErro ao abrir o arquivo. O arquivo %s nao existe.\n", arquivoCompactado);
        exit(1);
    }

    fread(&c, sizeof(Cabecalho), 1, fp); //lê o cabeçalho do arquivo
    fclose(fp);                          //fecha o arquivo

    HuffmanArquivo heapArquivo[c.tamanhoHeap + 1];

    fp = fopen(arquivoCompactado, "rb"); //Abre o arquivo
    if (!fp)                             //caso ocorra algum erro na abertura
    {
        printf("\nErro ao abrir o arquivo. O arquivo %s nao existe.\n", arquivoCompactado);
        exit(1);
    }

    //posiciona o ponteiro do arquivo na posição certa depois do cabeçalho
    fseek(fp, sizeof(Cabecalho), SEEK_SET);
    fread(&heapArquivo, sizeof(HuffmanArquivo), c.tamanhoHeap + 1, fp); //lê o heap do arquivo
    fclose(fp);

    Huffman *heapMin[c.tamanhoHeap + 1];

    /*como o heap do arquivo não era de ponteiros, o heap foi convertido para
    um heap de ponteiros para nó da árvore para poder criar a árvore novamente*/
    for (int i = 1; i <= c.tamanhoHeap; i++)
    {
        heapMin[i] = criaNo(heapArquivo[i].caractere, heapArquivo[i].frequencia);
    }

    Huffman *arvore = criaArvoreHuffman(heapMin, c.tamanhoHeap); //recria a árvore

    int binarioPercorrido = 0;
    unsigned char ch;
    Huffman *aux = arvore;

    /*abre o arquivo de texto onde serão gravadas as informações do arquivo 
    compactado. Caso ele não exista, ele será criado*/
    FILE *fpDestino = fopen(arquivoDestino, "w+");
    if (!fp) //caso ocorra algum erro na abertura
    {
        printf("\nErro ao abrir o arquivo. O arquivo %s nao existe.\n", arquivoDestino);
        exit(1);
    }

    fp = fopen(arquivoCompactado, "rb"); //abre o arquivo compactado
    if (!fp)                             //caso ocorra algum erro
    {
        printf("\nErro ao abrir o arquivo. O arquivo %s nao existe.\n", arquivoCompactado);
        exit(1);
    }
    //posiciona o ponteiro do arquivo na posição certa depois do cabeçalho e do heap
    fseek(fp, sizeof(Cabecalho) + (c.tamanhoHeap + 1) * sizeof(HuffmanArquivo), SEEK_SET);

    while (fread(&ch, sizeof(unsigned char), 1, fp)) //lê o arquivo byte por byte
    {
        if (binarioPercorrido + 8 < c.tamanhoBinario) //se não for o último byte do arquivo
        {
            for (int i = 7; 0 <= i; i--) //percorre todos os bits daquele byte
            {
                if (aux->subarvoreDireita && aux->subarvoreEsquerda) //percorre a árvore dependendo do valor do bit
                {
                    if ((ch >> i) & 0x01) //caso o bit seja 1
                        aux = aux->subarvoreDireita;
                    else //caso o bit seja 0
                        aux = aux->subarvoreEsquerda;
                }

                if (!aux->subarvoreDireita && !aux->subarvoreDireita) //caso se chegue a uma folha
                {
                    fputc(aux->caractere, fpDestino); //escreve o caractere da folha no arquivo de destino
                    aux = arvore;                     //o ponteiro volta a apontar para a raiz da árvore
                }
            }
            binarioPercorrido += 8; //incrementa em um byte a quantidade de bits que já foi percorrida
        }
        else //se for o último byte do arquivo
        {
            //percorre o byte apenas na parte que falta pra competar o total
            for (int i = c.tamanhoBinario - binarioPercorrido - 1; 0 <= i; i--)
            {
                if (aux->subarvoreDireita && aux->subarvoreEsquerda) //percorre a árvore de acordo com o valor do bit
                {
                    if ((ch >> i) & 0x01) //caso o bit seja 1
                        aux = aux->subarvoreDireita;
                    else //caso o bit seja 0
                        aux = aux->subarvoreEsquerda;
                }

                if (!aux->subarvoreDireita && !aux->subarvoreDireita) //caso se chegue a uma folha
                {
                    fputc(aux->caractere, fpDestino); //escreve o caractere da folha no arquivo de destino
                    aux = arvore;                     //o ponteiro volta a apontar para a raiz da árvore
                }
            }
        }
    }
    fclose(fp);           //fecha o arquivo compactado
    fclose(fpDestino);    //fecha o  arquivo de destino
    liberaArvore(arvore); //libera a memória alocada para os nós da árvore
}

//Função utilizada para liberar a mamória alocada para uma árvore
void liberaArvore(Huffman *a)
{
    if (a) //se a árvore não estiver vazia
    {
        liberaArvore(a->subarvoreEsquerda); //percorre a subárvore da esquerda
        liberaArvore(a->subarvoreDireita);  //percorre a subárvore da direita
        free(a);                            //libera a memória do nó
    }
}

//Função utilizada para imprimir a sequência binária que representa um caractere através da árvore
void imprimeBinarioCaractere(Huffman *arvore, int letrasDistintas)
{
    if (arvore->pai) //se o nó tiver pai
    {
        imprimeBinarioCaractere(arvore->pai, letrasDistintas); //chama a função recursivamete para o pai do nó
        printf("%d", arvore->tipoFilho);                       //imprime o bit
    }
    else if (!arvore->pai && letrasDistintas == 1) //caso a árvore não tenha pai e o arquivo tenha apenas uma letra distinta
    {
        printf("%d", arvore->tipoFilho); //imprime o bit
    }
}