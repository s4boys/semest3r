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

    printf("Line Count: %d, Word Count: %d, Char Count: %d\n", countLines(argv[1]), countWords(argv[1]), countChars(argv[1]));
    return (EXIT_SUCCESS);
}

int countWords(char* path) {
    FILE* file;
    file = fopen(path, "r");
    int count = 0;
    char i = 0;
    char prev = 'a';
    if (file == NULL) {
        printf("File not found\n");
    }
    while ((i = fgetc(file)) != EOF) {
        if (i == ' '  && prev!= '\n')
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

