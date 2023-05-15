#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include "../headers/test.h"

int test_diagrams(Text *text, const char* outputFileName) {
    catchNullptr(     text     );
    catchNullptr(outputFileName);

	WordsArray words = {};
    HashTable  table = {};

	if (textToWords(text, &words)) return EXIT_FAILURE;

    FILE* stream = fopen(outputFileName, "w");
    catchNullptr(stream);

	HashFunc_t    hashes[HASH_FUNC_NUM]   = { DumbHash, FirstByteHash, StrLenHash, SumHash, RotlHash, RotrHash, GnuHash };

	const char *hash_names[HASH_FUNC_NUM] = { "DumbHash", "FirstByteHash", "LengthHash", "SumHash", "RolHash", "RorHash", "GnuHash" };

    fprintf(stream, ", ");
    for (int cur = 0; cur < MODULE; cur++) fprintf(stream, "%d, ", cur + 1);
    fprintf(stream, "\n");

    // fprintf(stderr, "%s\n", text -> buffer);

    for (int curFunc = 0; curFunc < HASH_FUNC_NUM; curFunc++) {
        hashCtor(&table, hashes[curFunc]);
        initHashTable(&table, &words);

		catchNullptr(table.list);

        fprintf(stream, "%s, ", hash_names[curFunc]);
        for (int i = 1; i < MODULE; i++) {
            if (table.list[i].status == InActive)
                fprintf(stream, "0, ");
            else
                fprintf(stream, "%zd, ", table.list[i].prev[0]);
        }
        fprintf(stream, "\n");

        if (hashDtor(&table)) return EXIT_FAILURE;
    }

    fclose(stream);

	if (WordsArrayDtor(&words)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int test_speed(HashFunc_t hash, Text *text) {
    catchNullptr(  hash  );
    catchNullptr(  text  );

	WordsArray words = {};
	HashTable  table = {};

	if (textToWords(text, &words)) return EXIT_FAILURE;
	catchNullptr(words.array);

    hashCtor(&table, hash);
    initHashTable(&table, &words);	

	float results[50] = {};
	float    mid      =  0;

	//for (int i = 0 ; i < 50 ; i++) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		for (int cur = 0; cur < 10000000; cur++) {
			char *curWord = words.array[cur % words.numOfWords];
			if (isInHashTable(&table, curWord) == nullptr) {
				fprintf(stdout, "TestWord is not in List :(\n");
				WordsArrayDtor(&words);
				hashDtor(&table);
				return EXIT_FAILURE;
			}
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		//results[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		printf("millisecs: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

		//if (i >= 10)
			//mid += results[i];
	//}
	/*float dev = 0;
	mid = mid / (float) 40;
	for (int i = 10; i < 50; i++)
		dev += (results[i] - mid) * (results[i] - mid);
	dev = dev / (float) 40;
	printf("mid: %lg\n", mid);
	printf("deviation: %lg\n", sqrt(dev));*/

	WordsArrayDtor(&words);
    hashDtor(&table);

    return EXIT_SUCCESS;
}