#ifndef LIVRO_H
#define LIVRO_H
#define SUCESSO 1
#define EscrevetamanhoOriginal  -2
#include "Indice.h"

typedef struct {
    char * TITLE;
    char * AUTHOR;
    char * PUBLISHER;
    int YEAR;
    char * LANGUAGE;
    int PAGES;
    float PRICE;

}Livro;


void fflush_in();// função para limpar o teclado

void Pesquisa_ano(int ); // procura livros sequencialmente no arquivo, de acordo com o ano oferecido

char* Le_String();

void Ler_dados_livro(Livro*);

void fflush_in();

void InsereUmLivro(FILE *,Livro);

void Insere();

void Remove_registro(int byteoffset);

int reglen(Livro);

void print_livro(Livro);

void Listar();

void setTopo(int value);

int getTopo();

void escreveRegistro(FILE *, Livro, int, int);

void Pesquisar(List *, char *);

void PesquisarPeloAutorUniaoEditora(List *, List *, char *, char *);

void PesquisarPeloAutorIntersecaoEditora(List *, List *, char *, char *);

void  OrganizaRemocao(List *, List *, char *);

int Tamanho_Arquivos();

void adicionaNaContagemDeRegistros(int);

Livro * ResgatarRegistro(int);

#endif // LIVRO_H

