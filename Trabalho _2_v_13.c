#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stddef.h>
#include <time.h>

//********************* TRABALHO 2 *******************************
// **************** LISTA DE CLIENTES ****************************
//****************************************************************

//Caso o usuario inicie uma lista sem usar dados do txt e depois resolva abrir o txt,
//o programa ira anexar os dados do txt a lista ja existente e nenhum dado sera perdido

int foiOrdenado=0;//foiOrdenado -> para dizer que a sequencia esta ordenada (VARIAVEL GLOBAL)

typedef struct dados {
        char nom[50];//nome do funcionario
        int rg;
} Dados;

typedef struct encadeada {
        Dados node;
        struct encadeada *anterior;
        struct encadeada *proximo;
}Encadeada;

typedef struct header {
    Encadeada *primeiro;
    Encadeada *ultimo;
    int numElementos;
}Header;

void procurarRgDadoEncadeada_BuscaBinaria (Encadeada *lista,Header *head, Encadeada **vetor, int *contComparacoes, int rg);
void procurarRgDadoEncadeada_BuscaSequencial (Encadeada *lista,Header *head, int *contComparacoes, int rg);
void imprimirVetorListaEncadeada (Header *head, Encadeada **vetor);
void ordenarListaEncadeada_Mergesort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor,  int posicaoInicio, int posicaoFim);
void ordenarListaEncadeada_Quicksort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor, int inicio, int fim);
void ordenarListaEncadeada_Shellsort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor);
void ordenarListaEncadeada_Bubble (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor);
void ordenarListaEncadeada_Insertion (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor);
void ordenarListaEncadeada_Selection (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor);
void inserirNoPosicaoDadaListaEncadeada (Encadeada *lista,Header *head, char nome[50], int rg, int *contMovimentos);
void insereElementoInicioListaEncadeada(Encadeada *lista,Header *head, char nome[50], int rg, int *contMovimentos);
void insereElementoFinalListaEncadeada(Encadeada *lista,Header *head, char nome[50], int rg);
void retirarNoInicioListaEncadeada( Encadeada *lista,Header *head);
void retirarFinalListaEncadeada( Encadeada *lista,Header *head);
void retirarNoPosicaoDadaListaEncadeada( Encadeada *lista,Header *head, int *contMovimento);
void gravarArquivoEncadeada(Encadeada *lista,Header *head);
void lerArquivoSalvarDadosEncadeada(FILE *fp, Header *head, Encadeada* lista);
void imprimeListaEncadeada (Encadeada *lista, Header *head);
void limparLista(Header *head);
void transformarListaEncadeadaEmVetor(Encadeada *lista,Header *head, Encadeada **vetor );
void transformarVetorEmListaEncadeada(Encadeada *lista, Header *head, Encadeada **vetor );

void procurarRgDadoSequencial_BuscaSequencial (int *tam, Dados* node, int *contComparacoes, int rg);
void procurarRgDadoSequencial_BuscaBinaria (int *tam, Dados* node, int *contComparacoes, int rg);
void ordenarListaSequencial_Mergesort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes, int posicaoInicio, int posicaoFim);
void ordenarListaSequencial_Quicksort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes, int inicio, int fim);
void ordenarListaSequencial_Shellsort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes);
void ordenarListaSequencial_Bubble (int *tam, Dados* node, int *contMovimentos, int *contComparacoes);
void ordenarListaSequencial_Insertion (int *tam, Dados* node, int *contMovimentos, int *contComparacoes);
void ordenarListaSequencial_Selection (int *tam, Dados* node, int *contMovimentos, int *contComparacoes);
void imprimeListaSequencial (int *tam, Dados* node);
void lerArquivoSalvarDadosSequencial(FILE *fp, int *tam, Dados* node, int *ultimo);
void inserirNoInicioListaSequencia (int *tam, Dados* node, int *ultimo, int *contMovimentos);
void retirarNoInicioListaSequencia (int *tam, Dados* node, int *contMovimentos);
void gravarArquivoSequencia( int *tam, Dados* node);
void inserirFinalListaSequencia (int *tam, Dados* node, int *ultimo);
void retirarFinalListaSequencia (int *tam, Dados* node);
void inserirNoPosicaoDadaListaSequencial (int *tam, Dados* node, int *ultimo, int *contMovimentos);
void retirarNoPosicaoDadaListaSequencial (int *tam, Dados* node, int *contMovimentos);

