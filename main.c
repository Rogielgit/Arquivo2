
#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "Indice.h"

int main()
{
    FILE *arq;
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


  //printf("Topo pilha %d\n",getTopo());
        printf("Opcao Desejada: ");
        setbuf(stdin,NULL);
        scanf(" %c",&op);
        ///criar o indice somente quando chegar a 10.


        if (op == '1')
        {   
            setbuf(stdin,NULL);
            Livro L;
         //   Ler_dados_livro(&L);
           // InsereUmLivro(L);
            Insere();
            tamanho =Tamanho_Arquivos();
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
        {  
            Listar();
        }
        else if(op == '4')
        {
            scanf("%s",Autor);
            //chamar função
        }
        else if(op == '5')
        {
             scanf("%s",Editora);
        }
        else if(op == '6')
        {   
            printf("Autor: ");
            scanf("%s",Autor);
            printf("Editora: ");
            scanf("%s",Editora);

        }
        else if(op == '7')
        {
            printf("Autor: ");
            scanf("%s",Autor);
            printf("Editora: ");
            scanf("%s",Editora);
        }
        else if(op == '8')
        {
            Remove_registro(0);
            //Remove_registro(25);
            //Remove_registro(48);          
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