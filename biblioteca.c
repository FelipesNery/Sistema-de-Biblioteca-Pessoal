#include <stdio.h>

struct Livro {
    char nome[100];
    char autor[100];
    char isbn[20]; // texto: ISBN tem 13 digitos e nao cabe em int
};

int main() {
    int opcao;
    int i;
    struct Livro biblioteca[100];
    int total_livros = 0;
    FILE *arquivo;

    // 1. CARREGAR LIVROS SALVOS AO INICIAR
    arquivo = fopen("biblioteca.txt", "r");
    if (arquivo != NULL) {
        while (total_livros < 100 &&
               fscanf(arquivo, " %99[^;];%99[^;];%19[^\n]\n",
                      biblioteca[total_livros].nome,
                      biblioteca[total_livros].autor,
                      biblioteca[total_livros].isbn) == 3) {
            total_livros++;
        }
        fclose(arquivo);
    }

    do {
        printf("\n=== Sistema de Biblioteca Pessoal ===\n");
        printf("Opcao 1: Cadastrar livro\n");
        printf("Opcao 2: Visualizar biblioteca\n");
        printf("Opcao 0: Sair\n");
        printf("Escolha a opcao que deseja: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (total_livros < 100) {
                    printf("\nEscreva o nome do livro: ");
                    scanf(" %99[^\n]", biblioteca[total_livros].nome);

                    printf("Escreva o nome do autor: ");
                    scanf(" %99[^\n]", biblioteca[total_livros].autor);

                    printf("Escreva o ISBN (apenas numeros): ");
                    scanf(" %19[^\n]", biblioteca[total_livros].isbn);

                    // 2. SALVAR O NOVO LIVRO NO ARQUIVO
                    arquivo = fopen("biblioteca.txt", "a"); // "a" adiciona no final sem apagar os antigos
                    if (arquivo != NULL) {
                        fprintf(arquivo, "%s;%s;%s\n",
                                biblioteca[total_livros].nome, 
                                biblioteca[total_livros].autor, 
                                biblioteca[total_livros].isbn);
                        fclose(arquivo);
                    }

                    total_livros++;
                    printf("Livro cadastrado e salvo com sucesso!\n");
                } else {
                    printf("A biblioteca esta cheia!\n");
                }
                break;

            case 2:
                printf("\n--- Livros na Biblioteca ---\n");
                if (total_livros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (i = 0; i < total_livros; i++) {
                        printf("%d. %s | Autor: %s | ISBN: %s\n",
                               i + 1, 
                               biblioteca[i].nome, 
                               biblioteca[i].autor, 
                               biblioteca[i].isbn);
                    }
                }
                break;

            case 0:
                printf("Fechando biblioteca!!\n");
                break;

            default:
                printf("Opcao invalida, escolha uma opcao possivel!!\n");
        }

    } while (opcao != 0);

    return 0;
}
