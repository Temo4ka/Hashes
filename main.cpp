#include "headers/in.h"
#include "headers/hash.h"

int main() {
    HashFunc_t hashes[7] = { hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_7 };

    HashTable table = {};

    hashCtor(&table, hash_1);

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    

    // fprintf(stderr, "%s\n", text.buffer);
    initHashTable(&table, text.buffer);
    fprintf(stderr, "%d\n", table.numOfElems);

    // if (table.list[1].status == InActive) fprintf(stderr, "NULLPTR!!!\n");

    
    for (int i = 1; i < MOD; i++) {
        if (table.list[i].status == InActive)
            fprintf(stderr, "%d -> Inactive\n", i);
        else
            fprintf(stderr, "%d -> %d\n", i, table.list[i].prev[0]);
    }

    printf("Succes\n");

    return 0;
}