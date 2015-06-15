#ifndef LIVRO_H
#define LIVRO_H
#define SUCESSO 1
#include "Lista.h"



typedef struct {
    char *TITLE;
    char *AUTHOR;
    char *PUBLISHER;
    int YEAR;
    char *LANGUAGE;
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

void escreveRegistro(FILE*,Livro,int);

void Pesquisa_autor(List *, char *);

void Pesquisa_editora(List *, char *);

void Pesquisa_autor_ou_editora(List *, List *, char *, char *);

void Pesquisa_autor_e_editora(List *, List *, char *, char *);

void  Organiza_remocao(List *, char *);

int Tamanho_Arquivos();
// Soma ou subtrai do contador de registros
// Para criação do índice, que só é feita quando há 10+ registros.
void adicionaNaContagemDeRegistros(int);

// @arg char * -> Diretório do arquivo
// Retorna um vetor de duas posições
// A primeira é o ponteiro para o arquivo criado
// O segundo é o ponteiro para o índice(lista) em RAM
void * criarIndiceSecundarioAutor(char *);

// Mesma coisa da do Autor
void * criarIndiceSecundarioEditora(char *);

// Faz matching entre duas listas dadas no argumento
// Retorna o resultado num ponteiro de outra lista
List * matching(List *, List *);

// Faz merging entre duas listas dadas no argumento
// Retorna o resultado num ponteiro de outra lista
List * merging(List *, List *);

#endif // LIVRO_H

