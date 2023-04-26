#include "headers/test.h"

int test(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName) {
    catchNullptr(     text     );
    catchNullptr(   hashFuncs  );
    catchNullptr(outputFileName);

    HashTable table = {};

    FILE* stream = fopen(outputFileName, "w");
    catchNullptr(stream);

    for (int curFunc = 0; curFunc <= HASH_FUNC_NUM; curFunc++) {
        hashCtor(&table, hashFuncs[curFunc]);
        initHashTable(&table, text -> buffer);

        fprintf(stream, "HashFunction%d(%d),", curFunc + 1, table.numOfElems);
        
        for (int i = 1; i < MOD; i++) {
            if (table.list[i].status == InActive)
                fprintf(stream, "0, ");
            else
                fprintf(stream, "%d, ", i, table.list[i].prev[0]);
        }
        fprintf(stream, "\n");

        hashDtor(&table);
    }

    fclose(stream);

    return EXIT_SUCCESS;
}