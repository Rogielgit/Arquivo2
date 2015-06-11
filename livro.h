#ifndef LIVRO_H
#define LIVRO_H
#define ArgumentoInvalido -3
#define SUCESSO 1

//#include "Lista.h"

typedef struct {
    char *TITLE;
    char *AUTHOR;
    char *PUBLISHER;
    int YEAR;
    char *LANGUAGE;
    int PAGES;
    float PRICE;
}Livro;


void Pesquisa_ano(int ); // procura livros sequencialmente no arquivo, de acordo com o ano oferecido
char* Le_String();
void Ler_dados_livro(Livro*);
void fflush_in();
void InsereUmLivro(FILE *arq, Livro*);
void Insere();
int reglen(Livro*);
void print_livro(Livro);
void Listar();
void setTopo(int value);

// Soma ou subtrai do contador de registros
// Para cria��o do �ndice, que s� � feita quando h� 10+ registros.
void adicionaNaContagemDeRegistros(int);

// @arg char * -> Diret�rio do arquivo
// Retorna um vetor de duas posi��es
// A primeira � o ponteiro para o arquivo criado
// O segundo � o ponteiro para o �ndice(lista) em RAM
void * criarIndiceSecundarioAutor(char *);

// Mesma coisa da do Autor
void * criarIndiceSecundarioEditora(char *);

// Faz matching entre duas listas dadas no argumento
// Retorna o resultado num ponteiro de outra lista
///List * matching(List *, List *);



// Faz merging entre duas listas dadas no argumento
// Retorna o resultado num ponteiro de outra lista
//List * merging(List *, List *);


#endif // LIVRO_H
