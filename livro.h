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

#endif // LIVRO_H_INCLUDED
