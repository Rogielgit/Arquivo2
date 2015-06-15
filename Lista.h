#ifndef LISTA_H
#define LISTA_H

#define ListaEstaVazia    - 29
#define ArgumentoInvalido -  1
#define False                0
#define True                 1
#define Sucesso              1

typedef int  (* FuncaoComparacao)(const void *, const void *);

typedef struct NoLista {
    void *Info;
    struct NoLista * Proximo;
} NoLista;

typedef struct{
    NoLista * Primeiro;
} List;

/**
 * @brief Cria uma Lista Ligada
 *
 * @return List * Ponteiro para a Lista
 */
List * CriaLista();

/**
 * @brief Libera toda a mem�ria da Lista.
 *
 * @param List * Ponteiro para a Lista
 *
 * @return Retorna c�digo de erro
 */
int DestroiLista(List * );

/**
 * @brief Verifica se a lista est� vazia
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
 * @return Retorna c�digo de erro
 */
int InserirLista(List *, void * );

/**
 * @brief Remove todos os elementos espec�ficos
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
 * @param FuncaoComparacao Funcao espec�fica para o Elemento
 * @param const void * Especifidade
 *
 * @return Retorna c�digo de erro
 */
NoLista * BuscarLista (List *, FuncaoComparacao, const void * );

/**
 * @brief Ordena (QuickSort) a Lista
 *
 * @param NoLista ** Ponteiro de Ponteiro para o Primeiro Elemento
 * @param FuncaoComparacao Funcao espec�fica para o tipo de Elemento
 *
 * @return Retorna c�digo de erro
 */
void Ordena(NoLista **, FuncaoComparacao);

#endif // LISTA_H