int main()
{
    //***********   VARIAVEIS DOS DOIS TIPOS DE LISTA (Sequencial e encadeada) ************
    int contMovimentos=0, contComparacoes=0; //variaveis contadoras de movimentos e comparações
    FILE *fp; // arquivo txt que sera aberto
    int opcaoArquivo; // numero do arquivo de texto que sera lido
    int opcaoQueFazer; // funcao a ser escolhida (inserir, retirar, procurar, etc)
    int opcaoLista; // (1) para lista sequencial e (2) para lista encadeada
    //int foiOrdenado; // declarada acima - variavel global
    int fimPrograma=0; // fim = 1 -> terminar programa
    int i, rg, ultimo=0;
    char nomeArquivo[20]; //nome do arquivo de texto que sera aberto para leitura dos dados
    int nome[50];
    char opcaoOrdenar; // seleciona o tipo de ordenação: selection, insertion, etc
    int tempo; //variavel que calcula o tempo de execucao de uma funcao
    clock_t  inicioTempo, fimTempo;

    //++++++ ABAIXO--> ESCOLHER TIPO DE LISTA +++++++++++++++++++++
    printf("\nQual lista: ( 1 ) sequencial  ( 2 ) encadeada     ");
    scanf ("%d", &opcaoLista);
    while (opcaoLista > 2|| opcaoLista < 1){
        printf("\nNUMERO INVALIDO");
        printf("\nQual lista: ( 1 ) sequencia  ( 2 ) encadeada");
        scanf ("%d", &opcaoLista);
    }

    //***********   VARIAVEIS DO TIPO DE LISTA 1 - Sequencial ************                                                  //ultimo = ultima posicao ocupada no vetor da lista sequencial
    int tam=0;
    Dados *node; // vetor para lista sequencial
    node = (Dados*)malloc (tam*sizeof(Dados));
    if(node == NULL)
        printf("Sem espaço suficiente\n");


    //***********   VARIAVEIS DO TIPO DE LISTA 2 - Encadeada ************
    Encadeada *lista;
    lista = (Encadeada*)malloc(sizeof(Encadeada));
    Header *head;
    head = (Header*)malloc(sizeof(Header));
    lista->proximo = NULL;
    head->primeiro=NULL;
    head->ultimo = NULL;
    head->numElementos = 0;
    Encadeada **vetor;//vetor que guarda os enderecos da lista encadeada
    vetor = (Encadeada**)malloc((head->numElementos)* sizeof(Encadeada*));


// +++++++++++++++   INICIO ++++++++++++++++
    //abaixo: usuário escolhe o que deseja fazer
    while (fimPrograma==0){
        printf("\n\nDigine o que gostaria de fazer, sendo:\n"
           "(1) INSERCAO de um no no INICIO da lista\n"
           "(2) INSERCAO de um no no FIM da lista\n"
           "(3) INSERCAO de um no na POSICAO N\n"
           "(4) RETIRAR um no do INICIO da lista e apresentar o valor (nome e RG)\n"
           "(5) RETIRAR um no no FIM da lista e apresentar o valor (nome e RG)\n"
           "(6) RETIRAR um no na POSICAO N e apresentar o valor (nome e RG)\n"
           "(7) PROCURAR um no com o campo RG \n"
           "(8) ORDENAR a lista\n"
           "(9) SALVAR a lista em um ARQUIVO\n"
           "(10) LER a lista de um ARQUIVO\n"
           "(11) SAIR\n");
        scanf ("%d", &opcaoQueFazer);
        while (opcaoQueFazer > 11){
            printf("\nNUMERO INVALIDO\n");
            printf("\n\nDigine o que gostaria de fazer, sendo:\n"
               "(1) INSERCAO de um no no INICIO da lista\n"
               "(2) INSERCAO de um no no FIM da lista\n"
               "(3) INSERCAO de um no na POSICAO N\n"
               "(4) RETIRAR um no do INICIO da lista e apresentar o valor (nome e RG)\n"
               "(5) RETIRAR um no no FIM da lista e apresentar o valor (nome e RG)\n"
               "(6) RETIRAR um no na POSICAO N e apresentar o valor (nome e RG)\n"
               "(7) PROCURAR um no com o campo RG \n"
               "(8) ORDENAR a lista\n"
               "(9) SALVAR a lista em um ARQUIVO\n"
               "(10) LER a lista de um ARQUIVO\n"
               "(11) SAIR\n");
        scanf ("%d", &opcaoQueFazer);
        }
    // **************** EXECUTAR FUNÇÃO SELECIONADA ***********************************************
    //abaixo, programa verifica tipo de lista escolhida e qual funcao foi escolhida para chamar as funcoes

    //********************* 1 - INSERIR NO INICIO DA LISTA ****************************************
        if (opcaoQueFazer==1){
            if (opcaoLista==1){
                contMovimentos=0;
                node = (Dados*)realloc (node, (tam+1)*sizeof(Dados));
                if(node == NULL)
                    printf("Sem espaço suficiente\n");
                inicioTempo = clock();
                inserirNoInicioListaSequencia (&tam, node, &ultimo, &contMovimentos);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else {
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor );
                contMovimentos=0;
                printf("\nDigite o nome   ");
                scanf("%s", &nome);
                nome[strlen(nome)]='\0';
                printf("\nDigite RG   ");
                scanf ("%d", &rg);
                inicioTempo = clock();
                insereElementoInicioListaEncadeada(lista,head, nome, rg, &contMovimentos);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaEncadeada(lista, head);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
                }
            }

        else if (opcaoQueFazer==2){
            if (opcaoLista==1){
                contMovimentos=0;
                node = (Dados*)realloc (node, (tam+1)*sizeof(Dados));
                if(node == NULL)
                    printf("Sem espaço suficiente\n");
                inicioTempo = clock();
                inserirFinalListaSequencia(&tam, node, &ultimo);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                //imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d)  e tempo = T(%d)********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else{
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor );
                printf("\nDigite o nome   ");
                scanf("%s", &nome);
                nome[strlen(nome)]='\0';
                printf("\nDigite RG   ");
                scanf ("%d", &rg);
                inicioTempo = clock();
                insereElementoFinalListaEncadeada (lista,head, nome, rg);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaEncadeada(lista, head);
                printf("\n\n*****  Foram realizado(s) 1 movimento(s): M(1) e tempo = T(%d)  ********\n\n", tempo);//1 pois apenas último node tem o valor proximo alterado
                system("pause");
            }
        }
        else if(opcaoQueFazer==3){
            if (opcaoLista==1){
                contMovimentos = 0;
                node = (Dados*)realloc (node, (tam+1)*sizeof(Dados));
                if(node == NULL)
                    printf("Sem espaço suficiente\n");
                inicioTempo = clock();
                inserirNoPosicaoDadaListaSequencial(&tam, node, &ultimo, &contMovimentos);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                //imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else{
                if (head->numElementos>0){
                    if (foiOrdenado==1)
                        transformarVetorEmListaEncadeada(lista, head, vetor );
                    contMovimentos = 0; //usei a mesma variavel que contava movimentos, para nao precisar criar outra
                    inicioTempo = clock();
                    printf("\nDigite o nome   ");
                    scanf("%s", &nome);
                    nome[strlen(nome)]='\0';
                    printf("\nDigite RG   ");
                    scanf ("%d", &rg);
                    inserirNoPosicaoDadaListaEncadeada (lista,head, nome, rg, &contMovimentos);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    imprimeListaEncadeada(lista, head);
                    printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d)   e 1 movimento M(1)  e tempo = T(%d)********\n\n", contMovimentos, contMovimentos, tempo);
                    //usei a mesma variavel que contava movimentos, para nao precisar criar outra
                    system("pause");
                }
                else{
                    printf("lista vazia    ");
                    system("pause");
                }
            }
        }
        else if (opcaoQueFazer==4){
            if (opcaoLista==1){
                contMovimentos = 0;
                inicioTempo = clock();
                retirarNoInicioListaSequencia(&tam, node, &contMovimentos);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                //imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else{
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor );
                inicioTempo = clock();
                retirarNoInicioListaEncadeada(lista,head);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaEncadeada(lista, head);
                printf("\n\n*****  Foram realizado(s) 1 movimento(s): M(1)  e tempo = T(%d)********\n\n", tempo);//fixei um movimento pq apenas um node teve proximo e aterior trocado
                system("pause");
            }
        }
        else if (opcaoQueFazer==5){
            if (opcaoLista==1){
                contMovimentos = 0;
                inicioTempo = clock();
                retirarFinalListaSequencia(&tam, node);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else {
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor );
                inicioTempo = clock();
                retirarFinalListaEncadeada(lista,head);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaEncadeada(lista, head);
                printf("\n\n*****  Foram realizado(s) 1 movimento(s): M(1) e tempo = T(%d) ********\n\n", tempo);//fixei um movimento pq apenas um node teve proximo e aterior trocado
                system("pause");
            }
        }
        else if (opcaoQueFazer==6){
            if (opcaoLista==1){
                contMovimentos = 0;
                inicioTempo = clock();
                retirarNoPosicaoDadaListaSequencial(&tam, node, &contMovimentos);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d movimento(s): M(%d) e tempo = T(%d) ********\n\n", contMovimentos, contMovimentos, tempo);
                system("pause");
            }
            else{
                if (head->numElementos>0){
                    if (foiOrdenado==1)
                        transformarVetorEmListaEncadeada(lista, head, vetor );
                    inicioTempo = clock();
                    contMovimentos = 0; //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    retirarNoPosicaoDadaListaEncadeada(lista,head, &contMovimentos);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    imprimeListaEncadeada(lista, head);
                    printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d)  e 1 movimento e tempo = T(%d)********\n\n", contMovimentos, contMovimentos, tempo);
                    //apenas 1 movimento pois apenas um node tem valor trocado
                }
                else
                    printf("\nlista vazia   ");
                system("pause");
            }
        }
        else if (opcaoQueFazer==7){
            int tipoBusca;
            printf("\n (1) Usando busca SEQUENCIAL \n (2) Usando busca BINARIA\n\n ");
            scanf ("%d", &tipoBusca);
            while (tipoBusca>2){
                printf("\n (1) Usando busca SEQUENCIAL \n (2) Usando busca BINARIA\n\n ");
                scanf ("%d", &tipoBusca);
            }
            if (opcaoLista==1 && tipoBusca==1){
                contComparacoes = 0;
                printf("\nDigite RG   ");
                scanf ("%d", &rg);
                inicioTempo = clock();
                procurarRgDadoSequencial_BuscaSequencial (&tam, node, &contComparacoes, rg);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                //imprimeListaSequencial (&tam, node);
                printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d) e tempo = T(%d) ********\n\n", contComparacoes, contComparacoes, tempo); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                system("pause");
            }
            else if (opcaoLista==1 && tipoBusca==2){
                if (foiOrdenado==0){printf("\n\n_____arquivo NAO ordenado para busca binaria_____\n\n");system("pause");}
                else{
                    contComparacoes = 0;
                    printf("\nDigite RG   ");
                    scanf ("%d", &rg);
                    inicioTempo = clock();
                    procurarRgDadoSequencial_BuscaBinaria (&tam, node, &contComparacoes, rg);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d) e tempo = T(%d) ********\n\n", contComparacoes, contComparacoes, tempo); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoLista==2 && tipoBusca==1){
                contComparacoes = 0;
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor);
                printf("\nDigite RG   ");
                scanf ("%d", &rg);
                inicioTempo = clock();
                procurarRgDadoEncadeada_BuscaSequencial (lista, head, &contComparacoes, rg);
                fimTempo = clock();
                tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d) e tempo = T(%d) ********\n\n", contComparacoes, contComparacoes, tempo);
                //imprimeListaEncadeada(lista, head);
                system("pause");
            }
            else if (opcaoLista==2 && tipoBusca==2){
                if (foiOrdenado==0){printf("\n\n_____arquivo NAO ordenado para busca binaria_____\n\n");system("pause");}
                else{
                    contComparacoes = 0;
                    printf("\nDigite RG   ");
                    scanf ("%d", &rg);
                    inicioTempo = clock();
                    procurarRgDadoEncadeada_BuscaBinaria (lista, head, vetor, &contComparacoes, rg);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    printf("\n\n*****  Foram realizado(s) %d comparacao(oes): C(%d) e tempo = T(%d) ********\n\n", contComparacoes, contComparacoes, tempo);
                    //imprimirVetorListaEncadeada(head, vetor);
                    system("pause");
                }
            }
        }
        else if (opcaoQueFazer==8){
            fflush(stdin);
            printf("\nDigite o algoritmo de ordenacao, sendo:\n"
                   "\t(A) Selection Sort\n\t(B) Insertion-Sort\n\t(C) Bubble-Sort\n\t(D) Shell-Sort\n\t(E) Quick-Sort\n\t(F) Merge Sort \n");
            scanf ("%c", &opcaoOrdenar);
            if (opcaoOrdenar > 'Z'){
                opcaoOrdenar = opcaoOrdenar - 32; //converter letra minuscula em maiuscula
            }
            while (opcaoOrdenar > 'F' ){
                printf("\nLETRA INVALIDA\n");
                fflush(stdin);
                printf("\nDigite o algoritmo de ordenacao, sendo:\n"
                   "\t(A) Selection Sort\n\t(B) Insertion-Sort\n\t(C) Bubble-Sort\n\t(D) Shell-Sort\n\t(E) Quick-Sort\n\t(F) Merge Sort \n");
                scanf ("%c", &opcaoOrdenar);
                if (opcaoOrdenar > 'Z'){
                opcaoOrdenar = opcaoOrdenar - 32; //converter letra minuscula em maiuscula
            }

            }
            if (opcaoOrdenar=='A'){
                if (opcaoLista==1){
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    ordenarListaSequencial_Selection (&tam, node, &contMovimentos, &contComparacoes);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Selection (lista, head, &contMovimentos, &contComparacoes, vetor);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoOrdenar=='B' ){
                if (opcaoLista==1){
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    ordenarListaSequencial_Insertion (&tam, node, &contMovimentos, &contComparacoes);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)     T(%d)********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Insertion (lista,head, &contMovimentos, &contComparacoes, vetor);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoOrdenar=='C' || opcaoOrdenar=='c'){
                if (opcaoLista==1){
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    ordenarListaSequencial_Bubble (&tam, node, &contMovimentos, &contComparacoes);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)     T(%d)********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Bubble (lista,head, &contMovimentos, &contComparacoes, vetor);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoOrdenar=='D' || opcaoOrdenar=='d'){
                if (opcaoLista==1){
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    ordenarListaSequencial_Shellsort (&tam, node, &contMovimentos, &contComparacoes);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)     T(%d)********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Shellsort (lista,head, &contMovimentos, &contComparacoes, vetor);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoOrdenar=='E' || opcaoOrdenar=='e'){
                if (opcaoLista==1){
                    inicioTempo = clock();
                    contMovimentos = 0;
                    contComparacoes = 0;
                    ordenarListaSequencial_Quicksort (&tam, node, &contMovimentos, &contComparacoes, 0, tam);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)     T(%d)********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Quicksort (lista,head, &contMovimentos, &contComparacoes, vetor, 0, head->numElementos-1);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
            else if (opcaoOrdenar=='F' || opcaoOrdenar=='f'){
                if (opcaoLista==1){
                    inicioTempo = clock();
                    contMovimentos = 0;
                    contComparacoes = 0;
                    ordenarListaSequencial_Mergesort (&tam, node, &contMovimentos, &contComparacoes, 0, tam);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimeListaSequencial (&tam, node);
                    printf("\n\n*****  C(%d)  ,    M(%d)     T(%d)********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
                else {
                    contMovimentos = 0;
                    contComparacoes = 0;
                    inicioTempo = clock();
                    vetor = (Encadeada**)realloc(vetor, head->numElementos * sizeof(Encadeada*));
                    transformarListaEncadeadaEmVetor(lista,head, vetor);
                    ordenarListaEncadeada_Mergesort (lista, head, &contMovimentos, &contComparacoes, vetor,  0, head->numElementos-1);
                    fimTempo = clock();
                    tempo = (fimTempo - inicioTempo)/CLOCKS_PER_SEC;
                    //imprimirVetorListaEncadeada (head, vetor);
                    printf("\n\n*****  C(%d)  ,    M(%d)    e    T(%d) ********\n\n", contComparacoes, contMovimentos, tempo ); //usei a mesma variavel que contava movimentos para contar comparacoes, para nao precisar criar outra
                    system("pause");
                }
            }
        }
        else if (opcaoQueFazer==9){
            if (opcaoLista==1){
                gravarArquivoSequencia (&tam, node);
                //imprimeListaSequencial (&tam, node);
                system("pause");
            }
            else {
                if (foiOrdenado==1)
                    transformarVetorEmListaEncadeada(lista, head, vetor );
                gravarArquivoEncadeada(lista,head);
                //imprimeListaEncadeada(lista, head);
                system("pause");
            }
        }
        else if (opcaoQueFazer==10){
            printf("\nDigite o tamanho da lista, sendo:\n    (1) 10 nomes\n    (2) 50 nomes\n    (3) 100 nomes\n    (4) 1000 nomes (1K)\n    (5) 10.000 nomes (10K)\n    (6) 1M\n    (7) 100M\n");
            scanf ("%d", &opcaoArquivo);
            while (opcaoArquivo > 7){
                printf("\nNUMERO INVALIDO\n");
                printf("\nDigite o tamanho da lista, sendo:\n    (1) 10 nomes\n    (2) 50 nomes\n    (3) 100 nomes\n    (4) 1000 nomes (1K)\n    (5) 10.000 nomes (10K)\n    (6) 1M\n    (7) 100M\n");
                scanf ("%d", &opcaoArquivo);
            }

            if (opcaoArquivo==1){
                strcpy(nomeArquivo, "NomeRG10.txt");
                tam=10;
            }
            else if (opcaoArquivo==2){
                strcpy(nomeArquivo, "NomeRG50.txt");
                tam=50;
            }
            else if (opcaoArquivo==3){
                strcpy(nomeArquivo, "NomeRG100.txt");
                tam=100;
            }
            else if (opcaoArquivo==4){
                strcpy(nomeArquivo, "NomeRG1K.txt");
                tam=1000;
            }
            else if (opcaoArquivo==5){
                strcpy(nomeArquivo, "NomeRG10K.txt");
                tam=10000;
            }
            else if (opcaoArquivo==6){
                strcpy(nomeArquivo, "NomeRG1M.txt");
                tam = 1000000;
            }
            else if (opcaoArquivo==7){
                strcpy(nomeArquivo, "NomeRG100M.txt");
                tam = 100000000; //esse valor eh atualizado quando o arquivo for lido
            }
            fp = fopen(nomeArquivo,"r+");  // para leitura e escrita, arquivo deve existir
            if(!fp){
              printf( "Erro na abertura do arquivo");
              exit(0);
            }

            if (opcaoLista==1){
                node = (Dados*)realloc (node, (tam+ultimo)*sizeof(Dados));//tam+ultimo pois ultimo eh a ultima posicao ocupada no vetor, caso ja tenha iniciado uma lista
                lerArquivoSalvarDadosSequencial (fp,&tam, node, &ultimo);
                //imprimeListaSequencial (&tam, node);
                system("pause");
            }
            else {
                lerArquivoSalvarDadosEncadeada(fp, head, lista);
                //imprimeListaEncadeada(lista, head);
                system("pause");
            }
        }
        else if (opcaoQueFazer==11){
            fimPrograma = 1;
            return 0;
        }
    }
    free(vetor);
    free(lista);
    free(node);
    fclose(fp);
    return 0;
}
//******************************************************************************************
//      ----------      letra F        ------------
void ordenarListaEncadeada_Mergesort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor,  int posicaoInicio, int posicaoFim){
    int i, j, k, metadeTamanho;
    Encadeada **vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    ordenarListaEncadeada_Quicksort(lista, head, contMovimentos, contComparacoes, vetor, posicaoInicio, metadeTamanho);
    ordenarListaEncadeada_Quicksort(lista, head, contMovimentos, contComparacoes, vetor, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (Encadeada **) malloc((posicaoFim - posicaoInicio + 1) * sizeof(Encadeada*));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
            else {
                *contComparacoes= *contComparacoes + 1;
                if (vetor[i]->node.rg < vetor[j]->node.rg) {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                else {
                    vetorTemp[k]= vetor[j];
                    j++;
                    k++;
                }
            }
        }
    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        *contMovimentos= *contMovimentos + 1;
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra E        ------------
void ordenarListaEncadeada_Quicksort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor, int inicio, int fim){
    int i,j, pivo;
    Encadeada *aux;
    i = inicio;
    j = fim;
    pivo = vetor[(inicio+fim)/2]->node.rg;

    do{
        while (vetor[i]->node.rg < pivo){
            *contComparacoes = *contComparacoes + 1;
            i = i+1;
        }
        *contComparacoes = *contComparacoes + 1;//incrementa ao coparar e nao executar o while
        while (vetor[j]->node.rg > pivo){
            *contComparacoes = *contComparacoes + 1;
            j = j-1;
        }
        *contComparacoes = *contComparacoes + 1;//incrementa ao coparar e nao executar o while
        if (i <= j){
            *contMovimentos = *contMovimentos + 1;
            aux = vetor[i];
            vetor[i]= vetor[j];
            vetor[j]= aux;
            i = i+1;
            j = j-1;
        }
    }while (i <= j);

    if (j > inicio)
        ordenarListaEncadeada_Quicksort(lista, head, contMovimentos, contComparacoes,vetor, inicio, j);
    if (i < fim)
        ordenarListaEncadeada_Quicksort(lista, head, contMovimentos, contComparacoes, vetor, i, fim);

    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra F        ------------
void ordenarListaSequencial_Mergesort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes, int posicaoInicio, int posicaoFim){
    int i, j, k, metadeTamanho;
    Dados *vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    ordenarListaSequencial_Quicksort(tam, node, contMovimentos, contComparacoes, posicaoInicio, metadeTamanho);
    ordenarListaSequencial_Quicksort(tam, node, contMovimentos, contComparacoes, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (Dados *) malloc((posicaoFim - posicaoInicio + 1) * sizeof(Dados));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k] = node[j];
            j++;
            k++;
        }
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k] = node[i];
                i++;
                k++;
            }
            else {
                *contComparacoes= *contComparacoes + 1;
                if (node[i].rg < node[j].rg) {
                    vetorTemp[k] = node[i];
                    i++;
                    k++;
                }
                else {
                    vetorTemp[k]= node[j];
                    j++;
                    k++;
                }
            }
        }
    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        *contMovimentos= *contMovimentos + 1;
        node[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
    foiOrdenado=1;
}

