

#include <stdio.h>
#include <stdlib.h>


struct livro{

	char *TITLE,*AUTHOR,*PUBLISHER,*LANGUAGE; // definição dos tamanhos
	int YEAR,PAGES;
	float PRICE;
};

void print_livro(Livro lv)
{
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

void Pesquisa_ano(int Ano)
{

    FILE *arq;
    int tamRegistro;
    char remLogica;
    char *registro;


    if((arq = fopen ("BD_livros.txt","rb")) == NULL)
    	printf("Nao foi possivel abrir o arquivo!!\n");
    	exit(0);

    fseek(arq,sizeof(int),SEEK_SET); // pula o conteúdo relacionado ao topo da pilha 

    while((fread(&tamRegistro,sizeof(int),1,arq))!=NULL) // ler o tamanho
    {

    	fread(&remLogica,sizeof(char),1,arq)
    	if (remLogica == '*'); // o arquivo foi marcado como removido
    	else
    	{
    		fseek(arq,sizeof(int),SEEK_CUR); // pula o byteoffiset
    		registro = (char*)malloc((tamRegistro+1),sizeof(char)); // aloca uma string do tamanho do registro

    		fread (&registro,sizeof(tamRegistro),1,arq);
    		 // fazer a parte para separar
    		
    	}





    }








}





int main () {




	return 0;
}
