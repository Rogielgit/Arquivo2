#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

typedef struct {
    char *TITLE;
    char *AUTHOR;
    char *PUBLISHER;
    int YEAR;
    char *LANGUAGE;
    int PAGES;
    float PRICE;
} Livro;

char* Le_String();
void Ler_dados_livro(Livro*);
void fflush_in();
void InsereUmLivro(Livro*);
void Insere();
int reglen(Livro*);
void print_livro(Livro);

#endif // LIVRO_H_INCLUDED
