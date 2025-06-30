#ifndef OLDCARE_H
#define OLDCARE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
Livro livro[20]; // defino quantidade de livros
//////////////////////////
typedef struct {
  char nome[50];
  int idade;
  int matricula;
} Aluno;
Aluno alunos[50]; // defino quantidade de alunos
int quantidadeAlunos = 0;
//////////////////////////
typedef struct {
  int matriculaAluno;
  int isbnLivro;
  char dataEmprestimo[11];
  char dataDevolucaoPrevista[11];
  char dataDevolucaoReal[11];
  bool ativo;
} Emprestimo;
Emprestimo emprestimos[50];
int quantidadeEmprestimos = 0;
//////////////////////////

int escolha;
//////////////////////////
void registroLivro(int i) {
  system("clear"); // alterar dps se for usar no windows
  printf("Digite o Nome do Livro!\n");
  fgets(livro[i].nome, 50, stdin);
  // fgets(nomedavariavel, tamanhodotexto, stdin)
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
  printf("ISBN: %d\n", livro[i].isbn);
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
  if (quantidade > 50 - quantidadeAlunos) {
    quantidade = 1;
  }
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
    printf("Slot: %d\n\n", i);
  }
}

void emprestarLivro() {
  int isbn, matricula;
  system("clear");

  printf("=== Empréstimo de Livro ===\n");

  printf("Digite o ISBN do Livro: ");
  scanf("%d", &isbn);
  getchar();

  int indiceLivro = -1;
  for (int i = 0; i < quantidadeLivro; i++) {
    if (livro[i].isbn == isbn) {
      indiceLivro = i;
      break;
    }
  } // pra tipo verificar se tem realmetne um com esse isbn

  if (indiceLivro == -1) {
    printf("Livro com ISBN %d não encontrado!\n", isbn);
    return;
  }

  if (livro[indiceLivro].emprestimo) {
    printf("Este livro já está emprestado!\n");
    return;
  }

  printf("Digite a matrícula do Aluno: ");
  scanf("%d", &matricula);
  getchar();

  int indiceAluno = -1;
  for (int i = 0; i < quantidadeAlunos; i++) {
    if (alunos[i].matricula == matricula) {
      indiceAluno = i;
      break;
    }
  } // verificar agora se tem um aluno

  if (indiceAluno == -1) {
    printf("Aluno com matrícula %d não encontrado!\n", matricula);
    return;
  }

  // marca o livro como emprestado usando o indice que foi procurado pelo isbn
  livro[indiceLivro].emprestimo = true;

  // preenche o struct do emprestimo com os dados do aluno e do livro tipo em
  // sql com chave estrnageira
  emprestimos[quantidadeEmprestimos].matriculaAluno = matricula;
  emprestimos[quantidadeEmprestimos].isbnLivro = isbn;
  emprestimos[quantidadeEmprestimos].ativo = true;

  // salva a data que foi feita com esse comando louco igual a função mas to com
  // pregiça de mudar pra usar a função
  time_t t = time(NULL);
  struct tm dataAtual = *localtime(&t);
  strftime(emprestimos[quantidadeEmprestimos].dataEmprestimo, 11, "%d/%m/%Y",
           &dataAtual);

  // pega o dia que o emprestimo foi feito e acrescente mais 7 dias
  dataAtual.tm_mday += 7;
  mktime(&dataAtual); // faz com que se apos a soma fique tipo dia 37 de junho
                      // ai pula o mes pra ficar certinho e ficar no dia tipo 7
                      // de julho
  strftime(emprestimos[quantidadeEmprestimos].dataDevolucaoPrevista, 11,
           "%d/%m/%Y", &dataAtual);

  // inicia pra nao ficar com lixo
  strcpy(emprestimos[quantidadeEmprestimos].dataDevolucaoReal, "-");

  // mostra confirmação
  printf("\nLivro '%s' emprestado com sucesso para %s (matrícula: %d)!\n",
         livro[indiceLivro].nome, alunos[indiceAluno].nome,
         alunos[indiceAluno].matricula);

  printf("Data do Empréstimo: %s\n",
         emprestimos[quantidadeEmprestimos].dataEmprestimo);
  printf("Devolver até: %s\n",
         emprestimos[quantidadeEmprestimos].dataDevolucaoPrevista);

  quantidadeEmprestimos++;
}

