#include "headers/in.h"
#include "headers/list.h"

int TextCtor(Text *text, const char *fileName) {
    catchNullptr(fileName);
    catchNullptr(  text  );

    text -> fileName = fileName;
    text ->  stream  = fopen(fileName, "r");

    if (text -> stream == nullptr) return EXIT_FAILURE; 

    size_t readSymbols = fread(text -> buffer, sizeof(char), BUFFER_SZ - 1, text -> stream);

    if (text -> buffer == nullptr) return EXIT_FAILURE;
    text -> buffer[readSymbols] = '\0';

    return EXIT_SUCCESS;
}

int TextDtor(Text *text) {
    catchNullptr(text);

    text -> stream = nullptr;
    free(text -> buffer);

    return EXIT_SUCCESS;
}