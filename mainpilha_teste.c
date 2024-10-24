#include <stdio.h>
#include "pilha.h"

int main(){

Pilha *p = pilha_init();
float val1 = 100.1f;
float val2 = 250.5f;
float val3 = 300.6f;
float val4 = 200.7f;
pilha_push(p, &val1);
pilha_push(p, &val2);
pilha_push(p, &val3);
printf("primeio print:\n");
pilha_print(p);
pilha_push(p, &val4);
printf("segundo print:\n");
pilha_print(p);
printf("o topo é:\n");
pilha_print_topo(p);
pilha_pop(p);
printf("terceio print:\n");
pilha_print(p);
pilha_libera(p);

return 0;
}