#include "headers/test.h"

int test(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName) {
    catchNullptr(     text     );
    catchNullptr(   hashFuncs  );
    catchNullptr(outputFileName);

    HashTable table = {};

    FILE* stream = fopen(outputFileName, "w");
    catchNullptr(stream);

    const char *hash_names[HASH_FUNC_NUM] = { "DumbHash", "FirstElem", "LengthHash", "SumHash", "XorCycleLHash", "XorCycleRHash", "GnuHash" };

    fprintf(stream, ", ");
    for (int cur = 0; cur < MOD; cur++) fprintf(stream, "%d, ", cur + 1);
    fprintf(stream, "\n");

    for (int curFunc = 3; curFunc < HASH_FUNC_NUM; curFunc++) {
        hashCtor(&table, hashFuncs[curFunc]);
        initHashTable(&table, text -> buffer);

        fprintf(stream, "%s_%d, ", hash_names[curFunc], table.numOfElems, table.numOfElems);
        for (int i = 1; i < MOD; i++) {
            if (table.list[i].status == InActive)
                fprintf(stream, "0, ");
            else
                fprintf(stream, "%d, ", table.list[i].prev[0]);
        }
        fprintf(stream, "\n");

        if (hashDtor(&table)) return EXIT_FAILURE;
    }

    fclose(stream);

    return EXIT_SUCCESS;
}