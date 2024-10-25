#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

/* Protótipos das funções */
void cadastra_produto(Lista *Lista_Prod);
void dar_lance(Lista *Lista_Prod, Fila *fila_usuario_geral);
void lista_produtos(Lista *Lista_Prod);
void avisa_usuario(Lista *Lista_Prod, Fila *fila_usuario_geral);
void encerra(Lista *Lista_Prod);
void libera_mem(Lista *Lista_Prod);

void avisa_usuario(Lista *Lista_Prod, Fila *fila_usuario_geral)
{
    //printf("erro0");
    
    // Verifique se as listas não são nulas
    if (Lista_Prod == NULL || fila_usuario_geral == NULL) {
        return; // Retorne se uma das listas for nula
    }
    
    //printf("erro1");
    FilaBloco *aux = fila_usuario_geral->inicio;
    
    // Verifique se a fila de usuários gerais está inicializada
    if (aux == NULL) {
        printf("Fila de usuários gerais está vazia.\n");
        return;
    }

    while (aux != NULL)
    {
        printf("erro2");
        ListaBloco *aux2 = Lista_Prod->inicio;
        
        // Verifique se a lista de produtos está inicializada
        if (aux2 == NULL) {
            printf("Lista de produtos está vazia.\n");
            return;
        }

        while (aux2 != NULL)
        {
            //printf("erro3");
            int count = 0;

            // Verifique se a fila de usuários no produto está inicializada
            if (aux2->fila_usu == NULL || aux2->fila_usu->inicio == NULL) {
                printf("Fila de usuários do produto %s está vazia ou não inicializada.\n", aux2->dado);
                aux2 = aux2->proximo;
                continue; // Pule para o próximo produto se a fila não estiver inicializada
            }

            FilaBloco *aux3 = aux2->fila_usu->inicio;

            while (aux3 != NULL)
            {
                //printf("erro4");

                // Verifique se os dados não são nulos antes de compará-los
                if (aux->dado == NULL || aux3->dado == NULL) {
                    printf("Dados nulos durante a comparação.\n");
                    break;
                }

                if (strcmp(aux->dado, aux3->dado) != 0)
                {
                    count++;
                }
                else
                {
                    // Encontrou uma correspondência, não precisa continuar
                    break;
                }

                aux3 = aux3->proximo;
            }

            //printf("erro5");

            // Verifique se aux3 não é nulo antes de usar
            if (aux3 != NULL && count == aux2->fila_usu->total)
            {
                printf("para %s: não gostaria de dar um lance pela %s?\n", aux->dado, aux2->dado);
            }

            //printf("erro6");
            aux2 = aux2->proximo;
        }

        //printf("erro7");
        aux = aux->proximo;
    }
}


void cadastra_produto(Lista *Lista_Prod)
{
  printf("Entre com o nome do produto: ");
  char nome[50];
  scanf("%s", nome);

  char *produto = malloc(strlen(nome) + 1);
  if (produto == NULL)
  {
    printf("Erro ao alocar memória!\n");
    return;
  }
  strcpy(produto, nome);

  lista_push(Lista_Prod, produto);
  printf("Produto cadastrado com sucesso!\n");
}

void dar_lance(Lista *Lista_Prod, Fila *fila_usuario_geral)
{
  printf("Entre com seu nome: ");
  char aux_nome[50];
  scanf("%s", aux_nome);
  fila_push(fila_usuario_geral, aux_nome);

  printf("Entre com o valor do lance: R$ ");
  float aux_lance;
  scanf("%f", &aux_lance);

  printf("Entre com o nome do produto: ");
  char aux_produto[50];
  scanf("%s", aux_produto);

  ListaBloco *lance = lista_verifica_elem(Lista_Prod, aux_produto);
  if (lance == NULL)
  {
    printf("Produto não encontrado\n");
  }
  else
  {

    // cadastrando o usuário na fila do produto do lance em questão
    if (lance->fila_usu != NULL)
    {                                    // se não tem fila ainda desse produto
      Fila *fila_usu_prod = fila_init(); // criar um fila de usuarios DO PRODUTO
      lance->fila_usu = fila_usu_prod;   // fazer o ponteiro da lista apontar para fila de usuarios

      if (fila_vazia(fila_usu_prod) == true)
      { // se a fila ta vazia, dar push no nome da pessoa na fila
        fila_push(fila_usu_prod, aux_nome);
      }
      else
      { // se não tiver vazia, verificar se o nome da pessoa já está na fila
        FilaBloco *no = fila_verifica_elem(fila_usu_prod, aux_nome);
        if (no == NULL)
        { // se não tiver na fila, dar um push
          fila_push(fila_usu_prod, aux_nome);
        }
      }
    }

    if (pilha_vazia(lance->pilha) == true)
    {
      pilha_push(lance->pilha, &aux_lance, aux_nome);
      printf("Lance cadastrado com sucesso!\n");
    }
    else
    {
      PilhaBloco *n = pilha_print_topo(lance->pilha);
      if (n->dado <= aux_lance)
      {
        pilha_push(lance->pilha, &aux_lance, aux_nome);
        printf("Lance cadastrado com sucesso!\n");
      }
      else
      {
        printf("Seu lance pelo produto %s não foi aceito. Você precisa dar um lance maior!\n", aux_produto);
      }
    }
  }

  printf("\n");
}

