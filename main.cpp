#include "headers/test.h"

int main() {
    HashFunc_t hashes[HASH_FUNC_NUM] = { DumbHash, FirstElemHash, StrLenHash, SumHash, RotlHash, RotrHash, GnuHash };

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    /*if (test_diagrams(hashes, &text, OUTPUT_FILE_NAME))
        fprintf(stderr, "Failure\n");
    else
        fprintf(stderr, "Succes\n");*/
	
	char *testWord = (char *) calloc(MAX_DATA_SIZE, sizeof(char));
	catchNullptr(testWord);
	testWord = strcpy(testWord, "Courtier");
	catchNullptr(testWord);

    if (test_speed(CRC32Hash, &text, testWord))
		fprintf(stderr, "Failure\n");
	else
		fprintf(stderr, "Succes\n");

    return 0;
}