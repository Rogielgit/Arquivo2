#include "Lista.h"
#include "stdlib.h"

List * CriaLista(){
    // Declara, Aloca e Inicializa a Lista
    List * Lista;
    Lista = (List*)malloc(sizeof(List));
    Lista->Primeiro = NULL;

return Lista;
}

int DestroiLista(List * Lista){
    // Validade do Argumento
    if (Lista == NULL)
        return ArgumentoInvalido;

    // Auxiliar
    NoLista * Auxiliar;
    Auxiliar = Lista->Primeiro;
    // Percorre a pilha removendo
    while (Auxiliar != NULL){
        free(Auxiliar);
        Auxiliar = Auxiliar->Proximo;
    }
    // Libera a memória
    free(Lista);
}

int ListaVazia(List * Lista){
    // Validade do Argumento
    if (Lista == NULL)
        return ArgumentoInvalido;
    // Verifica se há um primeiro elemento
    if (Lista->Primeiro == NULL)
        return True;
    return False;
}

int InserirLista(List * Lista, void * Info){
    // Validade dos Argumentos
    if (Lista == NULL || Info == NULL)
        return ArgumentoInvalido;

    // Auxiliares
    NoLista * L;
    L = (NoLista*) malloc(sizeof(NoLista));
    L->Info    = Info;
    L->Proximo = NULL;

    // Insere como primeira se vazia
    if (ListaVazia(Lista)){
        Lista->Primeiro = L;
        return Sucesso;
    }

    // Insere no início
    L->Proximo = Lista->Primeiro;
    Lista->Primeiro = L;
    return Sucesso;
}

NoLista * BuscarLista(List * Lista, FuncaoComparacao Comparacao, const void * arg){
    // Validade dos Argumentos
    if (Lista == NULL || Comparacao == NULL || arg == NULL)
        return ArgumentoInvalido;

    // Auxiliares
    NoLista * L;
    L = Lista->Primeiro;
    // Percorre a lista comparando o elemento
    while (L != NULL){
        // Se encontrar, retorna positivamente
        if (Comparacao(L, arg))
            return L;
        L = L->Proximo;
    }
    return False;
}

int RemoverLista(List * Lista, FuncaoComparacao Comparacao, const void * arg){
    // Validade dos Argumentos
    if (Lista == NULL || Comparacao == NULL || arg == NULL)
        return ArgumentoInvalido;

    // Auxiliares
    NoLista * L, *LA;
    L = Lista->Primeiro;

    // Controlador de quantos elementos foram removidos
    int Quantidade = 0;
    // Percorre a lista
    while (L != NULL){
        // Se o elemento corresponder ao argumento
        if (Comparacao(L, arg)){
            // Incrementa no contador
            Quantidade++;
            // Se é o primeiro elemento, remove-o e torna o
            // próximo o primeiro
            if (L == Lista->Primeiro){
                Lista->Primeiro = L->Proximo;
                free(L);
                L = Lista->Primeiro;
                continue;
            }
            // Remove do meio ou do fim
            LA->Proximo = L->Proximo;
            free(L);
            L = L->Proximo;
            continue;
        }
        LA = L;
        L = L->Proximo;
    }
    return Quantidade;
}

NoLista * UltimoNo(NoLista *Raiz){
    // Percorre a Lista e retorna o último nó
    while (Raiz != NULL && Raiz->Proximo != NULL)
        Raiz = Raiz->Proximo;
    return Raiz;
}

NoLista *Particiona(NoLista *Primeiro, NoLista *Ultimo,
                       NoLista **NovoPrimeiro, NoLista **NovoUltimo, FuncaoComparacao Comparacao){

    // Auxiliares
    NoLista *Axial = Ultimo;
    NoLista *Anterior = NULL, *Raiz = Primeiro, *NoL = Axial;

    // Troca o primeiro e o último o máximo possível
    while (Raiz != Axial){
        // Se a Raiz é maior que o primeiro
        if (Comparacao(Raiz, Axial)){
            // Transforma o maior no Primeiro
            if ((*NovoPrimeiro) == NULL)
                (*NovoPrimeiro) = Raiz;

            Anterior = Raiz;
            Raiz = Raiz->Proximo;
        }
        else{
            // Ao próximo
            if (Anterior)
                Anterior->Proximo = Raiz->Proximo;
            NoLista *Auxiliar = Raiz->Proximo;
            Raiz->Proximo = NULL;
            NoL->Proximo = Raiz;
            NoL = Raiz;
            Raiz = Auxiliar;
        }
    }

    // Transforma a raiz em primeira caso seja a menor
    if ((*NovoPrimeiro) == NULL)
        (*NovoPrimeiro) = Axial;

    // Novo último nó
    (*NovoUltimo) = NoL;

    // Retorna a nova raiz
    return Axial;
}


NoLista *Recursao(NoLista *Primeiro, NoLista *Ultimo, FuncaoComparacao Comparacao){
    if (!Primeiro || Primeiro == Ultimo)
        return Primeiro;

    NoLista *NovoPrimeiro = NULL, *NovoUltimo = NULL;

    // Divide e Conquista
    NoLista *Axial = Particiona(Primeiro, Ultimo, &NovoPrimeiro, &NovoUltimo, Comparacao);

    // Caso a raiz já seja o menor, passa para o próximo caso
    if (NovoPrimeiro != Axial)
    {
        // Altera o nó anterior para apontar para NULL
        NoLista *Auxiliar = NovoPrimeiro;
        while (Auxiliar->Proximo != Axial)
            Auxiliar = Auxiliar->Proximo;
        Auxiliar->Proximo = NULL;

        NovoPrimeiro = Recursao(NovoPrimeiro, Auxiliar, (FuncaoComparacao) Comparacao);

        // Próximo nó se torna o esquerdo
        Auxiliar = UltimoNo(NovoPrimeiro);
        Auxiliar->Proximo =  Axial;
    }

    Axial->Proximo = Recursao(Axial->Proximo, NovoUltimo, (FuncaoComparacao) Comparacao);

    return NovoPrimeiro;
}

void Ordena(NoLista ** Primeiro, FuncaoComparacao Comparacao){
    // Chama a função que de fato ordena
    (*Primeiro) = Recursao(*Primeiro, UltimoNo(*Primeiro), (FuncaoComparacao) Comparacao);
    return;
}
