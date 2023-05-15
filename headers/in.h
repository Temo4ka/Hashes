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

int TextDtor(Text *text);