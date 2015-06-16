
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

void escreveRegistro(FILE *arq,Livro L,int byteoffset, int valorInsuf)  //escreve na posicao atual no arquivo passado
{
 
    char c = '|';
    int tam_registro_inserir = reglen(L);
    if(byteoffset == -1)
    {
        fseek(arq,0,SEEK_END);
        fwrite(&tam_registro_inserir,sizeof(int), 1, arq);
    }
    else if (valorInsuf == EscrevetamanhoOriginal)
        fseek(arq,2*sizeof(int) + byteoffset,SEEK_SET); // nao substitue o tamanho original
    else
    {
        fseek(arq,byteoffset + sizeof(int),SEEK_SET);
        fwrite(&tam_registro_inserir,sizeof(int), 1, arq);
    }

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

void Remove_registro(int byteoffset)
{
    FILE *arq;
    int tamRegistro,topo;
    char aux[50],removido = '*';
    arq = fopen("BD_livros2.bin","rb+");     // tratar erro

    fseek (arq,sizeof(int),SEEK_SET); // pula cabecalho da pilha
    
    fseek(arq,byteoffset,SEEK_CUR); 
    fread(&tamRegistro,sizeof(int),1,arq); // ler o tamanho
    printf("TaRemovido: %d\n",tamRegistro );
    fwrite(&removido,sizeof(char),1,arq);
    fscanf(arq,"%[^|]s",aux); //restante do titulo    
    fseek (arq,sizeof(char), SEEK_CUR);
    fscanf(arq,"%[^|]s",aux); // autor 
    fseek (arq,sizeof(char), SEEK_CUR);
    fscanf(arq,"%[^|]s",aux); // editora
    fseek (arq,sizeof(char),SEEK_CUR);
    
    topo = getTopo();
    fwrite(&topo,sizeof(int),1,arq); // salva o topo da pilha no ano
    setTopo(byteoffset);

    fclose(arq);
}

int byteoffsetWorstFit(int tam_reg, int *valorInsuf){
    // Retornos:      -1 se nao houver registro deletado maior do que o tamanho passado
    //                -1 se nao houver nenhum reg. deletado
    //                (int)byte offset do maior registro deletado
    FILE *arq;
    int topoPilha, anteriorPilha, proximoPilha;
    int tamAtual, anterior;    
    int offsetMaior = -1,diferenca,topo;
    int MaiorTam = 0, flag = 0;
    int proxRemovido;
    char aux,removido = '*', NomeAux[50];
    char c = '|';
    arq = fopen("BD_livros2.bin", "rb+");
    topoPilha = anteriorPilha = proximoPilha = getTopo(); //offset do proximo removido
    if(proximoPilha == -1)
    { //Se o topo da pilha for -1
        fclose(arq);   
        return -1;
        
    }
    while(!feof(arq))
    {   
       
        if(proximoPilha == -1) //Se o topo da pilha for -1
            break;      

        printf("proximoPilha: %d\n",proximoPilha);
      
        fseek(arq,proximoPilha + sizeof(int),SEEK_SET); // Pulando para registro no offset de offsetProx
        fread(&tamAtual,sizeof(int),1,arq); // lendo primeiro int do registro (tamanho do registro)
        
        fscanf(arq, "%[^|]s",NomeAux);//restante do titulo
        fseek(arq,sizeof(char),SEEK_CUR); // |
        fscanf(arq, "%[^|]s",NomeAux); // autor
        fseek(arq,sizeof(char),SEEK_CUR); // |
        fscanf(arq, "%[^|]s",NomeAux); // Editora
        fseek(arq,sizeof(char),SEEK_CUR); // |

        fread(&proximoPilha,sizeof(int),1,arq); // como eh um arquivo removido, contém o proximo topo da pilha e não o ano
        printf("tamAtual: %d\n",tamAtual);
        if(tamAtual >= MaiorTam)
        {   
            MaiorTam = tamAtual;
            anterior = anteriorPilha;
            anteriorPilha = topoPilha;            
            topoPilha = proximoPilha;    
        }
   }
  printf("MaiorTam: %d\n",MaiorTam );
   if (MaiorTam >= tam_reg){

        fseek(arq, anterior + sizeof(int), SEEK_SET);// acessar o ultimo que chamou   
        //busca o endereço para o proximo que esta na pilha
        fread(&tamAtual,sizeof(int),1,arq);
        fscanf(arq,"%[^|]s",NomeAux);//restante do titulo
        fseek(arq,sizeof(char),SEEK_CUR); // |
        fscanf(arq, "%[^|]s",NomeAux); // autor
        fseek(arq,sizeof(char),SEEK_CUR); // |
        fscanf(arq, "%[^|]s",NomeAux); // Editora
        fseek(arq,sizeof(char),SEEK_CUR); // |
        fread(&proxRemovido,sizeof(int),1,arq);

       
        if ((MaiorTam - tam_reg) < 12)// só insere se for maior que doze(devido a tam*|||byteoffset)
        {              

            if (topoPilha != -1)         
                fwrite(&topoPilha,sizeof(int),1,arq);
                   
            else
                setTopo(-1);

            *valorInsuf = EscrevetamanhoOriginal;
            return anteriorPilha;
        }
        else
        {   
 
            fseek(arq,(2*sizeof(int) + anterior + tam_reg), SEEK_SET);
            diferenca = MaiorTam - tam_reg - 2*sizeof(int); // sizeof(int) desconta o tamanho
            printf("diferenca: %d\n",diferenca);
            fwrite(&diferenca,sizeof(int),1,arq);        
            fwrite(&removido,sizeof(char),1,arq);
            fwrite(&c,sizeof(char),1,arq);
            fwrite(&c,sizeof(char),1,arq);
            fwrite(&c,sizeof(char),1,arq);
            fwrite(&proxRemovido,sizeof(int),1,arq);
    
            setTopo(anterior + tam_reg + sizeof(int));        
            fclose(arq);
            return anteriorPilha;
        }        
        printf("anterior, anteriorPilha, topoPilha, proximoPilha %d %d %d %d\n",anterior,anteriorPilha,topoPilha,proximoPilha );
        
    }
fclose(arq);
return -1;         
}

int Tamanho_Arquivos()
{
    FILE *arq;
    arq = fopen("BD_livros2.bin","rb");
    int tam=0;
    int i;
    char NomeAux[50];
    fseek(arq,sizeof(int),SEEK_SET);
  
    while(1)
    {
        fread(&i,sizeof(int),1,arq);
        if(feof(arq))
            break;
        fscanf(arq, "%[^|]s",NomeAux);
        i-=strlen(NomeAux);
        if(NomeAux[0] != '*')
        {       
            fseek(arq,i,SEEK_CUR);
            tam++;
        }
    }
    fclose(arq);
    return tam;
}

void InsereUmLivro(FILE *arq,Livro L)
{   
    int valorInsuf = 0; 
    int byteoffset = byteoffsetWorstFit(reglen(L), &valorInsuf);
    escreveRegistro(arq,L,byteoffset,valorInsuf);
}

void Insere(){
    
    FILE *arq = fopen("BD_livros2.bin", "rb+");
    if(arq == NULL)
    printf("Erro ao abrir arquivo!!!");
    Livro L;
    char op = 's';
   // fseek(arq, sizeof(int), SEEK_SET); // pula o cabeçalho da pilha
    while(op == 's' || op == 'S'){
                
        Ler_dados_livro(&L);
        InsereUmLivro(arq,L);
        printf("Registrar mais um Livro? (S/N)\n");
        fflush(stdin);
        scanf(" %c",&op);
        fflush(stdin);

        while(op != 's' && op != 'S' && op != 'n' && op != 'N'){

            printf("Opcao Invalida!!\n");
            fflush(stdin);
            
            scanf("%c", &op);
        }
    
    }
fclose(arq);    

}

void Listar()
{   
    
    FILE *arq;
    arq = fopen("BD_livros2.bin", "rb");
    char opc = 's';
    Livro lv;
    char st[100];
    int tam;
    int tamRegistro;
    int auxi,flag = 0,aux;
    float auxf;
    fseek (arq , sizeof(int) , SEEK_SET); // pula o cabeçalho
    fread(&tam,sizeof(int),1,arq);
  
    if (feof(arq))
    {
        printf("Arquivo vazio.");
    }
    else while(opc!= 'n')
    {    
        printf("TA: %d\n",tam);
        tamRegistro = 0; 
        fscanf(arq,"%[^|]s",st);
        printf("st[0]= %c\n",st[0]);
        if( st[0] == '*')
        {              
            fseek(arq,-strlen(st),SEEK_CUR);       
            fseek(arq,tam,SEEK_CUR);       
            flag = 1;
        }
        else
        {               
            printf("\n|***Livro***|\n\n");   
            printf("TITLE : %s\n",st);
            tamRegistro +=strlen(st) + 1; 
            fseek (arq, sizeof(char), SEEK_CUR);

            fscanf(arq,"%[^|]s",st);
            tamRegistro +=strlen(st) + 1;
            printf("AUTHOR : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fscanf(arq,"%[^|]s",st);
            tamRegistro +=strlen(st) + 1;
            printf("PUBLISHER : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fread(&auxi,sizeof(int),1,arq);
            printf("YEAR : %d\n",auxi);

            fscanf(arq,"%[^|]s",st);
            tamRegistro +=strlen(st) + 1;
            printf("LANGUAGE : %s\n",st);
            fseek (arq, sizeof(char), SEEK_CUR);

            fread(&auxi,sizeof(int),1,arq);
            printf("PAGES : %d\n",auxi);

            fread(&auxf,sizeof(float),1,arq);
            printf("PRICE : %.2f\n",auxf);
            tamRegistro += 2*sizeof(int) + sizeof(float); // tamanho do registro
            
            fseek(arq,(tam - tamRegistro),SEEK_CUR);

       }
       fread(&tam,sizeof(int),1,arq);
        if (feof(arq))
        {
            printf("\nA lista de livros terminou.\n");
            break;
        }
        else
        {   
            if (flag == 0) // para não aparecer esse menu quando algum registro for removido
            {
                
                printf("\nDeseja continuar listando(s/n)?\n");
                fflush_in();// função para limpar o teclado
                scanf("%c",&opc);
                setbuf(stdin,NULL);
                
            }else 
                flag = 0; 
        }
        
  
    }
    fclose(arq);
}

void Pesquisa_ano(int Ano_procurado)
{

    FILE *arq;
    int tam;
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

    while(fread(&tam,sizeof(int),1,arq) == 1) // ler o tamanho
    {         
        fscanf(arq,"%[^|]s",aux); //Title
        if(aux[0] == '*' )
        {   
        
            fseek(arq,tam -strlen(aux), SEEK_CUR);
            fseek(arq,tam, SEEK_CUR);
        }      
        else
        {            
            tamRegistro = 0;
            tamRegistro+= strlen(aux) +1;
            strcpy(registro,aux); 
            strcat(registro,separador);     
            fseek (arq,sizeof(char), SEEK_CUR);
            fscanf(arq,"%[^|]s",aux); // autor
            tamRegistro+= strlen(aux) +1;
            strcat(registro,aux); 
            strcat(registro,separador);
           
            fseek (arq,sizeof(char), SEEK_CUR);
            fscanf(arq,"%[^|]s",aux); // Editora
            tamRegistro+= strlen(aux) +1;
            strcat(registro,aux); 
            strcat(registro,separador);

           
            fseek (arq,sizeof(char), SEEK_CUR);
            fread(&ano,sizeof(int),1,arq); //ano
           
            fscanf(arq,"%[^|]s",aux); // linguagem
            tamRegistro+= strlen(aux) + 1;
            strcat(registro,aux);
            strcat(registro,separador);
           
            fseek (arq,sizeof(char), SEEK_CUR);
            fread(&pagina,sizeof(int),1,arq);  // preco         
            fread(&preco,sizeof(float),1,arq); 
      
            tamRegistro+= 2*sizeof(int) + sizeof(float); // para tratar o caso em que foi inserido no lugar de um removido
            fseek(arq, (tam-tamRegistro),SEEK_CUR);            

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






























