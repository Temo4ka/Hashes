#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct Text {
    char *buffer = (char *) calloc(BUFFER_SZ, sizeof(char));

    FILE *stream = nullptr;

    const char *fileName = nullptr;
};

int TextCtor(Text *text, const char *fileName);

int TextDtor(Text *text);