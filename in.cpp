#define _CRT_SECURE_NO_WARNINGS
#include "in.h"
#include <string.h>

int TextCtor(Text *text, const char *fileName) {
    catchNullptr(fileName);
    catchNullptr(  text  );

    text -> fileName = fileName;
    text ->  stream  = fopen(fileName, "r");

    if (text -> stream == nullptr) return EXIT_FAILURE; 

    size_t readSymbols = fread(text -> buffer, sizeof(char), BUFFER_SZ - 1, text -> stream);

    if (text -> buffer == nullptr) return EXIT_FAILURE;
    text -> buffer[BUFFER_SZ - 1] = '\0';

    return EXIT_SUCCESS;
}

int textToWords(Text* text, WordsArray* words) {
	catchNullptr(text);
	catchNullptr(words);

	words -> buffer = text -> buffer;

	words -> array  = (char **) calloc( MAX_STRING_NUM, sizeof(char *));
	catchNullptr(words -> array );

	return initWordsArray(words -> buffer, words);
}

int initWordsArray(char* buffer, WordsArray* words) {
	catchNullptr(buffer);
	catchNullptr(words);
	
	char *curString = strtok(buffer, DELIM);
	while (curString != nullptr) {
		if (words -> numOfWords == MAX_STRING_NUM) return EXIT_FAILURE;

		words -> array[words -> numOfWords] = (char *) calloc(MAX_DATA_SIZE, sizeof(char));
		catchNullptr(words->array[words->numOfWords]);
		strcpy(words->array[words->numOfWords], curString);
		
		words -> numOfWords++;
		curString = strtok(nullptr, DELIM);
	}

	return EXIT_SUCCESS;
}

int TextDtor(Text *text) {
    catchNullptr(text);

    text -> stream = nullptr;
    free(text -> buffer);

    return EXIT_SUCCESS;
}

int WordsArrayDtor(WordsArray* words) {
	catchNullptr(words);

	for (int cur = 0; cur < words -> numOfWords; cur++)
		free(words -> array[cur]);
	free(words -> array);

	return EXIT_SUCCESS;
}