#include "bloco.h"
#include "pilha.h"
#include "lista.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
//  Protótipos das funções
// void cadastra(/*lista de produtos, nome do produto);
// void lista_produtos(/*lista de produtos...(?));
// void dar_lance(/*lista de produtos...(?));
// void avisa_usuario(/*lista de produtos...(?));
// void encerra(/*lista de produtos...(?));

void cadastra_produto(Lista *Lista_Prod)
{
  printf("Entre com o nome do produto:");
  char nome[50];
  scanf("%s", nome);
  
  char *produto = malloc(strlen(nome) + 1);  
  if (produto == NULL) {
    printf("Erro ao alocar memória!\n");
    return;
  }
  strcpy(produto, nome);
  
  lista_push(Lista_Prod, produto, strlen(produto) + 1);
  printf("Produto cadastrado com sucesso!\n");
}

void dar_lance(Lista *Lista_Prod, char *nome, float valor, char *produto)
{
  ListaBloco *aux = Lista_Prod->inicio;
  while (aux != NULL)
  {
    if (strcmp(aux->bloco->dado, produto) == 0)
    {
      if (pilha_vazia(aux->pilha))
      {
        pilha_push(aux->pilha, &valor, sizeof(float), nome);
      }
      else
      {
        if (atof(aux->pilha->topo->bloco->dado) > valor)
        {
          printf("Seu lance pela %s não foi aceito. Você precisa dar um lance maior!", produto);
          return;
        }
        else if (atof(aux->pilha->topo->bloco->dado) == valor)
        {
          fila_push(aux->pilha->topo->fila, nome, strlen(nome) + 1);
        }
        else if(atof(aux->pilha->topo->bloco->dado) < valor)
        {
          pilha_push(aux->pilha, &valor, sizeof(float), nome);
        }
      }
      printf("Lance cadastrado com sucesso!\n");
      return;
    }
    aux = aux->proximo;
  }
  printf("Produto não encontrado\n");
}

int main()
{
  setlocale(LC_ALL, "");
  // Menu inicial
  printf("Caro usuário, suas opções são:\n\t1)  cadastrar um produto\n\t2)  listar produtos e lances\n\t3)  dar um lance\n\t4)  listar outros produtos para lances\n\t5)  encerrar leilão\n\n");

  int comando;

  Lista Lista_Prod;
  lista_init(&Lista_Prod);
  int cont_cadastros = 0;

  // Menu
  do
  {
    printf("O que deseja fazer? ");
    scanf("%d", &comando);
    switch (comando)
    {
    case 1: // cadastra um produto
      printf("Resposta: 1\n");
      cadastra_produto(&Lista_Prod);
      cont_cadastros++;
      printf("\n");
      break;

    case 2: // lista todos os produtos e os lances de cada um
      printf("Resposta: 2\n");
      if (cont_cadastros == 0)
      {
        printf("Não há produtos cadastrados\n");
      }
      else
      {
        lista_print(&Lista_Prod);
        printf("Listagem completa\n");
      }
      printf("\n");
      break;

    case 3: // dá um lance em um produto
      printf("Resposta: 3\n");
      // dar_lance();
      printf("Entre com seu nome:");
      char aux_nome[50];
      scanf("%s", aux_nome);

      printf("Entre com o valor do lance:");
      float aux_lance;
      scanf("%f", &aux_lance);

      printf("Entre com o nome do produto:");
      char aux_produto[50];
      scanf("%s", aux_produto);

      dar_lance(&Lista_Prod, aux_nome, aux_lance, aux_produto);
      printf("\n");
      break;

    case 4: // avisa usuários os quais tiveram lances ultrapassados sobre quais outros produtos estão disponíveis para lance
      printf("Resposta: 4\n");
      // avisa_usuario();
      printf("\n");
      break;

    case 5: // encerra leilão: lista os usuários e o lance ganhador para cada produto, além de reinicializar o sistema
      printf("Resposta: 5\n");
      // encerra();
      printf("\n");
      break;

    default:
      printf("Comando inválido\n");
      break;
    }
  } while (comando != 5);

  return 0;
}
