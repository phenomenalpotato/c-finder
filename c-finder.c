/* Esse programa irá receber uma palavra e um arquivo qualquer. O mesmo irá verificar se essa palvara está no arquivo. No final, se essa palavra estiver no arquivo,
o programa irá printar o nome do arquivo. O arquivo já deve existir! O programa deve receber um arquivo e devolver se nesse arquivo tem a palavra digitada pelo o Usuário 


This program will receive a word and any file. It will check if that word is in the file. In the end, if that word is in the file,
the program will print the file name. The file must already exist! */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h> // Para utilizar a função regcomp() e a regexec(). To use the regcomp() function
#include <unistd.h> // Para utilizar a função sleep();. To use the sleep() function

// Macro para colocar uma linha pontilhada para fazer uma "separação melhor" e melhor visualização
// Macro to put one dotted line to do a "better separation" and better visualization
#define PONTO puts("--------------------=====================================--------------------");
#define SEPARQ printf("-----------================COUNTEUDO NO ARQUIVO=====================------------\n\n");

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

void help(char *hel, char *text, char *nameFile) {

    FILE *fe;

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

    case 'f': // The 'f' option will write the in the File-Name.txt

        fe = fopen("File-Name.txt", "a+");

        if(fe == NULL) {

            perror("Error in opening the file");
            exit(1);
        }

        fputs(nameFile, fe);

        fputs("\n", fe);

        printf("O arquivo File-Name.txt foi criado!\nO(s) nome(s) do(s) arquivo(s) que deram Match está escrito no arquivo File-Name.txt\n");

        fclose(fe);

        break;
        
    }

}

int main(int argc, char *argv[]) {

    FILE *fh; // Ponteiro para o arquivo
             // Pointer to the file

    char texto[1000]; 
    char frase[40];

    int value; // value irá armazenar o valor do retorno da função regcomp();
              // The variable value will store the return value of the regcomp() function  

    regex_t reg; // Variável para criar a regex
                // Variable to create the regex

    if(argc == 1) { // Se não for passado nenhum argumeto, somente o nome do programa para o argv[]
                   // If no argument is passed, only the program name for argv[] is passed 

        puts("The program MUST have at least one argument!");
        exit(1);

    }

    if (*argv[1] == 'h') {

        help(argv[1], NULL, NULL); // Chamando a função help() passando como argumento o segundo elemento de argv[2]
                                  // Calling the help () function passing the second element of argv[2] as an argument /
    } 

    fh = fopen(argv[1], "r"); // fopen é uma função que abre o arquivo. Parâmetro "r" da função fopen para abrir um arquivo para ler
                             // fopen is a function that opens the file. "R" parameter of the fopen function is to open a file to read

    if (fh == NULL) {

        perror("Error in opening the file");
        exit(1);
    }

    fread(texto, sizeof(char), 1000, fh);

    printf("Qual a String que está procurando: ");
    scanf("%s", frase);

    if(argc == 3) { // Se houver exatos 3 argumentos passados para o programa. Ou seja, executar o programa com um argumento 
                   // If there are exactly 3 arguments passed to the program.

        if(*argv[2] == 'v') { // if o segundo argumento for igual a 'v' irá passar como argumento para a função help()  o char 'v'
                             // if the second argument is equal to 'v' it will pass char 'v' as an argument to the help() function
            
            help(argv[2], texto, NULL);
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
    // The process wiil sleep for 3 seconds
    // Maybe you're asking yourself " But, why? " Because it looks cool!
    sleep(3);

    value = regexec(&reg, texto, 0, NULL, 0); // Função usada para dar match em uma string contra um padrão. regexec(&regex, expression, 0, NULL, 0);
                                             // Function used to match a string against a pattern. regexec (& regex, expression, 0, NULL, 0);

    printf_result(value ); // Chamando a função para printar na tela o resultado 
                          // Calling the function to print the result on the screen
    PONTO

    if(value == 0 && argc == 3) { // Se a Regex realmente deu match, e foram passados 3 argumentos para o programa
                                 // If Regex really matched, and 3 arguments were passed to the program
       
        if(*argv[2] == 'f') { // if o segundo argumento for a igual a 'f' irá passar como argumento para a função help() o char 'f'
                             // If the second argument is equal to 'f' it will pass char 'f' as an argument to the help() function
       
            help(argv[2], NULL, argv[1]);
        
        }      
        
        else { // Caso ele não tenha passado o argumento 'f', irá printar o nome do arquivo que deu match
              // If it has not passed the 'f' argument, it will print the name of the file that matched

            printf("Nome do arquivo na qual deu Match: %s\n", argv[1]); 

        }

    }

    else if (value == 0 && argc < 3 || argc > 3) {
        
        printf("Nome do arquivo na qual deu Match: %s\n", argv[1]); 

    }
    
    regfree(&reg);

    fclose(fh); // Fecha o arquivo que foi aberto
               // Closes the file that was opened

    return 0;
}