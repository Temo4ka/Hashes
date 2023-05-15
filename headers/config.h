
#ifndef CONFIG_INCLUDED

typedef unsigned long long (*HashFunc_t)(const char*);

const int    POISON_i    = 1e9 +  7;
const int   ERROR_HASH   = 1e9 + 17;
const int   BUFFER_SZ    =    1e6  ;
const int HASH_FUNC_NUM  =    07   ;
const int MAX_DATA_SIZE  =    32   ;
const int MAX_STRING_NUM =   5000  ;
const int    NOT_FOUND   =    -1   ;

const int MAX_LIST_SIZE =    20   ;

const unsigned long long  MOD  = 3e3 +  7;
const unsigned long long SHIFT = sizeof(long long) * 8 - 1; 

static const char *DELIM = " ,.;-%\"\'?!$()[]{}\n";

static const char *OUTPUT_FILE_NAME = "out/output.csv";
static const char * INPUT_FILE_NAME =  "in/input.txt" ;

#define listCtor(LIST) {                                                    \
    _listCtor((LIST), #LIST, __FILE__, __FUNCSIG__, __LINE__);				 \
}

#define catchNullptr(POINTER) {                                                                                    \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __FUNCSIG__, __FILE__, __LINE__);			 \
        return EXIT_FAILURE;                                                                                          \
    }                                                                                                                  \
}

#define listDump(LIST) {                                             \
    listDump_((LIST), __PRETTY_FUNCTION__, __FILE__, __LINE__);       \
}

#define CONFIG_INCLUDED

#endif