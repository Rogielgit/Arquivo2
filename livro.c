
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

struct livro{

	char TITLE[48],AUTHOR[32],PUBLISHER[20],LANGUAGE[16]; // definição dos tamanhos
	int YEAR,PAGES;
	float PRICE;
};

//*************************************************************
void fflush_in(){// função para limpar o teclado
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


void Pesquisa_ano(int Ano)
{

    FILE *arq;
    int tamRegistro;
    char remLogica;
    char *registro;


    if((arq = fopen ("BD_livros.txt","rb")) == NULL)
        printf("Nao foi possivel abrir o arquivo!!\n");
        exit(0);

    fseek(arq,sizeof(int),SEEK_SET); // pula o conteúdo relacionado ao topo da pilha 

    while((fread(&tamRegistro,sizeof(int),1,arq))!= 1) // ler o tamanho
    {
        fread(&remLogica,sizeof(char),1,arq);
        if (remLogica == '*'); // o arquivo foi marcado como removido
        else
        {
            fseek(arq,sizeof(int),SEEK_CUR); // pula o byteoffiset
            registro = (char*)malloc((tamRegistro+1)*sizeof(char)); // aloca uma string do tamanho do registro
            fread (&registro,sizeof(tamRegistro),1,arq); 
            // tirar daqui
            printf("Titulo : %s\n", (char*)strtok(registro,"|")); // percorre o registro 
            printf("Autor : %s\n", (char*)strtok(NULL,"|"));
            printf("Editora : %s\n", (char*)strtok(NULL,"|"));
            printf("Linguagem : %s\n", (char*)strtok(NULL,"|"));
            printf("Pagina : %s\n", (char*)strtok(NULL,"|"));                
            printf("Ano de Lancamento : %s\n", (char*)strtok(NULL,"|"));                
            printf("Preco : %s\n", (char*)strtok(NULL,"|"));                
             
        }
    }
}

