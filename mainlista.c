#include <stdio.h>
#include "lista.h"

int main(){

Lista *l = lista_init();
lista_push(l,"banana");
lista_push(l,"alface");
lista_push(l,"caramelo");
lista_print(l);
lista_push(l,"amora");
lista_pop(l);
lista_print(l);
lista_libera(l);



return 0;
}