
#ifndef LIVRO_H
#define LIVRO_H
#define ArgumentoInvalido -1
#define SUCESSO 1
#define ListaEstaVazia    - 29
#define ArgumentoInvalido -  1
#define False                0
#define True                 1
#define Sucesso              1


typedef int (* FuncaoComparacao)(const void *, const void *);

typedef struct {
    char *TITLE;
    char *AUTHOR;
    char *PUBLISHER;
    int YEAR;
    char *LANGUAGE;
    int PAGES;
    float PRICE;
}Livro;



typedef struct NoLista {
    char * Info;
    struct NoLista * Proximo;
} NoLista;

typedef struct{
    NoLista * Primeiro;
} List;



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


#endif // LIVRO_H





