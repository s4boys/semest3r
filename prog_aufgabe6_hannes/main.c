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
    char parameters[10] = ""; // 10 plätze für übergebene Argumente
    for (int i = 1; i < (argc - 1); i++) { // zählt vom 2 bis vorletzen Arg. (Name und File nicht)
        char* paramPos = strchr(argv[i], '-') + 1; //paramPos ist Zeiger auf zeichen '-' in argv[i], +1 weil mich '-' nicht interessiert
        if (paramPos != NULL) { // wenn nicht gefunden ist zeiger null
            strcat(parameters, paramPos); // hänge mein zeichen nach '-' an parameters
        } else {
            printf("%s", "unknown argument");
        }
    }
    // Struktur mit 0 initialisiert
    ct.wordcount = 0;
    ct.charcount = 0;
    ct.linecount = 0;
    // Zaehle alle auftreten
    countOccurences(argv[argc - 1]);

    // wenn jeweiliger Buchstabe in parameter vorhanden ist -> drucke counter
    char words = 'w';
    char lines = 'l';
    char chars = 'c';
    if (strchr(parameters,words)){
        printf("Wordcounter: %d ",ct.wordcount);
    }
    if (strchr(parameters,lines)){
        printf("Linecounter: %d ",ct.linecount);
    }
    if (strchr(parameters,chars)){
        printf("Charcounter: %d",ct.charcount);
    }
    printf("\n");
    return (EXIT_SUCCESS);


}

int countOccurences(char* path) {
    FILE* file;
    file = fopen(path, "r");
    char singleChar = 0; //einzelner gelesener Char
    int whitespace = 1; // whitespace "boolean" 1 heißt für mich letztes Zeichen kein whitespace
    if (file == NULL) {
        fprintf(stdout, "%s", "File not found\n");
    }
    char *wordSeparators = "\n\t "; //String mit Zeichen die whitespace bedeuten
    char *lineSeparators = "\n"; // String nur für Zeilenumbruch
    while ((singleChar = fgetc(file)) != EOF) { // lese char aus file solange kein fileende
        if (strchr(wordSeparators, singleChar) && whitespace) { // wenn singleChar in wordSeparators 
        //drinsteht && letztes Zeichen kein Whitespace
            ct.wordcount++;
            whitespace = 0; // letztes Zeichen war whitespace
        }
        if (strchr(lineSeparators, singleChar)) { // wie zuvor
            ct.linecount++;
        }
        if (!strchr(wordSeparators, singleChar)) { // wie zuvor
            whitespace = 1;
        }
        ct.charcount++;

    }
    fclose(file);
    return 0;
}
