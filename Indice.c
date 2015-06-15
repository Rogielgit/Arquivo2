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

int InserirIndiceSecundario(List *ListaDeSecundarios, char * Info, int ByteOffSet){
    BlocoDoSecundario * BlocoSecundario;

    BlocoDaInvertida  * BlocoInvertida;
    BlocoInvertida = (BlocoDaInvertida*) malloc(sizeof(BlocoDaInvertida));
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

List * CriaIndiceAutor() // recebe tamanho do Arquivouivo , para caso ele j? seja > 10
{
    FILE * Arquivo;
    List * ListaDeSecundarios;
    ListaDeSecundarios = CriaLista();

    Arquivo = fopen("BD_livros2.bin", "rb");
    char NomeAux[100];
    int Tamanho;
    int ByteOffSet=0;
    int caminha;

    fseek (Arquivo ,sizeof(int),SEEK_SET); // pula o cabe?alho
    fread(&Tamanho,sizeof(int),1,Arquivo);

    while(1)
    {
        if(feof(Arquivo))
            break;
        caminha = Tamanho;
        printf("%d -",Tamanho);
        fscanf(Arquivo,"%[^|]s",NomeAux); // ler o titulo
        fseek(Arquivo,sizeof(char),SEEK_CUR);
        caminha -= strlen(NomeAux);

        fscanf(Arquivo,"%[^|]s",NomeAux); // ler Autor
        if (NomeAux[0] != '*')
        {
            
            printf("%s\n",NomeAux);
            caminha -= strlen(NomeAux);
            caminha -= 1;

            InserirIndiceSecundario(ListaDeSecundarios, NomeAux, ByteOffSet);

            ByteOffSet+=Tamanho;
            fseek(Arquivo, caminha ,SEEK_CUR);

            fread(&Tamanho, sizeof(int), 1, Arquivo);
            if (feof(Arquivo))
            break;
        }
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
    char NomeAux[100];
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
        printf("%d -",Tamanho);
        fscanf(Arquivo,"%[^|]s",NomeAux); // ler o titulo
        if (NomeAux[0] == '*')
        {
            fseek(Arquivo,sizeof(char),SEEK_CUR);
            caminha -= strlen(NomeAux);

            fscanf(Arquivo,"%[^|]s",NomeAux); // ler Autor
            printf("%s\n",NomeAux);
            caminha -= strlen(NomeAux);
            caminha -= 1; // |

            fscanf(Arquivo,"%[^|]s",NomeAux); // ler editora
            printf("%s\n",NomeAux);
            caminha -= strlen(NomeAux);
            caminha -= 1; // |

            InserirIndiceSecundario(ListaDeSecundarios, NomeAux,ByteOffSet);

            ByteOffSet += Tamanho;
            fseek(Arquivo, caminha ,SEEK_CUR);

            fread(&Tamanho, sizeof(int), 1, Arquivo);
            if (feof(Arquivo))
                break;
        }
    }
    fclose(Arquivo);
    return ListaDeSecundarios;
}

