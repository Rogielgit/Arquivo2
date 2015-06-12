
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

void fflush_in(){// função para limpar o teclado

    getchar();
}


void Print_Livro(Livro lv)
{
    printf("Nome: %s",lv.TITLE);
    printf("\nAutor: %s",lv.AUTHOR);
    printf("\nEditora: %s\tAno: %d",lv.PUBLISHER,lv.YEAR);
    printf("\nIdioma: %s",lv.LANGUAGE);
    printf("\nPaginas: %d\tPreco: %.2f\n",lv.PAGES,lv.PRICE);
}

char* Le_String()
{
    char *str,leit[100];
    setbuf(stdin,NULL);
    scanf("%[^\n]s",leit);
    str = (char*)malloc( sizeof(char) * strlen(leit) );
    strcpy(str,leit);
    return str;
}

int reglen(Livro L)  //Retorna o numero de bytes de um registro passado(conta os delimitadores mas nao conta os \0)
{
    int cont = 0;
    cont += strlen(L.TITLE);
    cont += strlen(L.AUTHOR);
    cont += strlen(L.PUBLISHER);
    cont += strlen(L.LANGUAGE);
    cont += 2*sizeof(int); //YEAR e PAGES
    cont += sizeof(float); //PRICE
    cont += 4*sizeof(char); //delimitadores
    return cont;
}

void Ler_dados_livro(Livro *Dados)
{

    printf ("TITULO: ");
    fflush_in();
    Dados->TITLE = Le_String();
    printf ("AUTOR: ");
    Dados->AUTHOR = Le_String();
    printf ("LINGUAGEM: ");
    Dados->LANGUAGE = Le_String();
    printf ("EDITORA: ");
    Dados->PUBLISHER = Le_String();
    printf ("PAGINAS: ");
    scanf ("%d",&Dados->PAGES);
    printf ("ANO DE LANCAMENTO: ");
    scanf ("%d",&Dados->YEAR);
    printf ("PRECO: ");
    scanf ("%f",&Dados->PRICE);
    printf("\n");

}

void escreveRegistro(Livro L,int byteoffset)  //escreve na posicao atual no arquivo passado
{
    FILE *arq;
    arq = fopen("BD_livros2.bin", "rb+");
    char c = '|';
    int tam_registro_inserir = reglen(L);
    if(byteoffset == -1)
        fseek(arq,0,SEEK_END);
    else
        fseek(arq,byteoffset,SEEK_SET);

    fwrite(&tam_registro_inserir,sizeof(int), 1, arq);

    fwrite(L.TITLE, sizeof(char), strlen(L.TITLE), arq);
    fwrite(&c,sizeof(char), 1, arq); //colocando delimitador

    fwrite(L.AUTHOR,sizeof(char), strlen(L.AUTHOR), arq);
    fwrite(&c,sizeof(char), 1, arq); //colocando delimitador

    fwrite(L.PUBLISHER,sizeof(char), strlen(L.PUBLISHER), arq);
    fwrite(&c,sizeof(char), 1, arq); //colocando delimitador

    fwrite(&(L.YEAR),sizeof(int), 1, arq);

    fwrite(L.LANGUAGE,sizeof(char),strlen(L.LANGUAGE), arq);
    fwrite(&c,sizeof(char), 1, arq); //colocando delimitador

    fwrite(&(L.PAGES),sizeof(int), 1, arq);

    fwrite(&(L.PRICE),sizeof(float),1,arq);
    fclose(arq);
}

int getTopo(){ //funcao para pegar o topo da pilha

    FILE * File;
    int Topo;
    Topo = -1;
    File = fopen("BD_livros2.bin", "rb");
    if (File != NULL)
        fread(&Topo,sizeof(int),1,File);
    fclose(File);


return Topo;
}

void setTopo(int value){ // funcao para colocar elemento no topo da pilha

    FILE * File;
    File = fopen("BD_livros2.bin", "rb+");
    int Topo;
    Topo = value;
    fwrite(&Topo,sizeof(int),1,File);
    fclose(File);
}

