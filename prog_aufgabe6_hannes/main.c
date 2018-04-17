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

struct counter {
    int wordcount;
    int linecount;
    int charcount;
} ct;
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

    ct.wordcount = 0;
    ct.charcount = 0;
    ct.linecount = 0;

    countOccurences(argv[argc - 1]);
    printf("Line Count: %d, Word Count: %d, Char Count: %d\n", ct.linecount, ct.wordcount, ct.charcount);

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

    return (EXIT_SUCCESS);


}

int countOccurences(char* path) {
    FILE* file;
    file = fopen(path, "r");
    char singleChar = 0;
    int whitespace = 1;
    if (file == NULL) {
        fprintf(stdout, "%s", "File not found\n");
    }
    char *wordSeparators = "\n\t ";
    char *lineSeparators = "\n";
    while ((singleChar = fgetc(file)) != EOF) {
        //        if (strchr(wordSeparators, singleChar) && (!(strchr(wordSeparators, previous)))){
        if (strchr(wordSeparators, singleChar) && whitespace) {
            ct.wordcount++;
            whitespace = 0;
        }
        if (strchr(lineSeparators, singleChar)) {
            ct.linecount++;
        }
        if (!strchr(wordSeparators, singleChar)) {
            whitespace = 1;
        }
        ct.charcount++;

    }
    fclose(file);
    return 0;
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