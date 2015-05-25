#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"


int main() {
    FILE *arq = fopen("livraria.txt", "r+");
    if(arq == NULL)
        printf("Erro ao abrir arquivo!!!");

    Livro L;
    Ler_dados_livro(&L);
    print_livro(L);







}