int byteoffsetWorstFit(int tam_reg){
    // Retornos:      -1 se nao houver registro deletado maior do que o tamanho passado
    //                -1 se nao houver nenhum reg. deletado
    //                (int)byte offset do maior registro deletado
    FILE *arq = fopen("BD_Livros2.bin", "rb");
    int offsetProx = getTopo(); //offset do proximo removido
    int tamAtual;
    int offsetAnt = -1;
    int offsetMaior = -1;
    int MaiorTam = 0;
    int delimCont; // contador de delimitadores
    char aux;
    char asterisco;

    if(offsetProx == -1) //Se o topo da pilha for -1
        return -1;

    while(!feof(arq))
    {

      delimCont = 0;
      asterisco = '\0';
      tamAtual = 0;
      fseek(arq, offsetProx, SEEK_SET); // Pulando para registro no offset de offsetProx
      fread(&tamAtual, sizeof(int), 1, arq); // lendo primeiro int do registro (tamanho do registro)
      fread(&asterisco, sizeof(char), 1, arq); // lendo '*' do registro
      if(asterisco == '*')
      {
        if(tamAtual >= MaiorTam){

            MaiorTam = tamAtual;
            offsetAnt = offsetMaior;
            offsetMaior = offsetProx;
        }
                  //Encontrando campo YEAR (onde esta o byteoffset do proximo elemento da pilha)
                  /*while(delimCont != 3){ //Enquanto nao contarmos 3 delimitadores
                        fread(&aux, sizeof(char), 1, arq); //le um caractere
                        if(aux == '|') //Se for igual ao delimitador, incrementa delimCont
                              delimCont++;
                  }*/
        fread(&offsetProx, sizeof(int), 1, arq); // Lendo proximo byteoffset
        }
        else
        {
            if(MaiorTam >= tam_reg)
            {

                if(offsetAnt == -1)
                {
                    setTopo(-1);
                    return offsetMaior;
                }
                else
                {
                        //Reajustando Pilha
                    fseek(arq, offsetAnt, SEEK_SET); //Reajusta ponteiro para registro removido anterior ao offsetMaior
                    fseek(arq, sizeof(int), SEEK_CUR); //Pulando tamanho do registro do reg anterior removido
                    fseek(arq, sizeof(char), SEEK_CUR); //Pulando asterisco do reg anterior removido
                              //delimCont = 0;
                              //Procurando campo YEAR
                              /*while(delimCont != 3){ //Enquanto nao contarmos 3 delimitadores
                                    fread(&aux, sizeof(char), 1, arq); //le um caractere
                                    if(aux == '|') //Se for igual ao delimitador, incrementa delimCont
                                          delimCont++;
                              }*/
                    int x = -1;
                    fwrite(&x, sizeof(int), 1, arq); //
                    return offsetMaior;
                }
            }
            else return -1;
        }
    }
}

int Tamanho_Arquivos()
{
    FILE *arq;
    arq = fopen("BD_livros2.bin","rb");
    int tam=0;
    int i;
    fread(&i,sizeof(int),1,arq);
    while(1)
    {
        fread(&i,sizeof(int),1,arq);
        if(feof(arq))
            break;
        fseek(arq,i,SEEK_CUR);
        tam++;
    }
    fclose(arq);
    return tam;
}

void InsereUmLivro(Livro L){
    int byteoffset = byteoffsetWorstFit(reglen(L)); //Retorna -1 se nenhum registro deletado for maior que o passado (ou nao houver reg. deletado)
    escreveRegistro(L,byteoffset);
}

