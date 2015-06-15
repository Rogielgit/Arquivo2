#ifndef INDICE_H
#define INDICE_H

#include "Lista.h"

typedef struct NoIndice NoIndice;

typedef struct indice Indice;

struct NoIndice
{
    char *chave;
   // void lista;
};

struct indice
{
    int tam;
    NoIndice *elem;
};


void Cria_Indice_Autor(List *,int tam);

void Cria_Indice_Editora(List*,int tam);

void Insere_Indice(List *,char *st,int byteoffset);

#endif
