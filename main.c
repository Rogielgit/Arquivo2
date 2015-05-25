#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"


int main() {
    FILE *arq = fopen("livraria.txt", "r+");
    if(arq == NULL)
        printf("Erro ao abrir arquivo!!!");

    Livro L;

    char *s = Le_String();
    printf("%s", s);
    fwrite(s, sizeof(char), strlen(s), arq);
    //Ler_dados_livro(&L);
    //print_livro(L);
    //printf("%s", L.TITLE);

system("pause");




}











