
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"


int main() {


    List * Lista;
    Lista = CriaLista();
    InserirLista(Lista, 2);
    InserirLista(Lista, 1);
    InserirLista(Lista, 3);
    Ordena(&Lista->Primeiro, (FuncaoComparacao) ComparaChavePrimaria);

    return 0;
}

