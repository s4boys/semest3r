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
    
//    for(int i= 0; i < argc; i++){
//        printf("%i, %s\n", argc, argv[i]);
//    }
    
    printf("Line Count: %d, Word Count: %d, Char Count: %d\n", countLines(argv[1]), countWords(argv[1]), countChars(argv[1]));
    return (EXIT_SUCCESS);
}

int countWords(char* path) {
    FILE* file;
    file = fopen(path, "r");
    int count = 0;
    char i = 1;
    char prev = 'ö';
    if (file == NULL) {
        printf("File not found\n");
    }
    while ((i = fgetc(file)) != EOF) {
        if (i == ' ' || i == '\n'  && prev != '\n' && prev != ' ' && prev != '\t' && prev != '\r')
            count++;
        prev = i;
    }
    return count;
    
    fclose(file);

}

int countChars(char* path) {
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

int countLines(char* path) {
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