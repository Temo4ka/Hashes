#include "headers/test.h"

int main() {
    HashFunc_t hashes[HASH_FUNC_NUM] = { hash_1, hash_2, hash_3, hash_4, hash_5, hash_6, hash_7 };

    Text text = {};
    if (TextCtor(&text, INPUT_FILE_NAME)) { 
        fprintf(stderr, "Error here!\n");
        return EXIT_FAILURE;
    }

    if (test(hashes, &text, OUTPUT_FILE_NAME))
        fprintf(stderr, "Failure\n");
    else
        fprintf(stderr, "Succes\n");

    return 0;
}