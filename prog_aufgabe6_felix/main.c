/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: felix
 *
 * Created on 16. April 2018, 11:36
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int countWords(char* path);
int countLines(char* path);
int countChars(char* path);

int main(int argc, char** argv) {
    char parameters[5] = ""; //fünf Plätze für Argumente
    for (int i = 1; i < (argc - 1); i++) {
        char* paramPos = strchr(argv[i], '-') + 1; 
        if (paramPos != NULL) {
            strcat(parameters, paramPos);
        } else {
            printf("%s", "unknown argument");
        }
    }

    
//    for(int i= 0; i < argc; i++){
//        printf("%i, %s\n", argc, argv[i]);
//    }
    char wordCount = 'w';
    char lineCount = 'l';
    char charCount = 'c';
    if (strchr(parameters,wordCount)){
        printf("Words: %d\n",countWords(argv[argc - 1])); //Aufruf countWords wenn Parameter = w
    }
    if (strchr(parameters,lineCount)){
        printf("Lines: %d\n",countLines(argv[argc - 1])); //Aufruf countLines wenn Parameter = l
    }
    if (strchr(parameters,charCount)){
        printf("Chars: %d\n",countChars(argv[argc - 1])); //Aufruf countChars wenn Parameter = c (=countBytes)
    } else {
        printf("Line Count: %d, Word Count: %d, Char Count: %d\n", countLines(argv[argc - 1]), countWords(argv[argc - 1]), countChars(argv[argc - 1]));
    }
    
    return (EXIT_SUCCESS);
}

int countWords(char* path) { //zählt wörter in file
    FILE* file;
    file = fopen(path, "r");
    int count = 0;
    char i = 1;
    char prev = 'q'; //setze einen prev char der verhindert dass doppelte Leerzeichen usw. gezählt werden
    if (file == NULL) {
        printf("File not found\n");
    }
    while ((i = fgetc(file)) != EOF) {
        if (i == ' ' || i == '\n'  && prev != '\n' && prev != ' ' && prev != '\t' && prev != '\r') //Bedingungen um Wörter zu erkennen
            count++;
        prev = i; // setze prev char auf den Wert des aktuellen Chars.
    }
    return count;
    
    fclose(file);

}

int countChars(char* path) { //Zählt chars/bytes in file
    FILE* file;
    file = fopen(path, "r");
    int count = 0;
    char i;
    if (file == NULL) {
        printf("File not found\n");
    }
    while ((i = fgetc(file)) != EOF) {
        count++;
    }
    return count;
    fclose(file);
}

int countLines(char* path) { //zählt lines in file
    FILE* file;
    file = fopen(path, "r");
    int count = 0;
    char i = 0;
    if (file == NULL) {
        printf("File not found\n");
    }
    while ((i = fgetc(file)) != EOF) {
        if (i == '\n') { 
            count++;
        }
    }
    return count;
    fclose(file);
}



//int argumentHandler(char** argv){
//    if(argv[1] == "-c" || argv[2] == "-c" || argv[3] == "-c")
//        return countChars(argv[4]);
//    else if(argv[1] == "-l" || argv[2] == "-l" || argv[3] == "-l")
//        return countLines(argv[4]);
//    else if (argv[1] == "-w" || argv[2] == "-w" || argv[3] == "-w")
//        return countWords(argv[4]);
//    
//    
//}