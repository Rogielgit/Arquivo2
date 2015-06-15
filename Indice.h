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

int ComparaNomeNasListas(NoLista *, char *);

List * CriaIndiceAutor();

List * CriaIndiceEditora();

#endif // INDICE_H
