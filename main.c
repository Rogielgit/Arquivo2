
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
    printf("%d", Lista->Primeiro->Proximo->Info);
    RemoverLista(Lista, (FuncaoComparacao) ComparaChave, 2);
    printf("%d", Lista->Primeiro->Proximo->Info);
 



 
    return 0;
}

