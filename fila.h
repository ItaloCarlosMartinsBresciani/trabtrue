#ifndef FILA_H
#define FILA_H

typedef char elem;
typedef struct FilaBloco{
    struct FilaBloco *proximo; 
    elem *dado;
}FilaBloco;

typedef struct{
    FilaBloco *inicio, *fim; 
    int total;
}Fila;

Fila* fila_init();
int fila_vazia(Fila *f);
void fila_push(Fila *f, elem *dado);
FilaBloco *fila_pop(Fila *f);
void fila_print(Fila *fila);
//int fila_verifica_elem(Fila*f, elem*dado);
void fila_libera(Fila *f);


#endif