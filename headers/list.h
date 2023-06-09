#include "config.h"
#include "listType.h"
#include <cstdio>
#include <string.h>

enum ListErrors {
             ListIsOk         =       0,
            ListIsNull        = 1 <<  0,
            ListIsFull        = 1 <<  1, 
            ListIsEmpty       = 1 <<  2,
          ListHeadErase       = 1 <<  3,
          ListDataIsNull      = 1 <<  4,
          ListNextIsNull      = 1 <<  5,
          ListWrongIndex      = 1 <<  6,
          ListPrevIsNull      = 1 <<  7,
          ListIsInActive      = 1 <<  8,
         ListPoisonInData     = 1 <<  9,
         ListFreeBlocksErr    = 1 << 10,
       ListDoubleDestruction  = 1 << 11,
      ListDoubleConstruction  = 1 << 12,
     ListGraphVizExecutionErr = 1 << 13,
};

enum Status {
    InActive = 0,
     Active  = 1,
};

enum Life {
    Bitter = 0,  
    Sweet  = 1
};

struct listInfo {
    size_t  line   =    0   ;

    char *  name   = nullptr;
    char *  file   = nullptr;
    char * pointer = nullptr;
    char *function = nullptr;
};


struct List {
    Elem_t  *data   = nullptr ;
    size_t  *next   = nullptr ;
    size_t  *prev   = nullptr ;

    listInfo info   =    {}   ;

    size_t   head   =    0    ;
    size_t nextFree =    0    ;
    bool    status  = InActive;
    bool  sweetLife =  Active ;
};

int _listCtor(List *list, const char * name, const char *file, const char *function, size_t line);

int listDtor(List *list);

int listLogicInsert(List *list, size_t ind, Elem_t val, int *err = nullptr);

int listPhysInsert (List *list, size_t ind, Elem_t val, int *err = nullptr) ;

int listLogicErase (List *list, size_t ind);

int listPhysErase  (List *list, size_t ind);

int  listGetPos    (List *list, size_t ind);

int  listVerify    (List *list);

int  listPrint     (List *list); 

int listPushBack(List *list, Elem_t val, int *err = nullptr);

int listPushFront(List *list, Elem_t val, int *err);

void printErrorMessage(int error);

void listDump_(List *list, const char* functionName, const char *fileName, size_t line);

void listLogClose() ;

int listGraphVizLogicDump(List *list, FILE *stream, int num);

int listGraphVizPhysDump(List *list, const char *fileName, int cmd);

void vizLogClose();
