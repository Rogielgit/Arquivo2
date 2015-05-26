#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

char* Le_String(){ //coloca '\0' no fim da string lida
    char *str,c;
    int tamanho = 0, i = 1;
    str = (char*)malloc(sizeof(char));

    while(c!='\n'){
        c = getc(stdin);     //lendo caractere do teclado
        if(c=='\n')
            break;
        str = (char*)realloc(str,i*sizeof(char)); //realocando espaço
        str[tamanho] = c;  //grava caractere lido
        i++;
        tamanho++;
    }
    str[tamanho]='\0'; //coloca '\0'no fim da string
    return str;
}

void Ler_dados_livro(Livro *Dados){
    //fflush_in();
    printf ("TITULO: ");
    Dados->TITLE = Le_String();
    //fflush_in();
    printf ("AUTOR: ");
    Dados->AUTHOR = Le_String();
    //fflush_in();
    printf ("IDIOMA: ");
    Dados->LANGUAGE = Le_String();
    //fflush_in();
    printf ("EDITORA: ");
    Dados->PUBLISHER = Le_String();
    //fflush_in();
    printf ("PAGINAS: ");
	scanf ("%d",&Dados->PAGES);
	printf ("ANO DE LANCAMENTO: ");
	scanf ("%d",&Dados->YEAR);
	printf ("PRECO: ");
	scanf ("%f", &Dados->PRICE);
	printf("\n");
}

void fflush_in(){// função para limpar o teclado
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void Insere(Livro *L){
    //Se o arquivo estiver vazio
    //Se não, procura registro removido
    //se nao houver, insere no final
    FILE *arq = fopen("livraria.txt", "r+");
    if(arq == NULL){
        printf("ERRO AO ABRIR ARQUIVO!!");
        return;
    }
    int tam_registro = -1;
    int aux;
    char removido;
    char c = '|';

    fseek(arq, 0, SEEK_SET); //colocando ponteiro no inicio do arquivo
    fread(&tam_registro, sizeof(int), 1, arq); //lendo primeiro int do arquivo(tamanho do primeiro registro)
    if(tam_registro == -1){ //se o arquivo estiver vazio
            aux = reglen(L);
            fprintf(arq, "%d", aux); //escrevendo tamanho do registro a ser inserido

            fwrite(L->TITLE, sizeof(char), strlen(L->TITLE), arq);
            fprintf(arq, "%c", c); //colocando delimitador

            fwrite(L->AUTHOR, sizeof(char), strlen(L->AUTHOR), arq);
            fprintf(arq, "%c", c); //colocando delimitador

            fwrite(L->PUBLISHER, sizeof(char), strlen(L->PUBLISHER), arq);
            fprintf(arq, "%c", c); //colocando delimitador

            fprintf(arq, "%d", L->YEAR);
            fprintf(arq, "%c", c); //colocando delimitador

            fwrite(L->LANGUAGE, sizeof(char), strlen(L->LANGUAGE), arq);
            fprintf(arq, "%c", c); //colocando delimitador

            fprintf(arq, "%d", L->PAGES);
            fprintf(arq, "%c", c); //colocando delimitador

            fprintf(arq, "%f", L->PRICE);
            fprintf(arq, "%c", c); //colocando delimitador
            return;
    }
    else{ //Se nao estiver vazio, procura primeira remoção logica para inserir
    //checa se o primeiro registro foi removido
    //se ja, confere tamanho livre no registro
    //      se o registro a ser inserido couber no registro removido, insere
    //se nao, passa para proximo
    }

    else{ //se nenhuma das opçoes der certo, insere no final do arquivo

    }


    /*Livro lv;
    Ler_dados_livro(&lv);*/

}

int reglen(Livro *L){ //Retorna o numero de bytes de um registro passado(conta os delimitadores mas nao conta os \0)
    int cont = 0;
    int i = 0;

    while(L->TITLE[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->AUTHOR[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->PUBLISHER[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->LANGUAGE[i] != '\0'){
        cont += sizeof(char);
        i++;
    }
    cont += 2*sizeof(int); //YEAR e PAGES
    cont += sizeof(float); //PRICE

    cont += 7*sizeof(char); //delimitadores

    return cont;
}

void print_livro(Livro lv){
    printf("\n############################\n\n");
    printf ("           |LIVRO|\n\n");
    printf("NOME : ");
    printf("%s\n",lv.TITLE);
    printf("AUTOR : ");
    printf("%s\n",lv.AUTHOR);
    printf("LINGUAGEM : ");
    printf("%s\n",lv.LANGUAGE);
    printf("EDITORA : ");
    printf("%s\n",lv.PUBLISHER);
    printf("PAGINAS : ");
    printf("%d\n",lv.PAGES);
    printf("ANO DE LANCAMENTO : ");
    printf("%d\n",lv.YEAR);
    printf("PRECO : ");
    printf("%0.2f\n",lv.PRICE);
    printf("\n############################\n\n");

}




