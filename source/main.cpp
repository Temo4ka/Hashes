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

    if (test_speed(CRC32Hash, &text))
	fprintf(stderr, "Failure\n");
    else
	fprintf(stderr, "Succes\n");

    if (TextDtor(&text)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
