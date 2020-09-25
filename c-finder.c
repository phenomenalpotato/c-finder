/* Esse programa irá receber uma palavra e um arquivo qualquer. O mesmo irá verificar se essa palvara está no arquivo. No final, se essa palavra estiver no arquivo,
o programa irá printar o nome do arquivo. O arquivo já deve existir! O programa deve receber um arquivo e devolver se nesse arquivo tem a palavra digitada pelo o Usuário */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h> // Para utilizar a função regcomp() e a regexec()
#include <unistd.h> // Para utilizar a função sleep();

// Macro para colocar uma linha pontilhada para fazer uma "separação melhor" e melhor visualização
#define PONTO puts("--------------------=====================================--------------------");
#define SEPARQ puts("-----------================COUNTEUDO NO ARQUIVO=====================------------"); printf("\n");;

void printf_result(int value) {

    // If pattern found
    if(value == 0) {

        puts("Pattern found!");

    }

    // If pattern not found 
    else if(value == REG_NOMATCH) {

        puts("Pattern not found!");

    }

    // If error occured during Pattern Match
    else {

        puts("An error occurred!");
    }

}

void help(char *hel, char *text) {

    switch (*hel) { 
    
    case 'h': // Option 'h' will display the help with example on how to utilize the program
        
        printf("    - How to use:  \n"
            "           c-finder name_of_the_file \n\n"
        
        "    - The file MUST exist to be searched through!\n"
        "    - Example: \n\n" 
               "        c-finder example.txt\n\n"
               "    - If you want to see the text inside the file use: \n\n"
               "        c-finder name_of_the_file v \n");
        exit(0);

        break;
    case 'v': // the 'v' option will print the text that is inside the file

            SEPARQ
            printf("%s\n", text);
            SEPARQ

        break;
        
    }

}

int main(int argc, char *argv[]) {

    FILE *fh; // Ponteiro para o arquivo

    char texto[500]; 
    char frase[40];

    int value; // value irá armazenar o valor do retorno da função regcomp();

    regex_t reg; // Variável para criar a regex

    if(argc == 1) {

        puts("The program MUST have at least one argument!");
        exit(1);

    }

    if (*argv[1] == 'h') {

        help(argv[1], NULL); // Chamando a função help() passando como argumento o segundo elemento de argv[2]
    } 

    fh = fopen(argv[1], "r"); // fopen é uma função que abre o arquivo. Parâmetros "r" da função fopen para abrir um arquivo para ler

    if (fh == NULL) {

        perror("Error in opening the file");
        exit(1);
    }

    fread(texto, sizeof(char), 500, fh);

    printf("Qual a String que está procurando: ");
    scanf("%s", frase);

    printf("Expressão que será usada: %s\n", frase);

    if(argc == 3) { // Se haver exatos 3 argumentos passados para o programa. Ou seja, executar o programa com o um argumento 

        if(*argv[2] == 'v') { // if o segundo argumento for igual a 'v' irá passar como argumento para a função help() o char 'v'

            help(argv[2], texto);
        }

    }
 
    value = regcomp(&reg, frase, 0); 

    // If compilation is successful
    if(value == 0) {

        PONTO
        puts("Regex Compiled Successfuly!");
        PONTO
    }

    // Else for compilation error
    else {

        PONTO
        perror("Compilation Error!");
        PONTO

    }

    // O processo irá dormir por 3 segundos
    // Maybe you're asking yourself " But, why? " Because it looks cool!
    sleep(3);

    value = regexec(&reg, texto, 0, NULL, 0); // Função usada para dar match em uma string contra um padrão. regexec(&regex, expression, 0, NULL, 0);

    printf_result(value); // Chamando a função para printar na tela o resultado 
    PONTO

    if(value == 0) {

        printf("Nome do arquivo na qual deu Match: %s\n", argv[1]);

    }

    regfree(&reg);

    fclose(fh); // Fecha o arquivo que foi aberto

    return 0;
}