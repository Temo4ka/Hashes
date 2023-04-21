#include "headers/in.h"
#include "headers/hash.h"


int main() {
    HashTable table = {};

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) return EXIT_FAILURE;

    initHashTable(&table, text.buffer, hash_2);

    printf("Succes\n");

    return 0;
}