void lista_produtos(Lista *Lista_Prod)
{
  ListaBloco *aux_lista = Lista_Prod->inicio; //
  while (aux_lista != NULL)
  {
    printf("\t");
    lista_bloco_print(aux_lista); // printa o produto (bloco da lista de produtos)
    printf("\n");
    PilhaBloco *aux_pilha = pilha_print_topo(aux_lista->pilha);

    while (aux_pilha != NULL)
    {
      if (aux_pilha->fila->total > 1)
        printf("\t\t%d lances de R$", aux_pilha->fila->total);
      else
      {
        printf("\t\t%d lance de R$", aux_pilha->fila->total);
      }
      pilha_bloco_print(aux_pilha); // printa o valor do produto (elemento do bloco da pilha)
      printf(": ");
      FilaBloco *aux_fila = aux_pilha->fila->inicio;
      while (aux_fila != NULL)
      {
        fila_bloco_print(aux_fila); // printa o nome do usuario na fila
        if (aux_fila->proximo != NULL)
        {
          printf(", ");
        }
        aux_fila = aux_fila->proximo;
      }
      aux_pilha = aux_pilha->anterior;
      printf("\n");
    }
    aux_lista = aux_lista->proximo;
  }
}

void encerra(Lista *Lista_Prod)
{
  ListaBloco *aux = Lista_Prod->inicio;
  while (aux != NULL)
  {
    printf("\t%s: ", aux->dado);
    if (pilha_vazia(aux->pilha) == false)
    {
      PilhaBloco *n = pilha_print_topo(aux->pilha);
      FilaBloco *usuario = n->fila->inicio;

      printf("%s ", usuario->dado);
      printf("comprou por R$ %.2f\n", n->dado);
    }
    else
    {
      printf("Nenhum lance foi dado para esse produto.\n");
    }
    aux = aux->proximo;
  }
  printf("Leilão encerrado.\n");
}

void libera_mem(Lista *Lista_Prod)
{
  ListaBloco *l = Lista_Prod->inicio;
  while (l != NULL)
  {
    Pilha *p = l->pilha;
    PilhaBloco *t = pilha_print_topo(l->pilha);

    while (t != NULL)
    {
      Fila *f = t->fila;
      fila_libera(f);
      t = t->anterior;
    }
    pilha_libera(p);

    l = l->proximo;
  }
  lista_libera(Lista_Prod);
}

int main()
{
  setlocale(LC_ALL, "");
  printf("Caro usuário, suas opções são:\n\t1)  cadastrar um produto\n\t2)  listar produtos e lances\n\t3)  dar um lance\n\t4)  listar outros produtos para lances\n\t5)  encerrar leilão\n\n");

  int comando;
  int cont_cadastros = 0;

  Lista *Lista_Prod = lista_init();
  Fila *fila_usuario_geral = fila_init();
  do
  {
    printf("O que deseja fazer? ");
    int resultado = scanf("%d", &comando);

    // Se scanf não conseguiu ler um inteiro (resultado == 0), exibe erro
    if (resultado != 1) {
            printf("Comando inválido!\n");
            continue; // Volta para o começo do do while
        }

    switch (comando)
    {
    case 1: // cadastra um produto
      printf("Resposta: 1\n");
      cadastra_produto(Lista_Prod);
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
        lista_produtos(Lista_Prod);
        printf("Listagem completa\n");
      }
      printf("\n");
      break;

    case 3: // dá um lance em um produto
      printf("Resposta: 3\n");
      dar_lance(Lista_Prod, fila_usuario_geral);
      printf("\n");
      break;

    case 4: // avisa usuários os quais tiveram lances ultrapassados sobre quais outros produtos estão disponíveis para lance
      printf("Resposta: 4\n");
      avisa_usuario(Lista_Prod, fila_usuario_geral);
      printf("\n");
      break;

    case 5: // encerra leilão: lista os usuários e o lance ganhador para cada produto, além de reinicializar o sistema
      printf("Resposta: 5\n");
      encerra(Lista_Prod);
      printf("\n");
      break;

    default:
      printf("Comando inválido\n");
      break;
    }
  } while (comando != 5);

  libera_mem(Lista_Prod);
  fila_libera(fila_usuario_geral);

  return 0;
}
