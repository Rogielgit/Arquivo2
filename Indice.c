#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Indice.h"

int ComparaNomeNasListas( NoLista * A, char * B ){
    // Validade dos Argumentos
    if (A == NULL || B == NULL)
        return ArgumentoInvalido;

    BlocoDoSecundario * BlocoSecundario;
    BlocoSecundario = A->Info;
    // Retorna verdadeiro se corresponde
    return !strcmp(BlocoSecundario->Info, B);
}

int ComparaByteOffSetNasListas(NoLista * ListaInvertida, int ByteOffSet){
    BlocoDaInvertida * BlocoInvertida;
    BlocoInvertida = ListaInvertida->Info;

    return (BlocoInvertida->ByteOffSet == ByteOffSet);
}


int ComparaByteOffSetNasListasParaOrdenacao(NoLista * ListaInvertida, int ByteOffSet){
    BlocoDaInvertida * BlocoInvertida;
    BlocoInvertida = ListaInvertida->Info;

    return (BlocoInvertida->ByteOffSet > ByteOffSet);
}

int InserirIndiceSecundario(List * ListaDeSecundarios, char * Info, int ByteOffSet){
    BlocoDoSecundario * BlocoSecundario;

    BlocoDaInvertida  * BlocoInvertida;
    BlocoInvertida = (BlocoDaInvertida *) malloc(sizeof(BlocoDaInvertida));
    BlocoInvertida->ByteOffSet = ByteOffSet;

    NoLista * No = BuscarLista(ListaDeSecundarios, (FuncaoComparacao) ComparaNomeNasListas, Info);
    if (No != False){
        BlocoSecundario = No->Info;
        InserirLista(BlocoSecundario->ListaInvertida, BlocoInvertida);
        return 2;
    }

    BlocoSecundario = (BlocoDoSecundario *) malloc(sizeof(BlocoDoSecundario));
    BlocoSecundario->Info = (char *) malloc(sizeof(char) * strlen(Info));
    strcpy(BlocoSecundario->Info, Info);
    List * Lista;
    Lista = CriaLista();
    BlocoSecundario->ListaInvertida = Lista;

    InserirLista(BlocoSecundario->ListaInvertida, BlocoInvertida);
    InserirLista(ListaDeSecundarios, BlocoSecundario);
    return 1;
}

int RemoverIndiceSecundario(List * ListaDeSecundarios, char * Nome, int ByteOffSet){
    NoLista * NoDaListaDeSecundarios = BuscarLista(ListaDeSecundarios, (FuncaoComparacao) ComparaNomeNasListas, Nome);
    if (NoDaListaDeSecundarios == NULL)
        return 0;
    BlocoDoSecundario * BlocoSecundario;
    BlocoSecundario = NoDaListaDeSecundarios->Info;
    int Result = RemoverLista(BlocoSecundario->ListaInvertida, (FuncaoComparacao) ComparaByteOffSetNasListas, ByteOffSet);
    if (ListaVazia(BlocoSecundario->ListaInvertida))
        RemoverLista(ListaDeSecundarios, (FuncaoComparacao) ComparaNomeNasListas, Nome);
    return Result;
}

List * CriaIndiceAutor(){
    FILE * Arquivo;
    List * ListaDeSecundarios;
    ListaDeSecundarios = CriaLista();

    Arquivo = fopen("BD_livros2.bin", "rb");
    char NomeAutor[100];
    char NomeTitulo[100];
    int Tamanho;
    int ByteOffSet=0;
    int caminha;

    fseek (Arquivo, sizeof(int), SEEK_SET); // pula o cabe?alho
    fread(&Tamanho, sizeof(int), 1, Arquivo);

    while(1)
    {
        if(feof(Arquivo))
            break;
        caminha = Tamanho;
        fscanf(Arquivo,"%[^|]s", NomeTitulo); // ler o titulo
        fseek (Arquivo,sizeof(char), SEEK_CUR);
        caminha -= strlen(NomeAutor);

        fscanf(Arquivo,"%[^|]s", NomeAutor); // ler Autor

        caminha -= strlen(NomeAutor);
        caminha -= 1;

        if (NomeTitulo[0] != '*')
            InserirIndiceSecundario(ListaDeSecundarios, NomeAutor, ByteOffSet);

        ByteOffSet += Tamanho;
        fseek(Arquivo, caminha, SEEK_CUR);

        fread(&Tamanho, sizeof(int), 1, Arquivo);
        if (feof(Arquivo))
            break;
    }
    fclose(Arquivo);
    return ListaDeSecundarios;
}



