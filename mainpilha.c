#include <stdio.h>
#include "pilha.h"

int main(){

Pilha *p = pilha_init();
float val1 = 100.1f;
float val2 = 250.5f;
float val3 = 300.6f;
float val4 = 500.7f;

float val5 = 500.7f;
char nome1[50] = "luiz";
char nome2[50] = "pedro";
char nome3[50] = "rita";
char nome4[50] = "joao";
char nome5[50] = "maria";

pilha_push(p, &val1, nome1);
pilha_push(p, &val2, nome2);
pilha_push(p, &val3, nome3);
printf("primeio print:\n");
pilha_print(p);
pilha_push(p, &val4, nome4);
printf("segundo print:\n");
pilha_print(p);
printf("o topo é:\n");
pilha_print_topo(p);
pilha_push(p, &val5, nome5);
printf("quarto print:\n");

pilha_print(p);


pilha_libera(p);

return 0;
}