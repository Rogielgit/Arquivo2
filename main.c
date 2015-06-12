
#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
//#include "indice.h"

int main()
{
    FILE *arq;
  //  Indice aut_ind,edi_ind;
    int tamanho=Tamanho_Arquivos();
   // aut_ind.tam=-1;

    //verifica se arquivo existe, se não existir cria e coloca topo = -1
    arq = fopen("BD_livros2.bin", "rb+");

    if( arq == NULL )
    {
        int aux=-1;
        arq = fopen("BD_livros2.bin", "wb+");
        fwrite(&aux,sizeof(int), 1, arq);
    }
    //fclose(arq);
    char op='s';
    setTopo(-1); 
    while( op != '9' )
    {
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
        

        if (op == '1')
        {   
            setbuf(stdin,NULL);
            Livro L;
            Ler_dados_livro(&L);
            InsereUmLivro(L);
            tamanho++;
        }
        else if(op == '2')
        {
            int ano;
            printf("Ano: ");
            scanf("%d",&ano);
            setbuf(stdin,NULL);
            Pesquisa_ano(ano);

        }
        else if(op == '3')
        {   printf("Entrou Menu\n");
            Listar();
        }
        else if(op == '4')
        {

        }
        else if(op == '5')
        {
        }
        else if(op == '6')
        {

        }
        else if(op == '7')
        {

        }
        else if(op == '8')
        {

        }
        setbuf(stdin,NULL);
    }



    return 0;


/*
    List * Lista;
    Lista = CriaLista();
    InserirLista(Lista, 2);
    InserirLista(Lista, 1);
    InserirLista(Lista, 3);
    Ordena(&Lista->Primeiro, (FuncaoComparacao) ComparaChavePrimaria);
    printf("%d", Lista->Primeiro->Proximo->Info);
    RemoverLista(Lista, (FuncaoComparacao) ComparaChave, 2);
    printf("%d", Lista->Primeiro->Proximo->Info);
 

*/


}