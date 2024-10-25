#ifndef FILA_H // Verifica se FILA_H não foi definido
#define FILA_H

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
Fila* fila_init();

//  Verificar se a fila está vazia
int fila_vazia(Fila *f);

//  Adicionar um novo elemento à fila
int fila_push(Fila *f, elem_fila *dado);

//  Remover e retornar o bloco do início da fila
FilaBloco *fila_pop(Fila *f);

//  Imprimir os elementos da fila
int fila_print(Fila *fila);

//  Verificar se um elemento está presente na fila
FilaBloco *fila_verifica_elem(Fila*f, elem_fila *dado);

//  Liberar a memória ocupada pela fila
int fila_libera(Fila *f);

//  Retornar o número total de elementos na fila
int fila_total(Fila *f);

//  Imprimir o dado de um bloco específico da fila
int fila_bloco_print(FilaBloco *filabloco);

#endif