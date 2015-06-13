#ifndef INDICE_H
#define INDICE_H

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


Indice Cria_Indice_Autor(int tam);

Indice Cria_Indice_Editora(int tam);

void Insere_Indice(Indice *ind,char *st,int bos);

#endif
