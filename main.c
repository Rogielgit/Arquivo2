
#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "Indice.h"


int main()
{
    List * IndiceSecundarioAutor;
    List * IndiceSecundarioEditora;


    FILE *arq;
    int ano,flag=0;
    char Autor[30],Editora[30];

    arq = fopen("BD_livros2.bin", "rb+");
    if( arq == NULL )
    {   printf("Entrou\n");
        int aux=-1;
        arq = fopen("BD_livros2.bin", "wb+");
        fwrite(&aux,sizeof(int), 1, arq);
    }
    fclose(arq);
  
    int tamanho =0 ;

    char op='s';

    while( op != '9' )
    {
        tamanho =Tamanho_Arquivos();
       

        printf("\n**************************\n");
        printf("           MENU\n");
        printf("**************************\n\n");
        printf("1-Inserir Livro\n");
        printf("2-Pesquisa Ano\n");
        printf("3-Listar\n");
        printf("4-Pesquisa Autor\n");
        printf("5-Pesquisa Editora\n");
        printf("6-Pesquisa Autor Uniao Editora\n");
        printf("7-Pesquisa Autor Intersecao Editora\n");
        printf("8-Remove\n");
        printf("9-Sair\n\n\n");
        printf("Opcao Desejada: ");
        setbuf(stdin,NULL);
        scanf(" %c",&op);
      

        if (tamanho >= 10 && flag == 0){

            IndiceSecundarioAutor   = CriaIndiceAutor();
            IndiceSecundarioEditora = CriaIndiceEditora();
            flag=1;

        }
        ///criar o indice somente quando chegar a 10.
        switch (op){
            case '1':
                setbuf(stdin,NULL);
                Insere();
                tamanho = Tamanho_Arquivos();
                flag =0;
                break;
            case '2':
                printf("Ano: ");
                scanf("%d",&ano);
                setbuf(stdin,NULL);
                Pesquisa_ano(ano);
                break;
            case '3':
                Listar();
                break;
            case '4':

                printf("Autor: ");
                fflush_in();// função para limpar o teclado
                scanf("%[^\n]s", Autor);
               if (tamanho > 10)
                    Pesquisar(IndiceSecundarioAutor, Autor);
                else
                    Pesquisa_nome(Autor);

                
                
                break;
            case '5':
                fflush_in();// função para limpar o teclado
                printf("Editora: ");
                scanf("%[^\n]s", Editora);
                if (tamanho > 10)
                    Pesquisar(IndiceSecundarioEditora, Editora);
                else Pesquisa_editora(Editora);
                break;
            case '6':
                if (tamanho > 10){
                    printf("Autor: ");
                    fflush_in();// função para limpar o teclado
                    scanf("%[^\n]s", Autor);
                    printf("Editora: ");
                    fflush_in();// função para limpar o teclado
                    scanf("%[^\n]s", Editora);
                    PesquisarPeloAutorUniaoEditora(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor, Editora);
                    
                }else printf("Essa operacao nao eh permitida enquanto nao houver 10 registro%s\n");
                break;
            case '7':

                if (tamanho >= 10){
                    printf("Autor: ");
                    fflush_in();// função para limpar o teclado
                    scanf("%[^\n]s", Autor);
                    printf("Editora: ");
                    fflush_in();// função para limpar o teclado
                    scanf("%[^\n]s", Editora);
                    PesquisarPeloAutorIntersecaoEditora(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor, Editora);
                }else printf("Essa operacao nao eh permitida enquanto nao houver 10 registro");
                break;
            case '8':
                if (tamanho >= 10){
                    printf("Autor: ");
                    fflush_in();// função para limpar o teclado
                    scanf("%[^\n]s", Autor);
                    OrganizaRemocao(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor);
                    flag = 0;
                }else  printf("Essa operacao nao eh permitida enquanto nao houver 10 registro");
                break;
        }
        setbuf(stdin,NULL);
    }
    return 0;
}
