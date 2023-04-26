
#ifndef CONFIG_INCLUDED

typedef unsigned long long (*HashFunc_t)(const char*);

const int    MOD     = 1e3 +  7;
const int  POISON_i  = 1e9 +  7;
const int ERROR_HASH = 1e9 + 17;
const int BUFFER_SZ  =    1e6  ;

const int MAX_LIST_SIZE = 20000;

static const char *DELIM = " ,.;-%\"\'?!$()[]{}";

static const char *INPUT_FILE_NAME = "in/input.txt";

#define listCtor(LIST) {                                                    \
    _listCtor((LIST), #LIST, __FILE__, __PRETTY_FUNCTION__, __LINE__);     \
}

#define catchNullptr(POINTER) {                                                                                    \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);  \
        return EXIT_FAILURE;                                                                                          \
    }                                                                                                                  \
}

#define listDump(LIST) {                                             \
    listDump_((LIST), __PRETTY_FUNCTION__, __FILE__, __LINE__);       \
}

#define CONFIG_INCLUDED

#endif