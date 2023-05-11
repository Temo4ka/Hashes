#include <chrono>
#include <cmath>
#include "headers/test.h"

int test_diagrams(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName) {
    catchNullptr(     text     );
    catchNullptr(   hashFuncs  );
    catchNullptr(outputFileName);

    HashTable table = {};

    FILE* stream = fopen(outputFileName, "w");
    catchNullptr(stream);

    const char *hash_names[HASH_FUNC_NUM] = { "DumbHash", "FirstElem", "LengthHash", "SumHash", "RolHash", "RorHash", "GnuHash" };

    fprintf(stream, ", ");
    for (int cur = 0; cur < MOD; cur++) fprintf(stream, "%d, ", cur + 1);
    fprintf(stream, "\n");

    // fprintf(stderr, "%s\n", text -> buffer);

    for (int curFunc = 0; curFunc < HASH_FUNC_NUM; curFunc++) {
        hashCtor(&table, hashFuncs[curFunc]);
        initHashTable(&table, text -> buffer);

        float mid = (float) table.numOfElems / (float) MOD;
        float k = 0;
        fprintf(stream, "%s, ", hash_names[curFunc]);
        for (int i = 1; i < MOD; i++) {
            if (table.list[i].status == InActive) {
                fprintf(stream, "0, ");
                k += mid * mid; 
            } else {
                fprintf(stream, "%d, ", table.list[i].prev[0]);
                k += ((float) table.list[i].prev[0] - mid) * ((float) table.list[i].prev[0] - mid); 
            }
        }
        k /= MOD;
        fprintf(stream, "\n");
        fprintf(stderr, "%s -> %lg\n", hash_names[curFunc], sqrt(k));

        if (hashDtor(&table)) return EXIT_FAILURE;
    }

    fclose(stream);

    return EXIT_SUCCESS;
}

int test_speed(HashFunc_t hash, Text *text, const char *testWord) {
    catchNullptr(testWord);
    catchNullptr(  hash  );
    catchNullptr(  text  );

    HashTable table = {};
    hashCtor(&table, hash);
    initHashTable(&table, text -> buffer);

    // int hsh = hash(testWord) % MOD;
    // fprintf(stderr, "%d\n", table.list[hsh].prev[0]);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int cur = 0; cur < 10000000; cur++) {
        unsigned h = hash(testWord) % MOD;
		//printf("%llu\n", h);
        if (isInList(&(table.list[h]), testWord) == false) {
            fprintf(stdout, "Test Word is not in List :(\n");
                hashDtor(&table);
            return EXIT_FAILURE;
        }
    }

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	printf("millisecs: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    hashDtor(&table);

    return EXIT_SUCCESS;
}