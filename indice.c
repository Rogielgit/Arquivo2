#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"


void Insere_Indice(List *ini,char *st,int bos)
{
    //busca binaria
    //insere
}

void Cria_Indice_Autor(List *ini, int size) // recebe tamanho do arquivo , para caso ele ja seja > 10
{
    FILE *arq;
    //Indice ind;
   // ind.elem = malloc(size*sizeof(NoIndice));
    ///ind.tam = 0;

    arq = fopen("BD_livros2.bin", "rb");
    char st[100];
    int tam;
    int bos=4;//
    int caminha;

    fseek (arq ,sizeof(int),SEEK_SET); // pula o cabe�alho
    fread(&tam,sizeof(int),1,arq);

    while(1)
    {
        if(feof(arq))
            break;
        caminha = tam;
        printf("%d -",tam);
        fscanf(arq,"%[^|]s",st); // ler o titulo
        fseek(arq,sizeof(char),SEEK_CUR);
        caminha -= strlen(st);

        fscanf(arq,"%[^|]s",st); // ler Autor
        printf("%s\n",st);
        caminha -= strlen(st);
        caminha -= 1;

        Insere_Indice(ini,st,bos);
       
        bos+=tam;
        caminha; //Tam do Reg - Tam TITLE - Tam AUTHOR - 1 Delimitador
        fseek(arq, caminha ,SEEK_CUR);
        fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
            break;
    }
    fclose(arq);
    //return ind;
}



void Cria_Indice_Editora(List *ini,int size) // recebe tamanho do arquivo , para caso ele j� seja > 10
{
    FILE *arq;
    Indice ind;
    ind.elem = malloc(size*sizeof(NoIndice));
    ind.tam = 0;

    arq = fopen("BD_livros2.bin", "rb");
    char st[100];
    int tam;
    int bos=4; // soma o cabelhaco
    int caminha;

    fseek (arq ,sizeof(int),SEEK_SET); // pula o cabe�alho
    fread(&tam,sizeof(int),1,arq);

    while(1)
    {
        if(feof(arq))
            break;
        caminha = tam;
        printf("%d -",tam);
        fscanf(arq,"%[^|]s",st); // ler o titulo
        fseek(arq,sizeof(char),SEEK_CUR);
        caminha -= strlen(st);

        fscanf(arq,"%[^|]s",st); // ler Autor
        printf("%s\n",st);
        caminha -= strlen(st);
        caminha -= 1; // |

        fscanf(arq,"%[^|]s",st); // ler editora
        printf("%s\n",st);
        caminha -= strlen(st);
        caminha -= 1; // |

        Insere_Indice(ini,st,bos);
        

        bos+=tam;
        caminha; //Tam do Reg - Tam TITLE - Tam AUTHOR - Tam editora 1 Delimitador
        fseek(arq, caminha ,SEEK_CUR);

        fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
            break;
    }

    fclose(arq);
    //return ind;
}
