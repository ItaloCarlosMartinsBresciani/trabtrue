#include <stdio.h>
#include "fila.h"
#include "bloco.h"
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

void fila_init(Fila *fila){
    fila->inicio=NULL;
    fila->fim=NULL;
    fila->total=0;
}

int fila_vazia(Fila *fila){
    if (fila->total==0)
        return 1;
    return 0;
}
void fila_push(Fila *fila, void *dado, unsigned long tamanho) {

    Bloco *bloco = bloco_alocar(dado, tamanho);
    assert(bloco!=NULL);
    FilaBloco *fila_bloco=malloc(sizeof(FilaBloco));
    assert(fila_bloco!=NULL);
    fila_bloco->bloco=bloco;
        
    if (fila_vazia(fila)) {
        fila->inicio = fila_bloco;
    } else {
        fila->fim->proximo = fila_bloco;
    }

    fila->fim = fila_bloco;
    fila->fim->proximo = NULL;
    fila->total++;
    
    
}

FilaBloco *fila_pop(Fila *fila) {

    if (!fila_vazia(fila)){
        FilaBloco *aux = fila->inicio;
        if (fila->inicio == fila->fim){
            fila->inicio = NULL;
            fila->fim = NULL;
        }else{
            fila->inicio = fila->inicio->proximo;
        }
        return aux;
    } 
}
void fila_print(Fila *fila){
    if (!fila_vazia(fila)){
        FilaBloco *aux=fila->inicio;
        while (aux!=NULL){
        printf("%s\n", aux->bloco->dado);
        aux=aux->proximo;
        }
    }
}
// int empty(Fila *fila) { 
//     if (!isempty(fila)) {
//         while (!isempty(fila)) {
//             Bloco *bloco;
//             remover(fila, bloco);  
//         }
//         fila->inicio = NULL;
//         fila->fim = NULL;
//         fila->total = 0;
//         return 1;  
//     }
//     return 0;  
// }
