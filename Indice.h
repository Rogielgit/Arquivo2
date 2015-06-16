#ifndef INDICE_H
#define INDICE_H

#include <stdlib.h>
#include <string.h>
#include "Lista.h"

typedef struct {
    char * Info;
    List * ListaInvertida;
} BlocoDoSecundario;

typedef struct { 
    int ByteOffSet;
} BlocoDaInvertida;

int InserirIndiceSecundario(List *, char *, int);

int RemoverIndiceSecundario(List *, char *, int);

int ComparaNomeNasListas(NoLista *, char *);

int ComparaByteOffSetNasListas(NoLista *, int);

int ComparaByteOffSetNasListasParaOrdenacao(NoLista *, int);

List * CriaIndiceAutor();

List * CriaIndiceEditora();

List * Merging(List *, List *);

List * Matching(List *, List *);

#endif // INDICE_H
