#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "erro.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

/* Protótipos das funções */
void cadastra_produto(Lista *Lista_Prod, tipo_erro *erro);
void dar_lance(Lista *Lista_Prod, Fila *fila_usuario_geral, tipo_erro *erro);
void lista_produtos(Lista *Lista_Prod, tipo_erro *erro);
void avisa_usuario(Lista *Lista_Prod, Fila *fila_usuario_geral);
void encerra(Lista *Lista_Prod, tipo_erro *erro);
void libera_mem(Lista *Lista_Prod, tipo_erro *erro);

void avisa_usuario(Lista *Lista_Prod, Fila *fila_usuario_geral) // Essa função vai percorrer a lista de todos os usuários
{                                                               // Para percorrer todos os produtos para percorrer a lista de usuários do produto
  // Se encontra vai pro proximo
  // Verifique se as listas não são nulas
  if (Lista_Prod == NULL || fila_usuario_geral == NULL)
  {
    return; // Retorne se uma das listas for nulaf
  }

  FilaBloco *aux = fila_usuario_geral->inicio;

  while (aux != NULL)
  {
    ListaBloco *aux2 = Lista_Prod->inicio;
    // Verifique se a lista de produtos está inicializada
    if (aux2 == NULL)
    {
      printf("Lista de produtos está vazia.\n");
      return;
    }
    while (aux2 != NULL)
    {
      int count = 0;

      FilaBloco *aux3 = aux2->fila_usu->inicio;
      while (aux3 != NULL)
      {
        // Verifique se os dados não são nulos antes de compará-los
        if (aux->dado == NULL || aux3->dado == NULL)
        {
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
      // Verifica se aux3 não é nulo antes de usar
      if (count == aux2->fila_usu->total)
      {
        printf("para %s: não gostaria de dar um lance pelo produto %s?\n", aux->dado, aux2->dado);
      }
      aux2 = aux2->proximo;
    }
    aux = aux->proximo;
  }
}

void cadastra_produto(Lista *Lista_Prod, tipo_erro *erro) //  Apenas cadastra o produto
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

  lista_push(Lista_Prod, produto, erro); // ok
  if (*erro == SUCESSO)
  {
    printf("Produto cadastrado com sucesso!\n");
  }
  else if (*erro == ERRO_ELEM_REPETIDO)
  {
    printf("Produto já cadastrado! Tente outra vez.\n");
  }
  else
  {
    printf("Erro ao inserir elemento na lista");
  }
}

void dar_lance(Lista *Lista_Prod, Fila *fila_usuario_geral, tipo_erro *erro) // Função para receber e registrar um lance, além de adicionar os usuários
                                                                             // do lance para a lista de usuários
{
  printf("Entre com seu nome: ");
  char aux_nome[50];
  scanf(" %s", aux_nome);
  fila_push(fila_usuario_geral, aux_nome, erro);

  printf("Entre com o valor do lance: R$ ");
  float aux_lance;
  scanf(" %f", &aux_lance);

  printf("Entre com o nome do produto: ");
  char aux_produto[50];
  scanf(" %s", aux_produto);

  ListaBloco *lance = lista_verifica_elem(Lista_Prod, aux_produto, erro);
  if (*erro != SUCESSO)
  {
    // ERRO TRATADO
    printf("Erro ao verificar se o elemento está na lista\n");
    return;
  }
  if (lance == NULL)
  {
    printf("Produto não encontrado\n");
  }
  else
  {
    if (lance->fila_usu == NULL)
    {
      // printf("Fila de usuários do produto não inicializada");
      *erro = ERRO_NULL; // Tentativa de acesso a um ponteiro nulo
      return;
    }

    if (lance->fila_usu->inicio == NULL) // se a fila de usuários do produto do lance está vazia
    {
      fila_push(lance->fila_usu, aux_nome, erro);
      if (*erro != SUCESSO)
      { // ERRO TRATADO;
        printf("Erro ao inserir usuário.\n");
        return;
      }
    }
    else
    {
      FilaBloco *aux = fila_verifica_elem(lance->fila_usu, aux_nome, erro);
      if (*erro != SUCESSO)
      { // ERRO TRATADO
        printf("Erro ao inserir usuário.\n");
      }
      if (aux == NULL)
      { // é o primeiro lance do usuário no produto
        fila_push(lance->fila_usu, aux_nome, erro);
        if (*erro != SUCESSO)
        { // ERRO TRATATADO
          printf("Erro ao inserir usuário.\n");
          return;
        }
      }
    }

    if (pilha_vazia(lance->pilha, erro) == true)
    {
      if (*erro != SUCESSO)
      { // ERRO TRATADO
        printf("Erro ao verificar se não há lances.\n");
        return;
      }
      pilha_push(lance->pilha, &aux_lance, aux_nome, erro);
      if (*erro != SUCESSO)
      { // ERRO TRATADO
        printf("Erro ao inserir um lance.\n");
        return;
      }
      printf("Lance cadastrado com sucesso!");
    }
    else
    {
      PilhaBloco *n = pilha_print_topo(lance->pilha, erro); // precisa verificar
      if (*erro != SUCESSO)
      { // ERRO TRATADO;
        printf("Erro ao acessar lance.\n");
        return;
      }
      if (n->dado < aux_lance) // verifica se o usuário está dando um lance novo e maior
      {
        pilha_push(lance->pilha, &aux_lance, aux_nome, erro);
        if (*erro != SUCESSO)
        { // ERRO TRATADO
          printf("Erro ao inserir um lance.\n");
          return;
        }
        printf("Lance cadastrado com sucesso!\n");
      } // a lógica de verificação se o usuário deu lance repetido:
      else if ((n->dado == aux_lance) && (strcmp(n->fila->inicio->dado, aux_nome) == 0)) // verifica se o usuário está dando um lance repetido (lance igual ao maior, o qual ele mesmo deu)
      {
        printf("Você já deu um lance de %.2f pelo produto %s.\n", aux_lance, aux_produto);
      }
      else if ((n->dado == aux_lance))
      { // verifica se o usuário está dando um lance igual ao valor do maior lance
        pilha_push(lance->pilha, &aux_lance, aux_nome, erro);
        if (*erro != SUCESSO)
        { // ERRO TRATADO
          printf("Erro ao inserir um lance.\n");
          return;
        }
        printf("Lance cadastrado com sucesso!\n");
      }
      else // o usuário está dando um lance menor que o lance maior
      {
        printf("Seu lance pelo produto %s não foi aceito. Você precisa dar um lance maior!\n", aux_produto);
      }
    }
  }

  printf("\n");
}

void lista_produtos(Lista *Lista_Prod, tipo_erro *erro) // Esta função vai mostrar os produtos com seus respectivos lances (mostrando nome e valor dos lances)
{
  ListaBloco *aux_lista = Lista_Prod->inicio; // fazendo um ponteiro auxiliar apontar para o bloco do início da lista de produtos
  while (aux_lista != NULL)
  {
    printf("\t");
    lista_bloco_print(aux_lista, erro); // printa o produto (bloco da lista de produtos)
    if (*erro != SUCESSO)
    { // ERRO TRATADO
      printf("Erro ao imprimir produto.\n");
      return; // sai da função porque há problemas com a lista de produtos
    }
    printf("\n");
    PilhaBloco *aux_pilha = pilha_print_topo(aux_lista->pilha, erro);
    if (*erro != SUCESSO)
    { // ERRO TRATADO
      printf("Erro ao acessar lance.\n");
      return; // sai da função porque há problemas com a pilha de lances de um produto
    }

    while (aux_pilha != NULL)
    {
      if (aux_pilha->fila->total > 1)
        printf("\t\t%d lances de R$", aux_pilha->fila->total);
      else
      {
        printf("\t\t%d lance de R$", aux_pilha->fila->total);
      }
      pilha_bloco_print(aux_pilha, erro); // printa o valor do produto (elemento do bloco da pilha)
      if (*erro != SUCESSO)
      { // ERRO TRATADO
        printf("Erro ao acessar lance.\n");
        return; // sai da função porque há problemas com a pilha de lances de um produto
      }
      printf(": ");
      FilaBloco *aux_fila = aux_pilha->fila->inicio;
      while (aux_fila != NULL)
      {
        fila_bloco_print(aux_fila, erro); // printa o nome do usuario na fila
        if (*erro != SUCESSO)
        { // ERRO TRATADO
          printf("Erro ao acessar usuário.\n");
          return; // sai da função porque há problemas com a fila de usuarios do produto
        }
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

void encerra(Lista *Lista_Prod, tipo_erro *erro) // Função para encerrrar o leilão, mostrando os usuários que deram o lance no topo da pilha
{
  ListaBloco *aux = Lista_Prod->inicio;
  while (aux != NULL)
  {
    printf("\t%s: ", aux->dado);
    if (pilha_vazia(aux->pilha, erro) == false)
    {
      if (*erro != SUCESSO)
      {                                               // ERRO TRATADO
        printf("Erro ao acessar pilha de lances.\n"); // há algo errado com a estrutura de pilha de lances
        return;
      }
      PilhaBloco *n = pilha_print_topo(aux->pilha, erro);
      if (*erro != SUCESSO)
      {                                               // ERRO TRATADO
        printf("Erro ao acessar pilha de lances.\n"); // há algo errado com a estrutura de pilha de lances
        return;
      }
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
  return;
}

void libera_mem(Lista *Lista_Prod, tipo_erro *erro) // Função para liberar a meméria da lista de produtos cadastrados (e as estruturas ligadas a ela)
{
  ListaBloco *l = Lista_Prod->inicio;
  while (l != NULL)
  {
    Pilha *p = l->pilha;
    PilhaBloco *t = p->topo;
    if (*erro != SUCESSO)
    {
      printf("Erro ao acessar pilha de lances ao liberar memória\n");
      return;
    }

    while (t != NULL)
    { // liberandos as filas dos blocos das pilhas
      Fila *f = t->fila;
      fila_libera(f, erro); 
      if (*erro != SUCESSO)
      {
        printf("Erro ao acessar lista de usuários de um lance na liberação de memória\n");
        return;
      }

      t = t->anterior;
    }
    pilha_libera(p, erro);
    if (*erro != SUCESSO)
    {
      printf("Erro ao acessar lances na liberação de memória\n");
      return;
    }

    l = l->proximo;
  }
  lista_libera(Lista_Prod, erro);
  if (*erro != SUCESSO)
  {
    printf("Erro ao acessar lista de produtos na liberação de memória\n");
    return;
  }
}

int main() // Função principal, onde é exibida as opções de manipulação do Leilão
{
  setlocale(LC_ALL, "");
  printf("Caro usuário, suas opções são:\n\t1)  cadastrar um produto\n\t2)  listar produtos e lances\n\t3)  dar um lance\n\t4)  listar outros produtos para lances\n\t5)  encerrar leilão\n\t6)  sair do programa\n\n");
  tipo_erro erro = SUCESSO; // variável controladora de erros
  int comando;
  int cont_cadastros = 0;

  Lista *Lista_Prod = lista_init(&erro);
  if (erro != SUCESSO)
  {
    printf("Erro ao inicializar a lista");
  }
  Fila *fila_usuario_geral = fila_init(&erro);

  do
  {
    printf("O que deseja fazer? ");
    int resultado = scanf("%d", &comando);
    // Se scanf não conseguiu ler um inteiro (resultado == 0), exibe erro
    if (resultado != 1)
    {
      printf("Comando inválido!\n");
      printf("\n");
      while (getchar() != '\n');       // Remove qualquer caractere extra deixado no buffer
      continue; // Volta para o começo do do while
    }

    switch (comando)
    {
    case 1: // cadastra um produto
      printf("Resposta: 1\n");
      cadastra_produto(Lista_Prod, &erro);
      // Possíveis erros na cadastra_produto foram tratados na própria função
      cont_cadastros++;
      printf("\n");
      break;

    case 2: // lista todos os produtos e os lances de cada um
      printf("Resposta: 2\n");
      if (cont_cadastros == 0)
      {
        printf("Não há produtos cadastrados no leilão.\n");
      }
      else
      {
        if(Lista_Prod->inicio == NULL){
          printf("Não há produtos cadastrados no leilão.\n");
          break;
        }
        lista_produtos(Lista_Prod, &erro);
        // Possíveis erros na lista_produtos foram tratados na própria função
        printf("Listagem completa\n");
      }
      printf("\n");
      break;

    case 3: // dá um lance em um produto
      printf("Resposta: 3\n");
      dar_lance(Lista_Prod, fila_usuario_geral, &erro);
      // Possíveis erros na dar_lance foram tratados na própria função
      printf("\n");
      break;

    case 4: // avisa usuários os quais tiveram lances ultrapassados sobre quais outros produtos estão disponíveis para lance
      printf("Resposta: 4\n");
      avisa_usuario(Lista_Prod, fila_usuario_geral);
      printf("\n");
      break;

    case 5: // encerra leilão: lista os usuários e o lance ganhador para cada produto, além de reinicializar o sistema
      printf("Resposta: 5\n");
      encerra(Lista_Prod, &erro);
      
      fila_libera(fila_usuario_geral, &erro);
      
      libera_mem(Lista_Prod, &erro);
      
      if (erro != SUCESSO)
      {
        printf("Erro ao liberar memória para a fila de usuários do lance.\n");
      }
      // Inicializando novamente para possíveis leilões seguintes
      Lista_Prod = lista_init(&erro);
      if (erro != SUCESSO)
      {
        printf("Erro ao inicializar a lista.\n");
      }
      fila_usuario_geral = fila_init(&erro);
      
      cont_cadastros = 0;
      // Possíveis erros na encerra foram tratados na própria função
      printf("\n");
      break;

    case 6:
      printf("Resposta: 6\n");
      printf("Encerrando o programa...\n");
      break;

    default:
      printf("Comando inválido\n");
      break;
    }
  } while (comando != 6);


  libera_mem(Lista_Prod, &erro);
  fila_libera(fila_usuario_geral, &erro);
  if(erro != SUCESSO){
    printf("Erro ao liberar memória para a fila de usuários do lance\n");
  }

  return 0;
}
