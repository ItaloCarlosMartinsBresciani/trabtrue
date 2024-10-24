#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main(){

Pilha *p = pilha_init();
float val1 = 100.1;
float val2 = 250.5;
float val3 = 300.6;
float val4 = 500.7;
float val5 = 500.7;
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
PilhaBloco *topo = pilha_print_topo(p);
printf("%f\n", topo->dado);
pilha_push(p, &val5, nome5);
printf("quarto print:\n");

pilha_print(p);


pilha_libera(p);

return 0;
}