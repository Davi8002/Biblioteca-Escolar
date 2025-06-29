#ifndef OLDCARE_H
#define OLDCARE_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//////////////////////////
typedef struct {
  char nome[50];
  int isbn;
  char autor[50];
  char sinopse[250];
  char genero[50];
  int paginas;
  bool emprestimo;

} Livro;
int quantidadeLivro = 0;
Livro livro[20];//defino quantidade de livros
//////////////////////////
typedef struct {
  char nome[50];
  int idade;
  int matricula;
} Aluno;
Aluno alunos[50];// defino quantidade de alunos
int quantidadeAlunos = 0;
//////////////////////////
int escolha;
//////////////////////////
void registroLivro(int i) {
  system("clear"); // alterar dps se for usar no windows
  printf("Digite o Nome do Livro!\n");
  fgets(livro[i].nome, 50, stdin);
//fgets(nomedavariavel, tamanhodotexto, stdin)
  livro[i].nome[strcspn(livro[i].nome, "\n")] = '\0';
  printf("Digite o ISBN do Livro!\n");
  scanf("%d", &livro[i].isbn);
  // scanf("texto e %x", nomedavariavel)
  getchar();
  // limpa o buffercom o \n pra o proximo fgets nao pegar ele

  printf("Digite o Autor do Livro!\n");
  fgets(livro[i].autor, 50, stdin);
  livro[i].autor[strcspn(livro[i].autor, "\n")] = '\0';
  // verifica onde ta com o espaço e depois troca pelo fim da string

  printf("Digite a Sinopse do Livro!\n");
  fgets(livro[i].sinopse, 250, stdin);
  livro[i].sinopse[strcspn(livro[i].sinopse, "\n")] = '\0';

  printf("Digite o Gênero do Livro!\n");
  fgets(livro[i].genero, 50, stdin);
  livro[i].genero[strcspn(livro[i].genero, "\n")] = '\0';

  printf("Digite a Quantidade de Paginas do Livro!\n");
  scanf("%d", &livro[i].paginas);
  getchar();
  // fflush(stdin);
  livro[i].emprestimo = false;
  system("clear"); // alterar dps se for usar no windows

  printf("\n--- Livro Cadastrado ---\n");
  printf("Nome: %s\n", livro[i].nome);
  printf("ID: %d\n", livro[i].isbn);
  printf("Autor: %s\n", livro[i].autor);
  printf("Sinopse: %s\n", livro[i].sinopse);
  printf("Gênero: %s\n", livro[i].genero);
  printf("Páginas: %d\n", livro[i].paginas);
  printf("Slot Usado: %d\n", i);
  quantidadeLivro++;
  return;
};

void registroAluno() {
  system("clear"); // alterar dps se for usar no windows
  int quantidade, i;

  printf("Quantos alunos deseja cadastrar? ");
  scanf("%d", &quantidade);
  getchar(); // limpa o \n

  for (i = 0; i < quantidade; i++) {
    printf("\nAluno %d:\n", i + 1);

    printf("Nome: ");
    fgets(alunos[quantidadeAlunos].nome, 50, stdin);
    alunos[quantidadeAlunos]
        .nome[strcspn(alunos[quantidadeAlunos].nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &alunos[quantidadeAlunos].idade);
    getchar();

    printf("Matrícula: ");
    scanf("%d", &alunos[quantidadeAlunos].matricula);
    getchar();

    quantidadeAlunos++;
  }
  system("clear"); // alterar dps se for usar no windows
  printf("\n=== Alunos Cadastrados ===\n");
  for (i = 0; i < quantidadeAlunos; i++) {
    printf("\nAluno %d:\n", i + 1);
    printf("Nome: %s\n", alunos[i].nome);
    printf("Idade: %d\n", alunos[i].idade);
    printf("Matrícula: %d\n", alunos[i].matricula);
    printf("Id: %d\n\n", i);
  }
}

void mensagem(int i) {
  switch (i) {
  case 1:
    // Menu de opções
    printf("\nEscolha uma opção: ");
    printf("\n\n1 - Cadastrar Livro\n");
    printf("2 - Cadastrar Usuário\n");
    printf("3 - Fazer Empréstimo\n");
    printf("4 - Renovar Empréstimo\n");
    printf("5 - Devolução de Livro\n");
    printf("6 - Pesquisa de Livro\n");
    printf("\nOpção: ");
    break;

  case 2:

    break;
  }
}

void processo() {
  mensagem(1);
  scanf("%d", &escolha);
  getchar();
  switch (escolha) {
  case 1:
    registroLivro(quantidadeLivro);
    break;
  case 2:
    registroAluno();
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  }
  processo();
}

#endif
