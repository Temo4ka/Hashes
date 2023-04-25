#include "headers/in.h"
#include "headers/hash.h"


int main() {
    HashTable table = {};

    hashCtor(&table, hash_7);

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    // fprintf(stderr, "%s\n", text.buffer);
    initHashTable(&table, text.buffer);
    fprintf(stderr, "%d\n", table.numOfElems);

    if (table.list[1].status == InActive) fprintf(stderr, "NULLPTR!!!\n");

    for (int i = 1; i < MOD; i++) {
        fprintf(stderr, "%d -> %d", i, table.list[i].prev[0]);
    }

    printf("Succes\n");

    return 0;
}