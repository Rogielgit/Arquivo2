#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

char* Le_String(){ //coloca '|' e '\0' no fim da string lida
    char *str,c;
    int tamanho = 0, i = 3;
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
    tamanho++;
    str[tamanho] = '|';

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

void Insere(){
    //Se o arquivo estiver vazio
    //Se não, procura registro removido
    //se nao houver, insere no final

    FILE *arq = fopen("livraria.txt", "r+");
    if(arq == NULL){
        printf("ERRO AO ABRIR ARQUIVO!!");
        return;
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




