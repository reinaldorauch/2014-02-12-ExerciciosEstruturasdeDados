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

#define NO_ENDER 0
#define WITH_ENDER 1

#define SEARCH_BIGGER 1
#define SEARCH_LOWER 0

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
 * Retorna um número para ser procurado no vetor
 * @return O numero inputado
 */
int getNumToSearch() {
    int d;
    puts("Digite um número a ser procurado no array");
    scanf("%d", &d);
    __fpurge(stdin);

    return d;
}

/**
 * Verifica as repetições para determinado índice
 * @param vetor Haystack
 * @param i     Needle
 */
void verifyRepetitionFor(int *vetor, int *i) {
    int j, k, count = 0;
    int *indexArray = (int*) malloc(sizeof(int)),
        *temp = NULL;

    for (j = 0; j < TAM; j++)
        if(*i == *(vetor + j))   {
            *(indexArray + count++) = j;
            temp = (int*) realloc(indexArray, (count * sizeof(int)));
            if(temp)
                indexArray = temp;
        }

    if(count > 0) {
        printf("O valor %d aparece %d vezes nos índices: \n", *i, count);

        for (k = 0; k < count; k++)
            if((k + 1) == count)
                printf("nº %d \n\n", *(indexArray + k));
            else
                printf("nº %d, ", *(indexArray + k));
    } else
        printf("O valor %d não aparece nenhuma vez\n\n", *i);

    free(indexArray);

}

/**
 * Verifica as repetições para cada elemento do vetor
 * @param vetor o vetor que será utilizado para as verificações
 */
void countSame(int * vetor) {
    int i = getNumToSearch();

    verifyRepetitionFor(vetor, &i);

}

/**
 * Procura o maior ou o menor dependendo de maior
 * @param maior Verifica se é para procurar o maior ou o menor
 */
void findBiggerOrLower(int *vetor, int maior) {
    int *border = vetor, i;

    for (i = 1; i < TAM; i++)
    {
        if(maior && (*(vetor + i) > *border))
            border = (vetor + i);

        if(!maior && (*(vetor + i) < *border))
            border = (vetor + i);
    }

    if(maior)
        printf("\nO maior número é %d\n", *border);
    else
        printf("\nO menor número é %d\n", *border);
}

/**
 * Sai do programa
 */
void programExit() {
    printf("Saindo... \n");
    exit(0);
}

/**
 * Imprime o campo com o número
 * @param val   Valor a ser impresso
 * @param ender Se é final de linha ou não
 */
void printField(int *val, int ender) {
    printf("| %d ", *val);
    if(ender)
        puts("|");
}

/**
 * Imprime uma linha de divisão
 * @param width  a largura da linha,
 * @param ender  se tem o finalizador,
 */
void printLine(int width, int ender) {
    int i;
    putchar('+');
    for(i = 1; i < (width -1); i++) {
        putchar('-');
    }
    if(ender)
        puts("+");
}

/**
 * Verifica recursivamente a largura necessária para o campo
 * @param width a largura
 * @param value o valor
 */
void verifyIntegerWidth(int *width, int *value) {
    if((*value) < 0) {
        (*value) *= -1;
        (*width)++;
        verifyIntegerWidth(width, value);
    } else if((*value) > 10) {
        (*width)++;
        (*value) /= 10;
        verifyIntegerWidth(width, value);
    } else
        (*width)++;
}

/**
 * Imprime a a linha de separação vertical da tabela
 * @param v     valor para a verificação da largura necessária
 * @param ender se é final da linha ou não
 */
void printLineWithOffset(int *v, int ender) {
    int width = 4, origValue = *v;

    verifyIntegerWidth(&width, v);
    printLine(width, ender);
    *v = origValue;
}

/**
 * Imprime os índices em uma linhas
 * @param v     valor da célula
 * @param i     índice
 * @param ender se é o final do vetor
 */
void printIndexLine(int *v, int *i, int ender) {
    int j, width = 4, origValue = *v, indexWidth = 3;

    verifyIntegerWidth(&width, v);
    *v = origValue;

    origValue = *i;
    verifyIntegerWidth(&indexWidth, i);
    *i = origValue;

    putchar('|');
    putchar(' ');
    printf("%d", *i);
    for (j = 0; j < (width - indexWidth); j++)
        putchar(' ');

    if(ender)
        puts("|");
}

/**
 * Imprime o vetor horizontalmente na tela, na ordem natural
 * @param vetor ponteiro para o vetor-destino
 */