void obterDataAtual(char *dataStr) {
  time_t t = time(NULL); // criei a variavel t no formato time_h estilo data
                         // 29/03/2025 mas so armazenou em segundos
  struct tm dataAtual = *localtime(
      &t); // dividiu em um struct proprio do c que deixa ficar com o 29/03/2025
  strftime(dataStr, 11, "%d/%m/%Y",
           &dataAtual); // por ultimo deixou nesse formato
}

int compararDatas(const char *data1, const char *data2) {
  int dia1, mes1, ano1;
  int dia2, mes2, ano2;
  sscanf(data1, "%2d/%2d/%4d", &dia1, &mes1, &ano1);
  sscanf(data2, "%2d/%2d/%4d", &dia2, &mes2, &ano2);

  if (ano1 != ano2)
    return ano1 - ano2;
  if (mes1 != mes2)
    return mes1 - mes2;
  return dia1 - dia2;
}

void devolucaoLivros() {
  system("clear");

  // cria as variáveis
  int matriculaAluno;
  char isbnLivroStr[20];
  char dataHoje[11];
  int estadoLivro;

  printf("===============================\n");
  printf("     Devolução de Livros       \n");
  printf("===============================\n\n");

  printf("Para qual matrícula de aluno o livro foi emprestado? ");
  scanf("%d", &matriculaAluno);
  getchar();

  printf("Qual o ISBN do livro a ser devolvido? ");
  fgets(isbnLivroStr, sizeof(isbnLivroStr), stdin); // pega o isbn ne
  isbnLivroStr[strcspn(isbnLivroStr, "\n")] = '\0'; // faz a limpeza do \n

  int isbnLivroInt = atoi(
      isbnLivroStr); // basicamente pega a string do fgets e transforma em int

  // cria os indices pra comparar
  int indiceEmprestimo = -1;
  int indiceLivroAssociado = -1;
  int indiceAlunoAssociado = -1;

  // procura o emprestimo igual ao isbn e matricula
  for (int i = 0; i < quantidadeEmprestimos; i++) {
    if (emprestimos[i].ativo &&
        emprestimos[i].matriculaAluno == matriculaAluno &&
        emprestimos[i].isbnLivro == isbnLivroInt) {

      indiceEmprestimo = i;

      // encontra o indice do livro e do aluno ligados
      for (int j = 0; j < quantidadeLivro; j++) {
        if (livro[j].isbn == isbnLivroInt) {
          indiceLivroAssociado = j;
          break;
        }
      }

      for (int k = 0; k < quantidadeAlunos; k++) {
        if (alunos[k].matricula == matriculaAluno) {
          indiceAlunoAssociado = k;
          break;
        }
      }
      break; // sai do loop principal de empréstimos
    }
  }

  // verifica se todos os indices foram encontrados
  if (indiceEmprestimo == -1 || indiceLivroAssociado == -1 ||
      indiceAlunoAssociado == -1) {
    system("clear"); // Limpa a tela antes de mostrar a mensagem de erro
    printf(
        "\nEmpréstimo ativo para o aluno %d e livro ISBN %s não encontrado.\n",
        matriculaAluno, isbnLivroStr);
    printf("Verifique a matrícula, o ISBN ou se o livro já foi devolvido.\n");
    printf("Pressione Enter para continuar...");
    getchar();
    return;
  }

  // pega a data atual do sistema para registrar a devolução
  obterDataAtual(dataHoje);

  // compara a data de hoje com a data de devolução prevista
  int comparacaoDatas = compararDatas(
      dataHoje, emprestimos[indiceEmprestimo].dataDevolucaoPrevista);

  // usa o nome do aluno associado encontrado
  char nomeAluno[50];
  strcpy(nomeAluno, alunos[indiceAlunoAssociado].nome);

  system("clear"); // limpa a tela antes de mostrar o status do prazo
  if (comparacaoDatas <= 0) {
    printf("\nO livro '%s' está dentro do prazo de devolução!\n",
           livro[indiceLivroAssociado].nome);
  } else {
    printf("\nATENÇÃO: O livro '%s' está FORA do prazo de devolução (previsto "
           "para: %s)!\n",
           livro[indiceLivroAssociado].nome,
           emprestimos[indiceEmprestimo].dataDevolucaoPrevista);
    printf("O aluno %s (matrícula: %d) pode estar sujeito a multa.\n",
           nomeAluno, matriculaAluno);
  }

  printf("\nDigite [1] se o livro estiver em bom estado.\n");
  printf("Digite [2] se o livro estiver em mau estado.\n");
  scanf("%d", &estadoLivro);
  getchar(); // limpa o buffer

  system("clear"); // limpa a tela antes de mostrar a confirmação final
  if (estadoLivro == 1) {
    printf("\n------------------------------------------------\n");
    printf("O livro '%s' foi devolvido em bom estado.\n",
           livro[indiceLivroAssociado].nome);
    printf("Obrigado por devolver o livro, %s!\n", nomeAluno);
    printf("Volte sempre!\n");
  } else if (estadoLivro == 2) {
    printf("\n------------------------------------------------\n");
    printf("O livro '%s' foi devolvido em mau estado.\n",
           livro[indiceLivroAssociado].nome);
    printf("O aluno %s (matrícula: %d) deverá pagar uma multa de 20%% do valor "
           "total do livro.\n",
           nomeAluno, matriculaAluno);
  } else {
    printf("\n------------------------------------------------\n");
    printf("Opção inválida para o estado do livro. Devolução registrada, mas o "
           "estado não foi validado.\n");
  }

  // --- Ações de Finalização da Devolução ---
  strcpy(emprestimos[indiceEmprestimo].dataDevolucaoReal,
         dataHoje); // strcpy serve meio que pra copiar o valor de uma strng pra
                    // outra
  emprestimos[indiceEmprestimo].ativo = false;
  livro[indiceLivroAssociado].emprestimo = false;

  printf("\nDevolução registrada com sucesso!\n");
  printf("Pressione Enter para continuar...");
  getchar();
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
    printf("7 - Listar Tudo\n");
    printf("\nOpção: ");
    break;

  case 2:

    break;
  }
}

