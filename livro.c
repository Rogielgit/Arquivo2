#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

char* Le_String(){ //coloca '\0' no fim da string lida
    char *str,c;
    int tamanho = 0, i = 1;
    str = (char*)malloc(sizeof(char));

    while(c!='\n'){
        c = getc(stdin);     //lendo caractere do teclado
        if(c=='\n')
            break;
        str = (char*)realloc(str,i*sizeof(char)); //realocando espaço
        str[tamanho] = c;  //grava caractere lido
        i++;
        tamanho++;
    }
    str[tamanho]='\0'; //coloca '\0'no fim da string
    return str;
}

void Ler_dados_livro(Livro *Dados){
    //fflush_in();
    printf ("TITULO: ");
    Dados->TITLE = Le_String();
    //fflush_in();
    printf ("AUTOR: ");
    Dados->AUTHOR = Le_String();
    //fflush_in();
    printf ("IDIOMA: ");
    Dados->LANGUAGE = Le_String();
    //fflush_in();
    printf ("EDITORA: ");
    Dados->PUBLISHER = Le_String();
    //fflush_in();
    printf ("PAGINAS: ");
	scanf ("%d",&Dados->PAGES);
	printf ("ANO DE LANCAMENTO: ");
	scanf ("%d",&Dados->YEAR);
	printf ("PRECO: ");
	scanf ("%f", &Dados->PRICE);
	printf("\n");
}

void fflush_in(){// função para limpar o teclado
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void escreveRegistro(FILE *arq, Livro *L){ //escreve na posicao atual no arquivo passado
      char c = '|';
      int tam_registro_inserir = reglen(L);
      //fprintf(arq, "%d", tam_registro_inserir);
      fwrite(&tam_registro_inserir, sizeof(int), 1, arq);

      fwrite(L->TITLE, sizeof(char), strlen(L->TITLE), arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      fwrite(L->AUTHOR, sizeof(char), strlen(L->AUTHOR), arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      fwrite(L->PUBLISHER, sizeof(char), strlen(L->PUBLISHER), arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      //fprintf(arq, "%d", L->YEAR);
      fwrite(&(L->YEAR), sizeof(int), 1, arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      fwrite(L->LANGUAGE, sizeof(char), strlen(L->LANGUAGE), arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      //fprintf(arq, "%d", L->PAGES);
      fwrite(&(L->PAGES), sizeof(int), 1, arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador

      //fprintf(arq, "%f", L->PRICE);
      fwrite(&(L->PRICE), sizeof(float), 1, arq);
      fwrite(&c, sizeof(char), 1, arq); //colocando delimitador
            return;
}

void InsereUmLivro(FILE *arq, Livro *L){
      /*FILE *arq = fopen("BD_livros2.bin", "rb+");
      if(arq == NULL){
        printf("ERRO AO ABRIR ARQUIVO!!");
        return;
      }*/
            int byteoffset = byteoffsetWorstFit(reglen(L)); //Retorna -1 se nenhum registro deletado for maior que o passado (ou nao houver reg. deletado)
            if(byteoffset == -1){ // Se for -1, insere no fim do arquivo
               fseek(arq, 0, SEEK_END); //Posicionando ponteiro para fim do arquivo
                  escreveRegistro(arq, L);
                  return;
            }
            fseek(arq, byteoffset, SEEK_SET); //Senao, pula pro byte offset retornado
            escreveRegistro(arq, L);
            return;
      fclose(arq);
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

      while(!feof(arq)){
            delimCont = 0;
            asterisco = NULL;
            tamAtual = 0;
            fseek(arq, offsetProx, SEEK_SET); // Pulando para registro no offset de offsetProx
            fread(&tamAtual, sizeof(int), 1, arq); // lendo primeiro int do registro (tamanho do registro)
            fread(&asterisco, sizeof(char), 1, arq); // lendo '*' do registro
            if(asterisco == '*'){
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
            else{
                  if(MaiorTam >= tam_reg){
                        if(offsetAnt == -1){
                              setTopo(-1);
                              return offsetMaior;
                        }
                        else{
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
void Insere(){
      FILE *arq = fopen("BD_livros2.bin", "rb+");
      if(arq == NULL)
        printf("Erro ao abrir arquivo!!!");

        Livro L;
        char op = 's';

        while(op == 's' || op == 'S'){
            Ler_dados_livro(&L);
            InsereUmLivro(arq, &L);
            printf("Registrar mais um Livro? (S/N)\n");
            fflush(stdin);
            scanf("%c", &op);
            fflush(stdin);
            while(op != 's' && op != 'S' && op != 'n' && op != 'N'){
                  printf("Opcao Invalida!!\n");
                  fflush(stdin);
                  scanf("%c", &op);
            }
        }
      return;
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

void Listar()
{
    FILE *fo = fopen("BD_livros2.bin", "rb");
    if(fo == NULL){
        printf("ERRO AO ABRIR ARQUIVO!!");
        return;
    }
    fseek(fo,sizeof(int),SEEK_SET); //pula o cabeçalho da pilha

    int tam;
    char st[150];
    fread(&tam,sizeof(int),1,fo);
  //  fread(&tam,sizeof(int),1,fo);
    fread(&st,tam,1,fo);
    printf("%s",st);
    while(feof(fo))
    {
        fread(&tam,sizeof(int),1,fo);
        fread(&st,tam,1,fo);
        printf("%s",st);
    }
}

int reglen(Livro *L){ //Retorna o numero de bytes de um registro passado(conta os delimitadores mas nao conta os \0)
    int cont = 0;
    int i = 0;

    while(L->TITLE[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->AUTHOR[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->PUBLISHER[i] != '\0'){
        cont += sizeof(char);
        i++;
    }

    i = 0;
    while(L->LANGUAGE[i] != '\0'){
        cont += sizeof(char);
        i++;
    }
    cont += 2*sizeof(int); //YEAR e PAGES
    cont += sizeof(float); //PRICE

    cont += 7*sizeof(char); //delimitadores

    return cont;
}

void print_livro(Livro lv){
    printf("\n############################\n\n");
    printf ("           |LIVRO|\n\n");
    printf("NOME : ");
    printf("%s\n",lv.TITLE);
    printf("AUTOR : ");
    printf("%s\n",lv.AUTHOR);
    printf("LINGUAGEM : ");
    printf("%s\n",lv.LANGUAGE);
    printf("EDITORA : ");
    printf("%s\n",lv.PUBLISHER);
    printf("PAGINAS : ");
    printf("%d\n",lv.PAGES);
    printf("ANO DE LANCAMENTO : ");
    printf("%d\n",lv.YEAR);
    printf("PRECO : ");
    printf("%0.2f\n",lv.PRICE);
    printf("\n############################\n\n");

}