//******************************************************************************************
//      ----------      letra D        ------------
void ordenarListaEncadeada_Shellsort (Encadeada *lista, Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor){
    int i,k, h, posicao;
    Encadeada *aux;

    h = head->numElementos;
    h = (int)h/2;
    while (h>0){
        for (k=0; k < head->numElementos; k++){
            for (i = k+h; i < head->numElementos; i+=h){
                aux = vetor[i];
                posicao = i;
                while (posicao > k && vetor[posicao - h]->node.rg > aux->node.rg){
                    *contComparacoes = *contComparacoes + 1;
                    *contMovimentos = *contMovimentos + 1;
                    vetor[posicao]=vetor[posicao - h];
                    posicao = posicao - h;
                }
                *contComparacoes = *contComparacoes + 1;//comparacao incrementa se comparou e nao
                                                    //executou o while
                if (posicao!=i)
                    vetor[posicao] = aux;
            }
        }
        h = (int)h/2;
    }
    //free(aux);
    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra E        ------------
void ordenarListaSequencial_Quicksort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes, int inicio, int fim){
    int i,j,pivo;
    Dados aux;
    i = inicio;
    j = fim;
    pivo = node[(inicio+fim)/2].rg;

    do{
        while (node[i].rg<pivo){
            i = i+1;
            *contComparacoes = *contComparacoes + 1;
        }
        *contComparacoes = *contComparacoes + 1;//incrementa ao comparar e nao executar o while
        while (node[j].rg > pivo){
            j = j-1;
            *contComparacoes = *contComparacoes + 1;
        }
        *contComparacoes = *contComparacoes + 1;//incrementa ao comparar e nao executar o while
        if (i <= j){
            *contMovimentos = *contMovimentos + 1;
            aux = node[i];
            node[i]= node[j];
            node[j]= aux;
            i = i+1;
            j = j-1;
        }
    }while (i <= j);

    if (j > inicio)
        ordenarListaSequencial_Quicksort(tam,node, contMovimentos, contComparacoes, inicio, j);
    if (i < fim)
        ordenarListaSequencial_Quicksort(tam, node, contMovimentos, contComparacoes, i, fim);

    foiOrdenado=1;
}

