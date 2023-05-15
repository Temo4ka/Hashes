<<<<<<< HEAD
#pragma once
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct Text {
    char *buffer = (char *) calloc(BUFFER_SZ, sizeof(char));

    FILE *stream = nullptr;

    const char *fileName = nullptr;
};

struct WordsArray {
	char *buffer   = nullptr;
	char **array   = nullptr;
	
	int numOfWords = 0;
};

int TextCtor(Text *text, const char *fileName);

int textToWords(Text* text, WordsArray *words);

int initWordsArray(char *buffer, WordsArray *words);

int WordsArrayDtor(WordsArray* words);

=======
#pragma once
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct Text {
    char *buffer = (char *) calloc(BUFFER_SZ, sizeof(char));

    FILE *stream = nullptr;

    const char *fileName = nullptr;
};

struct WordsArray {
	char *buffer   = nullptr;
	char **array   = nullptr;
	
	int numOfWords = 0;
};

int TextCtor(Text *text, const char *fileName);

int textToWords(Text* text, WordsArray *words);

int initWordsArray(char *buffer, WordsArray *words);

int WordsArrayDtor(WordsArray* words);

>>>>>>> 4a0a211e26fa9b71d07de0bc5cf7e43c6228120f
int TextDtor(Text *text);