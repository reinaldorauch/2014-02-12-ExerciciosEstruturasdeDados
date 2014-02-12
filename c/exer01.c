/**
 * @author Reinaldo A. C. Rauch <reinaldorauch@gmail.com>
 *
 * Resolução do exercício 01 da lista de hoje (12-04-2014)
 *
 * 1. Escreva um programa no qual o usuário digite 10 números inteiros
 * que serão armazenados em um vetor. Sobre esse vetor:
 * a. Imprima em ordem direta (do elemento na posição 0 até o
 * elemento na posição 9)
 * b. Imprima em ordem inversa (do elemento na posição 9 até o
 * elemento na posição 0)
 * c. Procure o maior elemento do vetor
 * d. Procure o menor elemento do vetor
 * e. Calcule quantas vezes e em que posições do vetor aparece
 * um determinado número digitado pelo usuário
 * f. Calcule a média entre os 10 valores
 *
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 10

#define SCR_WIDTH 80

#define MENU_WIDTH 40

/**
 * Imprime uma linha de divisão
 * @param width  a largura da linha,
 */
void printLine(int width) {
    int i;
    putchar('+');
    for(i = 1; i < (width -1); i++) {
        putchar('-');
    }
    putchar('+');
    putchar('\n');
}

/**
 * Retorna o valor inputado, se válido. Se não, retorna 0 e força a voltar uma
 * iteração na estrutura de controle
 * @param  i   índice no iterator
 * @param  val valor entrado pelo usuário
 * @return     valor do usuário, se válido. Se não, 0
 */
int validateInput(int *i, int val) {
    return val;
}

/**
 * Pega um número do usuário
 * @param  i índice do iterator
 * @return   valor recebido
 */
int getNum(int *i) {
    int b;

    printf("Digite o número para a pos %d do vetor:\n", *i);
    scanf("%d", &b);
    __fpurge(stdin);

    return b;
}

/**
 * Pega um caractere da stdin e limpa o resto
 * @return retultado de validateCharOption
 */
char getCharWipeInputStream() {
    char c = ' ';

    c = fgetc(stdin);
    __fpurge(stdin);

    return c;
}

/**
 * Para o programa, para eperar por um enter
 */
void stopProgramForEnter() {
    puts("\nPressione enter para continuar...");
    getCharWipeInputStream();
}

/**
 * Realiza o input no vetor repositório
 * @param  vetor vetor destinatário dos dados
 * @return       se foi válido a entrada de dados
 */
int dataInput(int *vetor) {
    putchar('\n');
    printLine(MENU_WIDTH);
    printf("| %-36s |\n", "Digite os números para popular o vetor");
    printLine(MENU_WIDTH);
    putchar('\n');

    int i;

    for(i = 0; i < TAM; i++)
        *(vetor + i) = validateInput(&i, getNum(&i));

    putchar('\n');
    stopProgramForEnter();
}

/**
 * Imprime o menu
 */
void printMenu() {
    printLine(MENU_WIDTH);
    printf("| %-36s |\n", "[E] Entrada dos dados");
    printf("| %-36s |\n", "[D] Listagem direta");
    printf("| %-36s |\n", "[I] Listagem inversa");
    printf("| %-36s |\n", "[M] Procurar o maior");
    printf("| %-36s |\n", "[N] Menor elemento");
    printf("| %-38s |\n", "[C] Contagem de repetições de ");
    printf("| %-31s |\n", "\tdeterminado elemento");
    printf("| %-37s |\n", "[A] Média dos elementos do vetor");
    printf("| %-36s |\n", "[S] Sair do programa");
    printLine(MENU_WIDTH);
}

/**
 * Valida os chars de input para o menu, sendo inválido, força a saída do
 * programa
 * @param  c caractere a ser validado
 * @return   retorna o caractere inputado se for válido. Se não, retorna 'S',
 *                   para forçar a saída do programa
 */
char validateCharOption(c) {
    int numEq = c;
    if(numEq < 65 || numEq > 90) {
        printf("Erro na entrada da opção, saindo do programa\n");
        return 'S';
    } else
        return c;
}

/**
 * Imprime o menu e pega um char da stream, limpado-a após
 * @return o char escolhido
 */
char getOption() {
    printMenu();
    return validateCharOption(getCharWipeInputStream());
}

/**
 * Imprime o header do programa
 */
void header() {
    system("clear");
    printLine(SCR_WIDTH);
    printf("| %-77s |\n", "12-02-2014, Revisão sobre vetores");
    printLine(SCR_WIDTH);
    putchar('\n');
}

/**
 * Sai do programa
 */
void programExit() {
    printf("Saindo... \n");
    exit(0);
}

/**
 * Roda o programa
 * @param vetor Vetor para o acondicionamento dos dados
 */
void run(int *vetor) {

    int hadInput = 0;

    while(1) {
        header();

        switch(getOption()) {
            // Entrada de dados
            case 'E':
                if(dataInput(vetor))
                    hadInput = 1;
                break;

            // Listagem direta
            case 'D':

            // Listagem Inversa
            case 'I':

            // Procura o maior elemento
            case 'M':

            // Procura o menor elemento
            case 'N':

            // Sai do programa
            case 'S':
                programExit();
        }

    }

}

/**
 * Main function
 * @return 0 for no error
 */
int main()
{

    int vetor[TAM];

    run(vetor);

    return 0;
}