//******************************************************************************************
//      ----------      letra C        ------------
void ordenarListaEncadeada_Bubble (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor){
    int i,j, movimentou=1;//movimentou=1 significa que houve troca de elementos
    Encadeada *aux;

    for (i=head->numElementos -1; i>0 && movimentou==1; i--){
        movimentou = 0;
        for (j=0; j<i; j++){
            *contComparacoes = *contComparacoes + 1;
            if (vetor[j]->node.rg > vetor[j+1]->node.rg){
                *contMovimentos = *contMovimentos + 1;
                aux = vetor[j];
                vetor[j]= vetor[j+1];
                vetor[j+1] = aux;
                movimentou = 1;
            }
        }
    }
    //imprimirVetorListaEncadeada (head, vetor);
    //free(aux);
    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra D        ------------
void ordenarListaSequencial_Shellsort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes){
    int i,k, h, posicao;
    Dados rg;

    h = *tam;
    h = h/2;
    while (h>0){
        for (k=0; k < *tam; k++){
            for (i = k+h; i < *tam; i+=h){
                rg = node[i];
                posicao = i;
                while (posicao > k && node[posicao - h].rg > rg.rg){
                    *contComparacoes = *contComparacoes + 1;
                    *contMovimentos = *contMovimentos + 1;
                    node[posicao]=node[posicao - h];
                    posicao = posicao - h;
                }
                *contComparacoes = *contComparacoes + 1;//comparacao incrementa se comparou e nao
                                                    //executou o while
                node[posicao] = rg;//nao conta como movimento pois o espaço ja foi aberto na execução do while
            }
        }
        h = h/2;
    }
    foiOrdenado=1;
}
//******************************************************************************************
void transformarVetorEmListaEncadeada(Encadeada *lista, Header *head, Encadeada **vetor ){
    int i;
    Encadeada *aux;

    head->primeiro = vetor[0];
    head->ultimo = vetor[head->numElementos-1];
    aux = head->primeiro;

    for (i=1; i<head->numElementos; i++){
        aux->proximo = vetor[i];
        aux = aux->proximo;
        aux->anterior = vetor[i-1];
    }

    head->primeiro->anterior = NULL;
    head->ultimo->proximo = NULL;

    //imprimeListaEncadeada(lista, head);
    //free(aux);
}
//******************************************************************************************
void transformarListaEncadeadaEmVetor(Encadeada *lista, Header *head, Encadeada **vetor ){
    int i;
    Encadeada *aux;

    aux = head->primeiro;
    for (i=0; i<head->numElementos; i++){
        vetor[i]= aux;
        aux = aux->proximo;
    }

}

