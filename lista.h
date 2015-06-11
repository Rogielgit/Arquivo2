
#ifndef LIVRO_H
#define LIVRO_H
#define ArgumentoInvalido -1
#define SUCESSO 1
#define ListaEstaVazia    - 29
#define ArgumentoInvalido -  1
#define False                0
#define True                 1
#define Sucesso              1


typedef int (* FuncaoComparacao)(const void *, const void *);

typedef struct {
    char *TITLE;
    char *AUTHOR;
    char *PUBLISHER;
    int YEAR;
    char *LANGUAGE;
    int PAGES;
    float PRICE;
}Livro;



typedef struct NoLista {
    char * Info;
    struct NoLista * Proximo;
} NoLista;

typedef struct{
    NoLista * Primeiro;
} List;



void Pesquisa_ano(int ); // procura livros sequencialmente no arquivo, de acordo com o ano oferecido
char* Le_String();
void Ler_dados_livro(Livro*);
void fflush_in();
void InsereUmLivro(FILE *arq, Livro*);
void Insere();
int reglen(Livro*);
void print_livro(Livro);
void Listar();
void setTopo(int value);



/**
 * @brief Cria uma Lista Ligada
 *
 * @return List * Ponteiro para a Lista
 */
List * CriaLista();

/**
 * @brief Libera toda a memória da Lista.
 *
 * @param List * Ponteiro para a Lista
 *
 * @return Retorna código de erro
 */
int DestroiLista(List * );

/**
 * @brief Verifica se a lista está vazia
 *
 * @param List * Ponteiro para a List
 *
 * @return Retorna o resultado (True/False)
 */
int ListaVazia(List * );

/**
 * @brief Insere um elemento
 *
 * @param List * Ponteiro para a Lista
 * @param void * Ponteiro para o Elemento
 *
 * @return Retorna código de erro
 */
int InserirLista(List *, char * );

/**
 * @brief Remove todos os elementos específicos
 *
 * @param List * Ponteiro para a Lista
 * @param FuncaoComparacao Funcao especifica para o Elemento
 * @param const void * Especifidade
 *
 * @return Retorna quantidade de elementos removidos
 */
int RemoverLista(List *, FuncaoComparacao, const void * );

/**
 * @brief Pesquisa na lista
 *
 * @param List * Ponteiro para a Lista
 * @param FuncaoComparacao Funcao específica para o Elemento
 * @param const void * Especifidade
 *
 * @return Retorna código de erro
 */
int BuscarLista (List *, FuncaoComparacao, const void * );

/**
 * @brief Ordena (QuickSort) a Lista
 *
 * @param NoLista ** Ponteiro de Ponteiro para o Primeiro Elemento
 * @param FuncaoComparacao Funcao específica para o tipo de Elemento
 *
 * @return Retorna código de erro
 */
void Ordena(NoLista **, FuncaoComparacao);

int ComparaNomeNasListas( NoLista *, char *);

#endif // LISTA_H

