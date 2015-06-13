#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"

void Insere_Indice(Indice *ind,char *st,int bos)
{
    //busca binaria
    //insere
}

Indice Cria_Indice_Autor(int size) // recebe tamanho do arquivo , para caso ele já seja > 10
{
    FILE *arq;
    Indice ind;
    ind.elem = malloc(size*sizeof(NoIndice));
    ind.tam = 0;

    arq = fopen("BD_livros2.bin", "rb");
    char st[100];
    int tam;
    int bos=0;
    int caminha;

    fseek (arq ,sizeof(int),SEEK_SET); // pula o cabeçalho
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

        Insere_Indice(&ind,st,bos);
        printf("%s",ind.elem[ind.tam-1].chave);

        bos+=tam;
        caminha; //Tam do Reg - Tam TITLE - Tam AUTHOR - 1 Delimitador
        fseek(arq, caminha ,SEEK_CUR);

        fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
            break;
    }
    fclose(arq);
    return ind;
}



Indice Cria_Indice_Editora(int size) // recebe tamanho do arquivo , para caso ele já seja > 10
{
    FILE *arq;
    Indice ind;
    ind.elem = malloc(size*sizeof(NoIndice));
    ind.tam = 0;

    arq = fopen("BD_livros2.bin", "rb");
    char st[100];
    int tam;
    int bos=0;
    int caminha;

    fseek (arq ,sizeof(int),SEEK_SET); // pula o cabeçalho
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

        Insere_Indice(&ind,st,bos);
        printf("%s",ind.elem[ind.tam-1].chave);

        bos+=tam;
        caminha; //Tam do Reg - Tam TITLE - Tam AUTHOR - Tam editora 1 Delimitador
        fseek(arq, caminha ,SEEK_CUR);

        fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
            break;
    }

    fclose(arq);
    return ind;
}
