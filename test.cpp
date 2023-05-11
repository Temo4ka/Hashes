#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include "test.h"

int test_diagrams(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName) {
    catchNullptr(     text     );
    catchNullptr(   hashFuncs  );
    catchNullptr(outputFileName);

	WordsArray words = {};
    HashTable  table = {};

	if (textToWords(text, &words)) return EXIT_FAILURE;

    FILE* stream = fopen(outputFileName, "w");
    catchNullptr(stream);

    const char *hash_names[HASH_FUNC_NUM] = { "DumbHash", "FirstElem", "LengthHash", "SumHash", "RolHash", "RorHash", "GnuHash" };

    fprintf(stream, ", ");
    for (int cur = 0; cur < MOD; cur++) fprintf(stream, "%d, ", cur + 1);
    fprintf(stream, "\n");

    // fprintf(stderr, "%s\n", text -> buffer);

    for (int curFunc = 0; curFunc < HASH_FUNC_NUM; curFunc++) {
        hashCtor(&table, hashFuncs[curFunc]);
        initHashTable(&table, &words);

        fprintf(stream, "%s, ", hash_names[curFunc]);
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

int test_speed(HashFunc_t hash, Text *text) {
    catchNullptr(  hash  );
    catchNullptr(  text  );

	WordsArray words = {};
	HashTable  table = {};

	if (textToWords(text, &words)) return EXIT_FAILURE;

    hashCtor(&table, hash);
    initHashTable(&table, &words);
	
	catchNullptr(words.array);

    // int hsh = hash(testWord) % MOD;
    // fprintf(stderr, "%d\n", table.list[hsh].prev[0]);

	float results[50] = {};
	float    mid    =  0;

	for (int i = 0 ; i < 50 ; i++) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		for (int cur = 0; cur < 10000000; cur++) {
			char *curWord = words.array[cur % words.numOfWords];
			unsigned h = hash(curWord) % MOD;
			//printf("%llu\n", h);
			if (isInList(&(table.list[h]), curWord) == false) {
				fprintf(stdout, "TestWord is not in List :(\n");
					hashDtor(&table);
				return EXIT_FAILURE;
			}
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		printf("millisecs: %lg\n", results[i]);

		if (i >= 10)
			mid += results[i];
	}
	float dev = 0;
	mid = mid / (float) 40;
	for (int i = 10; i < 50; i++)
		dev += (results[i] - mid) * (results[i] - mid);
	dev = dev / (float) 40;
	printf("mid: %lg\n", mid);
	printf("deviation: %lg\n", sqrt(dev));


    hashDtor(&table);

    return EXIT_SUCCESS;
}