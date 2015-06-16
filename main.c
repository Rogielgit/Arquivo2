
#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "Indice.h"

int main()
{
    List * IndiceSecundarioAutor;
    List * IndiceSecundarioEditora;

    IndiceSecundarioAutor   = CriaIndiceAutor();
    IndiceSecundarioEditora = CriaIndiceEditora();

    FILE *arq;
    int ano;
    char Autor[30],Editora[30];

    List *segAutor,*segEditora;
  //Indice aut_ind,edi_ind;

   //aut_ind.tam=-1;
    //guardar no arquivo a quantidade de registro salvo.
    //verifica se arquivo existe, se não existir cria e coloca topo = -1
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
        printf("Tam-agora %d\n",tamanho);
        //se ainda não inicializou e tamanho > 10
       /* if( tamanho>=10 && aut_ind.tam==-1)
        {
            //aut_ind = Cria_Indice_Autor(tamanho);
            //edi_ind = Cria_Indice_Autor(tamanho);
        }*/

        printf("\n**************************\n");
        printf("           MENU\n");
        printf("**************************\n\n");
        printf("1-Inserir Livro\n");
        printf("2-Pesquisa Ano\n");
        printf("3-Listar\n");
        printf("4-Pesquisa Autor\n");
        printf("5-Pesquisa Editora\n");
        printf("6-Pesquisa Autor e Editora\n");
        printf("7-Pesquisa Autor ou Editora\n");
        printf("8-Remove\n");
        printf("9-Sair\n\n\n");
        printf("Opcao Desejada: ");
        setbuf(stdin,NULL);
        scanf(" %c",&op);
        ///criar o indice somente quando chegar a 10.
        switch (op){
            case '1':
                setbuf(stdin,NULL);
                Livro L;
                // Ler_dados_livro(&L);
                // InsereUmLivro(L);
                Insere();
                tamanho =Tamanho_Arquivos();
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
                fflush_in();
                printf("Autor: ");
                scanf("%[^\n]%*c", Autor);
                Pesquisar(IndiceSecundarioAutor, Autor);
                break;
            case '5':
                fflush_in();
                printf("Editora: ");
                scanf("%[^\n]%*c", Editora);
                Pesquisar(IndiceSecundarioEditora, Editora);
                break;
            case '6':
                printf("Autor: ");
                scanf("%[^\n]%*c", Autor);
                printf("Editora: ");
                scanf("%[^\n]%*c", Editora);
                PesquisarPeloAutorEPelaEditora(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor, Editora);
                break;
            case '7':
                printf("Autor: ");
                scanf("%[^\n]%*c", Autor);
                printf("Editora: ");
                scanf("%[^\n]%*c", Editora);
                PesquisarPeloAutorOuPelaEditora(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor, Editora);
                break;
            case '8':
                printf("Autor: ");
                scanf("%[^\n]%*c", Autor);
                OrganizaRemocao(IndiceSecundarioAutor, IndiceSecundarioEditora, Autor);
                break;
        }
        setbuf(stdin,NULL);
    }
    return 0;
}
