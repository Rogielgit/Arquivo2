#ifndef LIVRO_H
#define LIVRO_H
#define ArgumentoInvalido -3
#define SUCESSO 1

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


#endif // LIVRO_H