void printArrayStraight(int *vetor) {
    int i, we = NO_ENDER;

    putchar('\n');
    for(i = 0; i < TAM; i++) {
        if((i + 1) == TAM)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = 0; i < TAM; i++) {
        if((i + 1) == TAM)
            we = WITH_ENDER;
        printIndexLine(vetor + i, &i, we);
    }


    we = NO_ENDER;

    for(i = 0; i < TAM; i++) {
        if((i + 1) == TAM)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = 0; i < TAM; i++) {
        if((i + 1) == TAM)
            we = WITH_ENDER;
        printField(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = 0; i < TAM; i++) {
        if((i + 1) == TAM)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }
    putchar('\n');
}

/**
 * Imprime o vetor horizontalmente na tela, na ordem reversa
 * @param vetor ponteiro para o vetor-destino
 */
void printArrayReverse(int *vetor) {
    int i, we = NO_ENDER;

    putchar('\n');
    for(i = (TAM - 1); i >= 0; i--) {
        if(i == 0)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = (TAM - 1); i >= 0; i--) {
        if(i == 0)
            we = WITH_ENDER;
        printIndexLine(vetor + i, &i, we);
    }


    we = NO_ENDER;

    for(i = (TAM - 1); i >= 0; i--) {
        if(i == 0)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = (TAM - 1); i >= 0; i--) {
        if(i == 0)
            we = WITH_ENDER;
        printField(vetor + i, we);
    }

    we = NO_ENDER;

    for(i = (TAM - 1); i >= 0; i--) {
        if(i == 0)
            we = WITH_ENDER;
        printLineWithOffset(vetor + i, we);
    }
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
 * Realiza o input no vetor repositório
 * @param  vetor vetor destinatário dos dados
 * @return       se foi válido a entrada de dados
 */
int dataInput(int *vetor) {
    putchar('\n');
    printLine(MENU_WIDTH, WITH_ENDER);
    printf("| %-36s |\n", "Digite os números para popular o vetor");
    printLine(MENU_WIDTH, WITH_ENDER);
    putchar('\n');

    int i;

    for(i = 0; i < TAM; i++)
        *(vetor + i) = validateInput(&i, getNum(&i));

    putchar('\n');
    stopProgramForEnter();
    return 1;
}

/**
 * Imprime o menu
 */
void printMenu() {
    printLine(MENU_WIDTH, WITH_ENDER);
    printf("| %-36s |\n", "[E] Entrada dos dados");
    printf("| %-36s |\n", "[D] Listagem direta");
    printf("| %-36s |\n", "[I] Listagem inversa");
    printf("| %-36s |\n", "[M] Procurar o maior");
    printf("| %-36s |\n", "[N] Menor elemento");
    printf("| %-38s |\n", "[C] Contagem de repetições de ");
    printf("| %-31s |\n", "\tdeterminado elemento");
    printf("| %-37s |\n", "[A] Média dos elementos do vetor");
    printf("| %-36s |\n", "[S] Sair do programa");
    printLine(MENU_WIDTH, WITH_ENDER);
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
    printLine(SCR_WIDTH, WITH_ENDER);
    printf("| %-77s |\n", "12-02-2014, Revisão sobre vetores");
    printLine(SCR_WIDTH, WITH_ENDER);
    putchar('\n');
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
                if(hadInput)
                    printArrayStraight(vetor);
                else
                    puts("\nNão houve entrada de dados. Insira-os e tente novamente\n");
                stopProgramForEnter();
                break;

            // Listagem Inversa
            case 'I':
                if(hadInput)
                    printArrayReverse(vetor);
                else
                    puts("\nNão houve entrada de dados. Insira-os e tente novamente\n");
                stopProgramForEnter();
                break;

            // Procura o maior elemento
            case 'M':
                if(hadInput)
                    findBiggerOrLower(vetor, SEARCH_BIGGER);
                else
                    puts("\nNão houve entrada de dados. Insira-os e tente novamente\n");
                stopProgramForEnter();
                break;

            // Procura o menor elemento
            case 'N':
                if(hadInput)
                    findBiggerOrLower(vetor, SEARCH_LOWER);
                else
                    puts("\nNão houve entrada de dados. Insira-os e tente novamente\n");
                stopProgramForEnter();
                break;

            // Contagem de repetições
            case 'C':
                if(hadInput)
                    countSame(vetor);
                else
                    puts("\nNão houve entrada de dados. Insira-os e tente novamente\n");
                stopProgramForEnter();
                break;

            // Média entre os elementos do vetor
            case 'A':

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