//******************************************************************************************
//      ----------      letra C        ------------
void ordenarListaSequencial_Bubble (int *tam, Dados* node, int *contMovimentos, int *contComparacoes){
    int i,j, movimentou =1;//movimentou = 1 significa que ouve a troca de dois elementos
    Dados aux;

    for (i=*tam -1; i>0 && movimentou ==1; i--){
        movimentou = 0;
        for (j=0; j<i; j++){
            *contComparacoes = *contComparacoes + 1;
            if (node[j].rg > node[j+1].rg){
                *contMovimentos = *contMovimentos + 1;
                aux = node[j];
                node[j]= node[j+1];
                node[j+1] = aux;
                movimentou = 1;
            }
        }
    }
    foiOrdenado=1;
}
//******************************************************************************************
void imprimirVetorListaEncadeada (Header *head, Encadeada **vetor){
    int i;
    for (i=0; i<head->numElementos; i++){
        if (i<10)
            printf("\n[0%d] -> NOME: %s\t RG: %d ", i, vetor[i]->node.nom, vetor[i]->node.rg);
        else
            printf("\n[%d] -> NOME: %s\t RG: %d ", i, vetor[i]->node.nom, vetor[i]->node.rg);
    }
    printf("\n\n");
}
//******************************************************************************************
//      ----------      letra B        ------------
void ordenarListaEncadeada_Insertion (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor){
    int i, posicaoInserir;
    Encadeada *aux;

    for (i=1; i < head->numElementos; i++){
        aux = vetor[i];
        posicaoInserir =i;
        while (posicaoInserir > 0 && vetor[posicaoInserir-1]->node.rg > aux->node.rg){
            *contComparacoes = *contComparacoes +1;//comparacoes dentro do laço
            *contMovimentos = *contMovimentos + 1;
            vetor[posicaoInserir]=vetor[posicaoInserir -1];
            posicaoInserir--;
        }
        *contComparacoes = *contComparacoes +1;//se nao entrou no laco, incrementou 1 mas se entrou no laco incrementa este um mas nao executou o while
        if (posicaoInserir!= i){
            vetor[posicaoInserir]=aux;//nao eh movimento, o espaço ja foi aberto acima, eh copia apenas
        }
    }
    //free(aux);
    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra B        ------------
void ordenarListaSequencial_Insertion (int *tam, Dados* node, int *contMovimentos, int *contComparacoes){
    int i;
    int posicaoInserir; // localizacao para colocar elemento
    Dados aux;

    for (i=1; i < *tam; i++){
        aux = node[i];
        posicaoInserir =i;
        while (posicaoInserir > 0 && node[posicaoInserir-1].rg > aux.rg){
            *contComparacoes = *contComparacoes +1;
            *contMovimentos = *contMovimentos + 1;
            node[posicaoInserir]=node[posicaoInserir -1];
            posicaoInserir--;
        }
        *contComparacoes = *contComparacoes +1;//se nao entrou no laco, incrementou 1 mas se entrou no laco incrementa este um mas nao executou o while
        if (posicaoInserir!= i){
            node[posicaoInserir]=aux;//nao conta como movimento pois o espaço ja foi aberto na execução do while
        }
    }
    foiOrdenado=1;
}

//******************************************************************************************
//      ----------      letra A     ENCADEADA   ------------

void ordenarListaEncadeada_Selection (Encadeada *lista,Header *head, int *contMovimentos, int *contComparacoes, Encadeada **vetor){
    int i,j, posMenor, menor;
    Encadeada *aux;
    for (i=0; i< head->numElementos; i++){
        posMenor = i;
        menor = vetor[i]->node.rg;
        for (j=i+1; j< head->numElementos; j++){
            *contComparacoes = *contComparacoes +1;
            if (vetor[j]->node.rg < menor){
                menor = vetor[j]->node.rg;
                posMenor = j;
            }
        }
        if (posMenor!= i){ //caso o menor ja seja o elemento usado inicialmente para comparar, não precisa movimentar
            aux = vetor[i];
            vetor[i] = vetor[posMenor];
            vetor[posMenor]=aux;
            *contMovimentos = *contMovimentos + 1;
        }
    }
    //imprimirVetorListaEncadeada (head, vetor);

    //free(aux);
    foiOrdenado=1;
}
//******************************************************************************************
//      ----------      letra A     SEQUENCIAL   ------------
void ordenarListaSequencial_Selection (int *tam, Dados* node, int *contMovimentos, int *contComparacoes){
    int i,j, posMenor, menor;
    Dados aux;

    for (i=0; i< *tam; i++){
        posMenor = i;
        menor = node[i].rg;
        for (j=i+1; j< *tam; j++){
            *contComparacoes = *contComparacoes +1;
            if (node[j].rg < menor){
                menor=node[j].rg;
                posMenor = j;
            }
        }
        if (posMenor!= i){ //caso o menor ja seja o elemento usado inicialmente para comparar, não precisa movimentar
            aux = node[i];
            node[i]=node[posMenor];
            node[posMenor]=aux;
            *contMovimentos = *contMovimentos + 1;
        }
    }
    foiOrdenado=1;
}
//******************************************************************************************
void imprimeListaSequencial (int *tam, Dados* node){
    int i;
    for (i=0; i< *tam; i++)
        if (i<10)
            printf("\n[0%d]--> NOME = %s\t-> RG =\t%d", i, node[i].nom, node[i].rg);
        else
            printf("\n[%d]--> NOME = %s\t-> RG =\t%d", i, node[i].nom, node[i].rg);
    printf("\n\n");
}
//******************************************************************************************
void lerArquivoSalvarDadosSequencial(FILE *fp, int *tam, Dados* node, int *ultimo){
    char frase[100]; //frase = nome,rg
    char nome[50], rg[10];
    int k=0, n=0, num,i, RgInt;   //k-> contador p string nome     n-> contador p string rg
    if (*tam>0)     //verifica se a lista ja foi iniciada
        num=*ultimo;//se foi iniciada, comeca a colocar novos valores apos ultimo dado
    else
        num = 0;

    while(fgets(frase,sizeof(frase),fp) != NULL){
		for (i=0; i<strlen(frase) && frase[i]!='\0'; i++){
            if (frase[i]>='A' && frase[i]<='Z'||frase[i]>='a' && frase[i]<='z'){
                nome[k]=frase[i];
                k++;
            }
            else if (frase[i]>='0' && frase[i] <= '9'){
                rg[n]=frase[i];
                n++;
            }
		}
		nome[k]='\0';
		rg[n]='\0';
		strcpy(node[num].nom, nome);
        sscanf(rg, "%d", &RgInt);  //converte RG de string p/ int
		node[num].rg = RgInt;
		k=0;
		n=0;
		num++;
    }
    *tam = num ;
}
//******************************************************************************************
void inserirNoInicioListaSequencia (int *tam, Dados* node, int *ultimo, int *contMovimentos){
    char nome[50];
    int rg,i;

    printf("\nDigite o nome   ");
    scanf("%s", &nome);
    nome[strlen(nome)]='\0';
    printf("\nDigite RG   ");
    scanf ("%d", &rg);

    for (i=*tam; i>0; i--){
        node[i]=node[i-1];
        (*contMovimentos)++;
    }
    strcpy(node[0].nom, nome);
    node[0].rg = rg;
    *tam=(*tam)+1;
    *ultimo = *tam;
}
//******************************************************************************************
void retirarNoInicioListaSequencia (int *tam, Dados* node, int *contMovimentos){
    int opcao,i;
    if (*tam>0){
        printf("\nnome = %s  RG = %d\n\nTem certeza que deseja excluir primeiro item da lista?  (1) sim     (2) nao       ", node[0].nom, node[0].rg);
        scanf("%d", &opcao);
        while (opcao <1 || opcao > 2){
            printf("\nnome = %s  RG = %d\n\nTem certeza que deseja excluir primeiro item da lista?  (1) sim     (2) nao       ", node[0].nom, node[0].rg);
            scanf("%d", &opcao);
        }
        if (opcao==1){
            for (i=0; i<*tam-1; i++){   // menos 1 pq se tam=10, vetor vai ate posicao 9 e paro no 8 para pegar 9
                node[i]=node[i+1];
                (*contMovimentos)++;
            }
            node = (Dados*)realloc (node, (*tam-1)*sizeof(Dados));
            if(node == NULL)
                printf("Sem espaço suficiente\n");
            *tam=(*tam)-1;
        }
    }
    else {
        printf("\nlista vazia    ");
        return;
    }
}
//******************************************************************************************
void inserirFinalListaSequencia (int *tam, Dados* node, int *ultimo){
    char nome[50];
    int rg;

    printf("\nDigite o nome   ");
    scanf("%s", &nome);
    nome[strlen(nome)]='\0';
    printf("\nDigite RG   ");
    scanf ("%d", &rg);

    strcpy(node[*tam].nom, nome);
    node[*tam].rg=rg;
    *tam=(*tam)+1;
    *ultimo = *tam;
}
//******************************************************************************************
void retirarFinalListaSequencia (int *tam, Dados* node){
    int opcao,i;
    if (*tam > 0){
        printf("\nnome = %s  RG = %d\n\nTem certeza que deseja excluir ultimo item da lista?  (1) sim     (2) nao       ", node[*tam-1].nom, node[*tam-1].rg);
        scanf("%d", &opcao);
        while (opcao <1 || opcao > 2){
            printf("\nnome = %s  RG = %d\n\nTem certeza que deseja excluir ultimo item da lista?  (1) sim     (2) nao       ", node[*tam-1].nom, node[*tam-1].rg);
            scanf("%d", &opcao);
        }
        if (opcao==1){
            node = (Dados*)realloc (node, (*tam-1)*sizeof(Dados));
            if(node == NULL)
                printf("\nSem espaço suficiente   ");
            *tam=(*tam)-1;
        }
    }
    else{
        printf("\nlista vazia.     ");
        return;
    }
}
//******************************************************************************************
void inserirNoPosicaoDadaListaSequencial (int *tam, Dados* node, int *ultimo, int *contMovimentos){
    char nome[50];
    int rg, posicao,i;

    printf("\nDigite o nome   ");
    scanf("%s", &nome);
    nome[strlen(nome)]='\0';
    printf("\nDigite RG   ");
    scanf ("%d", &rg);
    if (*tam==0){
        printf("\nA lista nao foi criada, este sera o primeiro elemeto    \n");
        posicao = 0;
        strcpy(node[posicao].nom, nome);
        node[posicao].rg = rg;
    }
    else {
        printf("\nDigite a posicao que deseja inserir (de 0 ate %d)   ", *tam);
        scanf("%d", &posicao);
        //for (i=*tam; i>(posicao-1); i--){ //posicao 2 eh na vdd posicao 1 no vetor
        for (i=*tam; i>(posicao); i--){ //posicao 2 eh na vdd posicao 1 no vetor
            node[i]=node[i-1];
            (*contMovimentos)++;
        }
        //strcpy(node[posicao-1].nom, nome);
        strcpy(node[posicao].nom, nome);
        node[posicao].rg = rg;
        //node[posicao-1].rg = rg;
    }

    *tam=(*tam)+1;
    *ultimo = *tam;
}
//******************************************************************************************
void retirarNoPosicaoDadaListaSequencial (int *tam, Dados* node, int *contMovimentos){
    int posicao,i, opcao;
    if (*tam>0){
        printf("\nDigite a posicao que deseja excluir (de 0 ate %d)   ", *tam-1);   //posicao 2 eh na vdd posicao 1 no vetor
        scanf("%d", &posicao);

        printf("\nNOME = %s  RG = %d\n\nTem certeza que deseja excluir o item %d da lista?  (1) sim     (2) nao       ", node[posicao].nom, node[posicao].rg, posicao);
        scanf("%d", &opcao);
        while (opcao<1 || opcao >2){
            printf("\nNOME = %s  RG = %d\n\nTem certeza que deseja excluir o item %d da lista?  (1) sim     (2) nao       ", node[posicao].nom, node[posicao].rg, posicao);
            scanf("%d", &opcao);
        }
        if (opcao==1){
            //for (i=posicao-1; i< *tam-2; i++){ //posicao 2 eh na vdd posicao 1 no vetor
            for (i=posicao; i< *tam-1; i++){
                node[i]=node[i+1];
                (*contMovimentos)++;
        }
        node = (Dados*)realloc (node, (*tam-1)*sizeof(Dados));
        if(node == NULL)
            printf("Sem espaço suficiente\n");
        *tam=(*tam)-1;
        }
    }
    else{
        printf("\n lista vazia    ");
        return;
    }
}
//******************************************************************************************
void procurarRgDadoEncadeada_BuscaSequencial (Encadeada *lista,Header *head, int *contComparacoes, int rg){
    int achou = 0, i; //achou = 1 significa que encontrou RG solicitado
    //int rg;
    Encadeada *aux;
    aux = head->primeiro;

    //printf("\n Digite o numero do RG.     ");
    //scanf("%d", &rg);

    for (i = 0; i < head->numElementos && achou == 0; i++) {
        *contComparacoes = *contComparacoes + 1;
        if (aux->node.rg == rg) {
            printf("\nLocalizado. NOME: %s    posicao: %d      ", aux->node.nom, i);
            achou = 1;
            break;
        }
        if (aux->proximo == NULL) {
            break;
        }
        aux = aux->proximo;
    }

    if (achou == 0) {
        printf("\nRG nao encontrado.     ");
    }
}
//******************************************************************************************
void procurarRgDadoEncadeada_BuscaBinaria (Encadeada *lista,Header *head, Encadeada **vetor, int *contComparacoes, int rg){
    //int rg;
    int achou=0, inf, sup, meio ; //achou = 1 qdo encontrar RG
    if (head->numElementos>0){
        //printf("\n\nDigite o RG que deseja buscar    ");
        //scanf("%d", &rg);

        inf = 0;
        sup = head->numElementos -1;
        while (inf <= sup && achou ==0){
            meio = (inf + sup)/2;
            *contComparacoes = *contComparacoes + 1;
            if (rg == vetor[meio]->node.rg){
                printf("\n\n RG encontrado na posicao %d  -> NOME = %s\n\n", meio, vetor[meio]->node.nom);
                achou =1;
            }
            else if (rg < vetor[meio]->node.rg)
                sup = meio -1;
            else
                inf = meio + 1;
        }


        if (achou==0)
            printf("--------RG nao encontrado       \n");
    }
    else {
        printf("\n lista vazia     \n\n");
        return;
    }
}
//******************************************************************************************
void procurarRgDadoSequencial_BuscaSequencial (int *tam, Dados* node, int *contComparacoes, int rg){
    int i, achou=0; //achou = 1 qdo encontrar RG
    //int rg;
    if (*tam>0){
        //printf("\n\nDigite o RG que deseja buscar    ");
        //scanf("%d", &rg);

        for (i=0; i<*tam; i++){
            (*contComparacoes)++;
            if (rg == node[i].rg){
                printf("\nO nome eh: %s na posicao %d   \n\n", node[i].nom, i);
                achou=1;
                break;
            }
        }
        if (achou==0){
            printf("\nNAO esta na lista\n\n");
            system("pause");
        }
    }
    else {
        printf("\n lista vazia     \n\n");
        return;
    }
}
//******************************************************************************************
void procurarRgDadoSequencial_BuscaBinaria (int *tam, Dados* node, int *contComparacoes, int rg){
    //int rg;
    int i, achou=0, inf, sup, meio; //achou = 1 qdo encontrar RG
    if (*tam>0){
        //printf("\n\nDigite o RG que deseja buscar    ");
        //scanf("%d", &rg);

        inf = 0;
        sup = *tam -1;
        while (inf <= sup && achou ==0){
            meio = (inf + sup)/2;
            *contComparacoes = *contComparacoes + 1;
            if (rg == node[meio].rg){
                printf("\n\n RG encontrado na posicao %d  -> NOME = %s\n\n", meio, node[meio].nom);
                achou =1;
            }
            else if (rg < node[meio].rg)
                sup = meio -1;
            else
                inf = meio + 1;
        }

        if (achou==0)
            printf("\n\n-----------RG nao encontrado-------------------\n\n");
    }
    else {
        printf("\n lista vazia     \n\n");
        return;
    }
}
//******************************************************************************************

void gravarArquivoSequencia(int *tam, Dados* node){
    int i;
    char arquivoSalvar[20];

    strcpy(arquivoSalvar, "arquivoSalvoSequencial.txt");
    FILE *novoArquivo;
    novoArquivo = fopen(arquivoSalvar,"w");//Abre ou cria o arquivo para escrita e leitura, apagando o conteúdo pré-existente

    if(!novoArquivo)
    {
      printf( "Erro na abertura do arquivo");
      exit(0);
    }
    for(i=0; i<*tam; i++)
        fprintf(novoArquivo, "%s,%d", node[i].nom, node[i].rg);
    fclose(novoArquivo);
}
//******************************************************************************************
void limparLista(Header *head){//funcao que libera node solicitado
    if (head->numElementos > 0){
        Encadeada *aux;

        aux = head->primeiro;
        while (aux->proximo !=NULL){
            aux = aux->proximo;
            free(aux->anterior);
        }
        free(aux);
        head->primeiro=NULL;
        head->ultimo = NULL;
        head->numElementos = 0;
    }
}
//******************************************************************************************
void imprimeListaEncadeada (Encadeada *lista, Header *head){
    if (head->numElementos > 0) {
        int i = 0;
        Encadeada *aux;
        aux = head->primeiro;
        for (i = 0; i < head->numElementos; i++) {
            printf("\n--> (%d) \tNOME: %s\tRG: %d    ", i, aux->node.nom, aux->node.rg);
            aux = aux->proximo;
        }
        printf("\n\n");
    } else {
        printf("\nLista vazia.\n");
    }
}
//******************************************************************************************
void lerArquivoSalvarDadosEncadeada(FILE *fp, Header *head, Encadeada* lista){
    char frase[100]; //frase = nome,rg
    char nome[50], rg[10];
    int k=0, n=0, num=0,i, RgInt;   //k-> contador p string nome     n-> contador p string rg
    while(fgets(frase,sizeof(frase),fp) != NULL){
		for (i=0; i<strlen(frase) && frase[i]!='\0'; i++){
            if (frase[i]>='A' && frase[i]<='Z'||frase[i]>='a' && frase[i]<='z'){
                nome[k]=frase[i];
                k++;
            }
            else if (frase[i]>='0' && frase[i] <= '9'){
                rg[n]=frase[i];
                n++;
            }
		}
		nome[k]='\0';
		rg[n]='\0';
        sscanf(rg, "%d", &RgInt);  //converte RG de string p/ int

        insereElementoFinalListaEncadeada(lista,head, nome, RgInt);
		k=0;
		n=0;
		num++;
    }
}
//******************************************************************************************
void insereElementoInicioListaEncadeada(Encadeada *lista,Header *head, char nome[50], int rg, int *contMovimentos){
    Encadeada *novo;
    novo = (Encadeada*)malloc (sizeof(Encadeada));
    strcpy(novo->node.nom, nome);
    novo->node.rg = rg;
    novo->anterior = NULL;

    if (head->primeiro == NULL) {
        novo->proximo = NULL;
        head->ultimo = novo;
        head->primeiro = novo;
    } else {
        novo->proximo = head->primeiro;
        novo->proximo->anterior = novo;
        head->primeiro = novo;
    }
    *contMovimentos = 1;// recebe pois apenas um node tem seu valor alterado
    head->numElementos++;
}
//******************************************************************************************
void insereElementoFinalListaEncadeada(Encadeada *lista,Header *head, char nome[50], int rg){
        Encadeada *novo;
        novo = (Encadeada*)malloc (sizeof(Encadeada));

        strcpy(novo->node.nom, nome);
        novo->node.rg = rg;
        novo->proximo = NULL;

        if (head->primeiro==NULL){
            head->primeiro = novo;
            head->ultimo = novo;
            novo->anterior = NULL;
        }
        else{
            head->ultimo->proximo = novo;
            novo->anterior = head->ultimo;
            head->ultimo = novo;
        }
        head->numElementos = head->numElementos + 1;
}
//******************************************************************************************
void inserirNoPosicaoDadaListaEncadeada (Encadeada *lista,Header *head, char nome[50], int rg, int *contMovimentos){
    int posicao;
    printf("\nDigite a posicao    ");
    scanf("%d", &posicao);

    if (posicao == 0) {
        insereElementoInicioListaEncadeada(lista,head, nome, rg, *contMovimentos );
    } else if (posicao == head->numElementos) {
        insereElementoFinalListaEncadeada(lista, head, nome, rg);
        *contMovimentos = 1;
    } else {
        int i;
        Encadeada *aux, *novo;
        novo = (Encadeada *) malloc(sizeof(Encadeada));
        aux = head->primeiro;

        for (i = 0; i < posicao; i++) {
            aux = aux->proximo;
            *contMovimentos = *contMovimentos + 1;
        }
        strcpy (novo->node.nom, nome);
        novo->node.rg = rg;

        novo->proximo = aux;
        novo->anterior = aux->anterior;
        novo->anterior->proximo = novo;
        aux->anterior = novo;
        head->numElementos++;
    }
}
//******************************************************************************************
void retirarNoInicioListaEncadeada(Encadeada *lista,Header *head){
    int opcao;

    if (head->numElementos > 1){
        printf("\Tem certeza que deseja retirar o primeiro elemento: (1) sim (2) nao -> NOME: %s    RG: %d     ", head->primeiro->node.nom, head->primeiro->node.rg );
        scanf ("%d", &opcao);
        while (opcao<1 || opcao > 2){
            printf("\Tem certeza que deseja retirar o primeiro elemento: (1) sim (2) nao -> NOME: %s    RG: %d     ", head->primeiro->node.nom, head->primeiro->node.rg );
            scanf ("%d", &opcao);
        }
        if (opcao ==1){
            Encadeada *aux;
            aux = head->primeiro;
            head->primeiro = aux->proximo;
            head->primeiro->anterior = NULL;
            head->numElementos--;
            free(aux);
        }
    }
    else if (head->numElementos == 1){
        printf("\Tem certeza que deseja retirar o primeiro e unico elemento (1) sim (2) nao -> NOME: %s    RG: %d     ", head->primeiro->node.nom, head->primeiro->node.rg );
        scanf("%d", &opcao);
        if (opcao == 1)
            limparLista(head);
    }
}
//******************************************************************************************
void retirarFinalListaEncadeada( Encadeada *lista,Header *head){
    if (head->numElementos > 1) {
        printf("\nRemovendo -> NOME: %s   RG: %d         ", head->ultimo->node.nom, head->ultimo->node.rg);
        Encadeada *aux;
        aux = head->ultimo;
        head->ultimo = aux->anterior;
        head->ultimo->proximo = NULL;
        head->numElementos--;
        free(aux);
    }
    else if (head->numElementos == 1) {
        printf("\nRemovendo -> NOME: %s   RG: %d         ", head->ultimo->node.nom, head->ultimo->node.rg);
        limparLista(head);
    }
}
//******************************************************************************************
void retirarNoPosicaoDadaListaEncadeada( Encadeada *lista,Header *head, int *contMovimento){
    int posicao;
    printf("\nDigite a posicao (0 ate %d)   ", head->numElementos-1);
    scanf("%d", &posicao);
    while (posicao>head->numElementos-1){
        printf("\nNUMERO INVALIDO");
        printf("\nDigite a posicao (0 ate %d)   ", head->numElementos-1);
        scanf("%d", &posicao);
    }

    if (head->numElementos==0){
        printf("\nlista vazia");
    }
    else if (head->numElementos == 1){
        limparLista(head);
    }
    else if (posicao == 0){
        retirarNoInicioListaEncadeada(lista, head);
        *contMovimento = 1;
    }
    else if (posicao == head->numElementos - 1){
        retirarFinalListaEncadeada(lista, head);
        *contMovimento = 1;
    }
    else {
        int i;
        Encadeada *aux;
        aux = head->primeiro;

        for (i=0; i<posicao; i++){
            aux = aux->proximo;
            *contMovimento = *contMovimento + 1;
        }
        aux->proximo->anterior = aux->anterior;
        aux->anterior->proximo = aux->proximo;
        head->numElementos--;

        printf("\nRemovendo -> NOME: %s   RG: %d      ", aux->node.nom, aux->node.rg);
        free(aux);
    }
}

//******************************************************************************************
void gravarArquivoEncadeada(Encadeada *lista,Header *head){
    int i;
    char arquivoSalvar[35];
    Encadeada *aux;
    aux = head->primeiro;
    strcpy(arquivoSalvar, "arquivoSalvoEncadeada.txt");
    FILE *novoArquivo;
    novoArquivo = fopen(arquivoSalvar,"w");//Abre ou cria o arquivo para escrita e leitura, apagando o conteúdo pré-existente

    if(!novoArquivo){
          printf( "Erro na abertura do arquivo");
          exit(0);
        }
    if (head->numElementos == 0){
        printf("\nlista vazia.   ");
    }
    else {
        for (i = 0; i < head->numElementos; i++) {
            fprintf(novoArquivo, "%s,%d", aux->node.nom, aux->node.rg);
            aux = aux->proximo;
            if (aux==NULL)
                break;
        }
    }
    fclose(novoArquivo);
}

