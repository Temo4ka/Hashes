<<<<<<< HEAD:source/main.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "../headers/test.h"

//extern "C" unsigned long long GnuHashAsm(const char *); //x64
//extern "C" unsigned long long GnuHashMasm86(const char*); //x86


int main() {
    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    if (test_diagrams(&text, OUTPUT_FILE_NAME))
        fprintf(stderr, "Failure\n");
    else
        fprintf(stderr, "Succes\n");

    if (test_speed(FastCRC32Hash, &text))
		fprintf(stderr, "Failure\n");
	else
		fprintf(stderr, "Succes\n");

	if (TextDtor(&text)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
=======
#define _CRT_SECURE_NO_WARNINGS
#include "test.h"

//extern "C" unsigned long long GnuHashAsm(const char *); //x64
//extern "C" unsigned long long GnuHashMasm86(const char*); //x86


int main() {
	HashFunc_t hashes[HASH_FUNC_NUM] = { DumbHash, FirstElemHash, StrLenHash, SumHash, RotlHash, RotrHash, GnuHash };

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    /*if (test_diagrams(hashes, &text, OUTPUT_FILE_NAME, HASH_FUNC_NUM))
        fprintf(stderr, "Failure\n");
    else
        fprintf(stderr, "Succes\n");*/

    if (test_speed(FastCRC32Hash, &text))
		fprintf(stderr, "Failure\n");
	else
		fprintf(stderr, "Succes\n");

	if (TextDtor(&text)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
>>>>>>> 4a0a211e26fa9b71d07de0bc5cf7e43c6228120f:main.cpp
}