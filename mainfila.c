#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int main(){

    Fila *f = fila_init();
    bool deu_certo = fila_vazia(f);
    if (deu_certo == true){
        printf("fila inicializada\n");
    }else{
        printf("fila não inicializada\n");
    }

    fila_push(f,"luiz");
    fila_push(f,"luiza");
    fila_push(f,"luizao");
    
    fila_print(f);

    FilaBloco *ultimo_nome = fila_pop(f);
    printf("nome popado: %s\n", ultimo_nome->dado);

    fila_print(f);
    if (fila_verifica_elem(f, "ana")==true){
        printf("Ana está no lance\n");
    }
    if (fila_verifica_elem(f, "luizao")==true){
        printf("Luizao está no lance\n");
    }

    fila_libera(f);


return 0;
}