List * CriaIndiceEditora() // recebe tamanho do Arquivouivo , para caso ele j? seja > 10
{
    FILE *Arquivo;
    List * ListaDeSecundarios;
    ListaDeSecundarios = CriaLista();

    Arquivo = fopen("BD_livros2.bin", "rb");
    char NomeEditora[100];
    char NomeTitulo[100];
    int Tamanho;
    int ByteOffSet = 0;
    int caminha;

    fseek(Arquivo , sizeof(int),   SEEK_SET); // pula o cabe?alho
    fread(&Tamanho, sizeof(int), 1, Arquivo);

    while(1)
    {
        if(feof(Arquivo))
            break;
        caminha = Tamanho;
        fscanf(Arquivo,"%[^|]s", NomeTitulo); // ler o titulo
        fseek(Arquivo,sizeof(char),SEEK_CUR);
        caminha -= strlen(NomeEditora) + 1;

        fscanf(Arquivo,"%[^|]s",NomeEditora); // ler Autor
        fseek(Arquivo,sizeof(char),SEEK_CUR);
        caminha -= strlen(NomeEditora);
        caminha -= 1; // |

        fscanf(Arquivo,"%[^|]s",NomeEditora); // ler editora
        fseek(Arquivo,sizeof(char),SEEK_CUR);
        caminha -= strlen(NomeEditora);
        caminha -= 1; // |

        if (NomeTitulo[0] != '*')
            InserirIndiceSecundario(ListaDeSecundarios, NomeEditora, ByteOffSet);

        ByteOffSet += Tamanho;
        fseek(Arquivo, caminha ,SEEK_CUR);

        fread(&Tamanho, sizeof(int), 1, Arquivo);
        if (feof(Arquivo))
            break;
    }
    fclose(Arquivo);
    return ListaDeSecundarios;
}

List * Merging(List * ListaInvertida1, List * ListaInvertida2){
    List * ListaResultado;
    ListaResultado = CriaLista();
    Ordena(&(ListaInvertida1->Primeiro), (FuncaoComparacao) ComparaByteOffSetNasListasParaOrdenacao);
    Ordena(&(ListaInvertida2->Primeiro), (FuncaoComparacao) ComparaByteOffSetNasListasParaOrdenacao);

    NoLista * No1, * No2;
    No1 = ListaInvertida1->Primeiro;
    No2 = ListaInvertida2->Primeiro;

    while(No1 != NULL && No2 != NULL){

        BlocoDaInvertida * BlocoInvertida1;
        BlocoDaInvertida * BlocoInvertida2;
        BlocoInvertida1  = No1->Info;
        BlocoInvertida2  = No2->Info;

        if (BlocoInvertida1->ByteOffSet > BlocoInvertida2->ByteOffSet){
            InserirLista(ListaResultado, BlocoInvertida2);
            No2 = No2->Proximo;
        }
        else if (BlocoInvertida1->ByteOffSet < BlocoInvertida2->ByteOffSet){
            InserirLista(ListaResultado, BlocoInvertida1);
            No1 = No1->Proximo;
        }
        else{
            InserirLista(ListaResultado, BlocoInvertida1);
            No1 = No1->Proximo;
            No2 = No2->Proximo;
        }
    }
    if (No1 == NULL)
        No1 = No2;

    while (No1 != NULL){
        BlocoDaInvertida * BlocoInvertida;
        BlocoInvertida = No1->Info;
        InserirLista(ListaResultado, BlocoInvertida);
        No1 = No1->Proximo;
    }
    return ListaResultado;
}

List * Matching(List * ListaInvertida1, List * ListaInvertida2){
    List * ListaResultado;
    ListaResultado = CriaLista();
    Ordena(&(ListaInvertida1->Primeiro), (FuncaoComparacao) ComparaByteOffSetNasListasParaOrdenacao);
    Ordena(&(ListaInvertida2->Primeiro), (FuncaoComparacao) ComparaByteOffSetNasListasParaOrdenacao);

    NoLista * No1, * No2;
    No1 = ListaInvertida1->Primeiro;
    No2 = ListaInvertida2->Primeiro;

    while(No1 != NULL && No2 != NULL){

        BlocoDaInvertida * BlocoInvertida1;
        BlocoDaInvertida * BlocoInvertida2;
        BlocoInvertida1  = No1->Info;
        BlocoInvertida2  = No2->Info;

        if (BlocoInvertida1->ByteOffSet > BlocoInvertida2->ByteOffSet)
            No2 = No2->Proximo;
        else if (BlocoInvertida1->ByteOffSet < BlocoInvertida2->ByteOffSet)
            No1 = No1->Proximo;
        else{
            InserirLista(ListaResultado, BlocoInvertida1);
            No1 = No1->Proximo;
            No2 = No2->Proximo;
        }
    }
    return ListaResultado;
}
