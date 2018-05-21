#pragma once
#include <stddef.h>
typedef int HashType;
#define MaxSize 1000

typedef int Keytype; 
typedef int Valtype; 
typedef size_t (*HashFun)(Keytype);

typedef struct HashElem{
    Keytype key;
    Valtype value;
    struct HashElem* next;

}HashElem;

typedef struct HashTable{
    HashElem* data[MaxSize];
    size_t size;
    HashFun func;

}HashTable;



void HashInit(HashTable *ht);
void HashDestroy(HashTable *ht);
void HashInsert(HashTable *ht,Keytype key,Valtype value);
int HashFind(HashTable *ht,Keytype key,Valtype* value);
void HashRemove(HashTable *ht,Keytype key);

