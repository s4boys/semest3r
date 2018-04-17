/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hannes
 *
 * Created on April 17, 2018, 7:57 PM
 */

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
//    char parameters[10] = "";
//    for (int i = 1; i < (argc - 1); i++) {
//        char* paramPos = strchr(argv[i], '-') + 1;
//        if (paramPos != NULL) {
//            strcat(parameters, paramPos);
//        } else {
//            printf("%s", "unknown argument");
//        }
//    }
//    printf("%s", parameters);

            //    printf("%s,%s,%s", parameters[0], parameters[1], parameters[2]);


            //    char parameters[3][4];
            //    for (int i = 1; i < (argc - 1); i++) {
            //        char* paramPos = strchr(argv[i], '-') + 1;
            //        if (paramPos != NULL) {
            //            strcpy(parameters[i - 1], paramPos);
            //        }
            //    }
            //    printf("%s,%s,%s",parameters[0],parameters[1],parameters[2]);
            //    char parameters[2][3];
            //    char* pos1 = "xd";
            //    char* pos2 = "oo";
            //    strcpy(parameters[1],pos1);
            //    strcpy(parameters[2],pos2);
            //    
            //    printf("%s%s",parameters[1],parameters[2]);


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
            int lcount = countWords(argv[optind]);
            printf("%d Lines ", lcount);
        }

        if(myflags.cflag){
            int ccount = countWords(argv[optind]);
            printf("%d Characters ", ccount);
        }
        printf("\n");

    }

    return (EXIT_SUCCESS);


}
//
//int main(int argc, char** argv) {
//    if (argc > 2) {
//        argv[argc + 2] = argv[4];
//        argumentHandler(argv[1]);
//    }
//    for (int i = 0; i < argc; i++) {
//        printf("%i, %s\n", argc, argv[i]);
//    }
//
//    printf("Line Count: %d, Word Count: %d, Char Count: %d\n", countLines(argv[1]), countWords(argv[1]), countChars(argv[1]));
//    return (EXIT_SUCCESS);
//}

// int countOccurences(char* path) {
//     FILE* file;
//     file = fopen(path, "r");
//     char singleChar;
//     char previous = 'o';
//     if (file == NULL) {
//         fprintf(stdout, "%s", "File not found\n");
//     }
//     const char *wordSeparators = "\n\t ";
//     const char *lineSeparators = "\n";
//     while ((singleChar = fgetc(file)) != EOF) {
//         if (strchr(wordSeparators, singleChar & !(strchr(wordSeparators, previous)))) {
//             ct.wordcount++;
//             previous = singleChar;
//         }
//         if (strchr(lineSeparators, singleChar)) {
//             ct.linecount++;
//         }
//         ct.charcount++;
//     }
//     fclose(file);
//     return 0;
// }

int countWords(char* path) {
    FILE* file;
    file = fopen(path, "r");
    

    char delimiters[] =  " ,.;\n\r\t";
    char *wordpointer;
    int counter;


    char string[MAXLINELENGTH];
    
    do{
        wordpointer = fgets(string, MAXLINELENGTH, file);

        if(wordpointer!=NULL){
            wordpointer = strtok(string, delimiters);
            while(wordpointer!=NULL){
                counter++;
                wordpointer = strtok(NULL, delimiters);
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

