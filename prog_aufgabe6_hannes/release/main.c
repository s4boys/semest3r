/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Nico
 * 
 */


// Usage of this software:
// -w flag for wordcount
// -l flag for linecount
// -c flag for charcount
// followed by the path of the file you wish to analyze

// flags can be combined to your liking, like this: -wlc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINELENGTH 1024

typedef struct flags{
    char wflag;
    char lflag;
    char cflag;
}flags;


/*
 * 
 */
int countWords(char* path);
int countLines(char* path);
int countChars(char* path);
int countOccurences(char* path);

int main(int argc, char** argv) {

    int opt;
    flags myflags = {0,0,0};

    while((opt = getopt(argc, argv, "lcw")) != -1){

        switch(opt){
            case 'w': myflags.wflag++;break;
            case 'l': myflags.lflag++;break;
            case 'c': myflags.cflag++;break;
        }
    }


    while(optind < argc){
        printf("%s: ", argv[optind]);
        if(myflags.wflag){
            int wcount = countWords(argv[optind]);
            printf("%d Words ", wcount);
        }

        if(myflags.lflag){
            int lcount = countLines(argv[optind]);
            printf("%d Lines ", lcount);
        }

        if(myflags.cflag){
            int ccount = countChars(argv[optind]);
            printf("%d Characters ", ccount);
        }
        printf("\n");
        optind++;

    }

    return (EXIT_SUCCESS);


}

int countWords(char* path) {
    FILE* file;
    file = fopen(path, "r");
    

    char delimiters[] =  " ,.;\n\r\t";
    char *wordpointer;
    int counter=0;


    char string[MAXLINELENGTH];
    
    do{
        wordpointer = fgets(string, MAXLINELENGTH, file);

        if(wordpointer!=NULL){
            char *tokenfound;
            tokenfound = strtok(string, delimiters);
            while(tokenfound!=NULL){
                counter++;
                tokenfound = strtok(NULL, delimiters);
            }
        }
    }while(wordpointer!= NULL);

    fclose(file);
    return counter;
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