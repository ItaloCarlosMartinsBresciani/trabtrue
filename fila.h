#ifndef FILA_H // Verifica se FILA_H não foi definido
#define FILA_H

#include "erro.h"
#include <stdbool.h>

// Define o tipo elem_fila como char
typedef char elem_fila;

// Estrutura que representa um bloco (nó) da fila
typedef struct FilaBloco{
    struct FilaBloco *proximo; // Ponteiro para o próximo bloco da fila
    elem_fila *dado; // Ponteiro para os dados armazenados neste bloco
}FilaBloco;

// Estrutura da Fila
typedef struct{
    FilaBloco *inicio, *fim; // Ponteiros para o início e o fim da fila
    int total; // Total de elementos na fila
}Fila;

//  Inicializar uma nova fila e a retorna
Fila* fila_init(tipo_erro *erro);

//  Verificar se a fila está vazia
bool fila_vazia(Fila *f, tipo_erro *erro);

//  Adicionar um novo elemento à fila
void fila_push(Fila *f, elem_fila *dado, tipo_erro *erro);

//  Remover e retornar o bloco do início da fila
FilaBloco *fila_pop(Fila *f, tipo_erro *erro);

//  Imprimir os elementos da fila
void fila_print(Fila *fila, tipo_erro *erro);

//  Verificar se um elemento está presente na fila
FilaBloco *fila_verifica_elem(Fila*f, elem_fila *dado, tipo_erro *erro);

//  Liberar a memória ocupada pela fila
void fila_libera(Fila *f, tipo_erro *erro);

//  Retornar o número total de elementos na fila
int fila_total(Fila *f, tipo_erro *erro);

//  Imprimir o dado de um bloco específico da fila
void fila_bloco_print(FilaBloco *filabloco, tipo_erro *erro);

#endif