void renovarEmprestimo() {
  system("clear");
  int matriculaAluno, isbnLivro;

  printf("=========== Renovação de Empréstimo ===========\n\n");

  printf("Digite sua matrícula: ");
  scanf("%d", &matriculaAluno);
  getchar();

  printf("Digite o ISBN do livro que deseja renovar: ");
  scanf("%d", &isbnLivro);
  getchar();

  int indiceEmprestimo = -1;
  for (int i = 0; i < quantidadeEmprestimos; i++) {
    if (emprestimos[i].ativo &&
        emprestimos[i].matriculaAluno == matriculaAluno &&
        emprestimos[i].isbnLivro == isbnLivro) {
      indiceEmprestimo = i;
      break;
    }
  }

  if (indiceEmprestimo == -1) {
    system("clear");
    printf("Nenhum empréstimo ativo encontrado para esse aluno e livro.\n");
    return;
  }

  char dataHoje[11];
  obterDataAtual(dataHoje);

  int diasDiferenca =
      compararDatas(dataHoje, emprestimos[indiceEmprestimo].dataEmprestimo);

  if (diasDiferenca < 7) {
    system("clear");
    printf("Ainda restam %d dias de empréstimo.\n", 7 - diasDiferenca);
    printf("Você só pode renovar após os 7 dias.\n");
  } else {
    int opcao;
    printf("Seu empréstimo venceu. Deseja renovar por mais 7 dias?\n");
    printf("[1] Sim\n[2] Não\nOpção: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1) {
      time_t t = time(NULL);
      struct tm dataAtual = *localtime(&t);
      dataAtual.tm_mday += 7;
      mktime(&dataAtual);
      strftime(emprestimos[indiceEmprestimo].dataDevolucaoPrevista, 11,
               "%d/%m/%Y", &dataAtual);
      system("clear");
      printf("Empréstimo renovado com sucesso por mais 7 dias!\n");
    } else {
      system("clear");
      printf("A renovação foi cancelada. Por favor, devolva o livro.\n");
    }
  }
}