void Listar()
{   
    printf("Entrou\n");
    FILE *arq;
    arq = fopen("BD_livros2.bin", "rb");
    char opc = 's';
    Livro lv;
    char st[100];
    int tam;
    int auxi;
    float auxf;
    fseek (arq , sizeof(int) , SEEK_SET); // pula o cabeçalho
    fread(&tam,sizeof(int),1,arq);
    if (feof(arq))
    {
        printf("Arquivo vazio.");
    }
    else while(opc!='n')
    {   
        printf("\n|***Livro***|\n\n");        
        fscanf(arq,"%[^|]s",st);
        if( st[0] == '*' )
        {
            fseek(arq, tam-strlen(st), SEEK_CUR);
        }
        else
        {
           
            printf("TITLE : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fscanf(arq,"%[^|]s",st);
            printf("AUTHOR : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fscanf(arq,"%[^|]s",st);
            printf("PUBLISHER : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fread(&auxi,sizeof(int),1,arq);
            printf("YEAR : %d\n",auxi);

            fscanf(arq,"%[^|]s",st);
            printf("LANGUAGE : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fread(&auxi,sizeof(int),1,arq);
            printf("PAGES : %d\n",auxi);

            fread(&auxf,sizeof(float),1,arq);
            printf("PRICE : %.2f\n",auxf);

        }

        fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
        {
            printf("\nA lista de livros terminou.\n");
            break;
        }
        else
        {
            printf("\nDeseja continuar listando(s/n)?\n");
            fflush_in();// função para limpar o teclado
            scanf("%c",&opc);
            setbuf(stdin,NULL);
        }
    }
    fclose(arq);
}

void Pesquisa_ano(int Ano_procurado)
{

    FILE *arq;
    int tamRegistro;
    char remLogica = '0'; //teste
    char registro[100],aux[50];
    int ano,pagina,flag = 0;
    float preco;
    char separador[] = "|";


    if((arq = fopen("BD_livros2.bin","rb")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!!\n");
        exit(0);
    }

    fseek(arq,sizeof(int),SEEK_SET); // pula o conteÃºdo relacionado ao topo da pilha 
    if (feof(arq))
    {
        printf("Arquivo vazio.");
        fclose(arq);
        return;
    }

    while(fread(&tamRegistro,sizeof(int),1,arq) == 1) // ler o tamanho
    {  


        fscanf(arq,"%[^|]s",aux); //Title
        if(aux[0] == '*' )
        {
            fseek(arq, tamRegistro-strlen(aux), SEEK_CUR);
        }      
        else
        {
            //fseek(arq,sizeof(int),SEEK_CUR); // pula o byteoffiset
            strcpy(registro,aux); 
            strcat(registro,separador);     
            fseek (arq,sizeof(char), SEEK_CUR);
            fscanf(arq,"%[^|]s",aux); // autor
            strcat(registro,aux); 
            strcat(registro,separador);
           
            fseek (arq,sizeof(char), SEEK_CUR);
            fscanf(arq,"%[^|]s",aux); // Editora
            strcat(registro,aux); 
            strcat(registro,separador);

           
            fseek (arq,sizeof(char), SEEK_CUR);
            fread(&ano,sizeof(int),1,arq); //ano
           
            fscanf(arq,"%[^|]s",aux); // linguagem
            strcat(registro,aux);
            strcat(registro,separador);
           
            fseek (arq,sizeof(char), SEEK_CUR);
            fread(&pagina,sizeof(int),1,arq);  // preco         
            fread(&preco,sizeof(float),1,arq); 
      
            if (ano == Ano_procurado)
            {
              printf("\n|***Livro***|\n\n");    
              printf("Titulo : %s\n", (char*)strtok(registro,"|")); // percorre o registro 
              printf("Autor : %s\n", (char*)strtok(NULL,"|"));
              printf("Editora : %s\n", (char*)strtok(NULL,"|"));
              printf("Linguagem : %s\n", (char*)strtok(NULL,"|"));
              printf("Ano: %d\nPagina: %d\nPreco: %0.2f\n\n\n",ano,pagina,preco);
              flag = 1;

              

            }          
        }
    }
    if (flag == 0) 
        printf("NAO EXISTE NENHUM LIVRO COM ESSE ANO!\n\n");
    fclose(arq);
}

