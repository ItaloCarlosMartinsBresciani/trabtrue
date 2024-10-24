#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main(){

Lista *l = lista_init();
lista_push(l,"alface");
lista_push(l,"caramelo");
lista_print(l);
lista_push(l,"amora");
lista_pop(l);
lista_print(l);
ListaBloco *l1 = lista_verifica_elem(l,"banana");
if (l1!=NULL){
    printf("Achou\n");
    printf("%s\n",l1->dado);
}
lista_libera(l);




return 0;
}