void pesquisarLivros() {
  system("clear");

  char termo[50];
  printf("===== PESQUISA DE LIVROS =====\n\n");
  printf("Digite um termo (nome, autor ou gênero): ");
  fgets(termo, sizeof(termo), stdin);
  termo[strcspn(termo, "\n")] = '\0';

  int encontrados = 0;

  for (int i = 0; i < quantidadeLivro; i++) {
    if (strstr(livro[i].nome, termo) || strstr(livro[i].autor, termo) ||
        strstr(livro[i].genero, termo)) {

      printf("\n--- Livro Encontrado ---\n");
      printf("Nome: %s\n", livro[i].nome);
      printf("ISBN: %d\n", livro[i].isbn);
      printf("Autor: %s\n", livro[i].autor);
      printf("Gênero: %s\n", livro[i].genero);
      printf("Páginas: %d\n", livro[i].paginas);
      printf("Emprestado: %s\n", livro[i].emprestimo ? "Sim" : "Não");
      encontrados++;
    }
  }

  if (encontrados == 0) {
    printf("\nNenhum livro encontrado com o termo \"%s\".\n", termo);
  }
}

void listarTudo() {
  system("clear");
  int i = 0;

  printf("===== LISTA DE ALUNOS =====\n");
  while (i < quantidadeAlunos) {
    printf("\nAluno %d:\n", i + 1);
    printf("Nome: %s\n", alunos[i].nome);
    printf("Idade: %d\n", alunos[i].idade);
    printf("Matrícula: %d\n", alunos[i].matricula);
    i++;
  }

  i = 0;
  printf("\n===== LISTA DE LIVROS =====\n");
  while (i < quantidadeLivro) {
    printf("\nLivro %d:\n", i + 1);
    printf("Nome: %s\n", livro[i].nome);
    printf("ISBN: %d\n", livro[i].isbn);
    printf("Autor: %s\n", livro[i].autor);
    printf("Gênero: %s\n", livro[i].genero);
    printf("Páginas: %d\n", livro[i].paginas);
    printf("Emprestado: %s\n", livro[i].emprestimo ? "Sim" : "Não");
    i++;
  }

  i = 0;
  printf("\n===== EMPRÉSTIMOS ATIVOS =====\n");
  while (i < quantidadeEmprestimos) {
    if (emprestimos[i].ativo) {
      printf("\nEmpréstimo %d:\n", i + 1);
      printf("Matrícula do Aluno: %d\n", emprestimos[i].matriculaAluno);
      printf("ISBN do Livro: %d\n", emprestimos[i].isbnLivro);
      printf("Data do Empréstimo: %s\n", emprestimos[i].dataEmprestimo);
      printf("Devolver até: %s\n", emprestimos[i].dataDevolucaoPrevista);
    }
    i++;
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
    emprestarLivro();
    break;
  case 4:
    renovarEmprestimo();
    break;
  case 5:
    devolucaoLivros();
    break;
  case 6:
    pesquisarLivros();
    break;

  case 7:
    listarTudo();
    break;
  }
  processo();
}

#endif
