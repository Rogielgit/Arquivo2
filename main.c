#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"


int main() {
    FILE *arq = fopen("BD_livros2.bin", "rb+");
    Livro L;
    if(arq == NULL)
        printf("Erro ao abrir arquivo!!!");

    //setTopo(-1); // 4, 31, 58
    //setTopo(4);
    //setTopo(31);
    //setTopo(58);
    printf("Topo: %d\n", getTopo());
    //Ler_dados_livro(&L);
    //InsereUmLivro(&L);
    Insere();
    //Listar();
    //printf("  Tamanho do Registro (REGLEN) %d\n\n", reglen(&L));
    //escreveRegistro(arq, &L);
    //printf("%s", Le_String());

    //print_livro(L);

system("pause");



    return 0;
}











