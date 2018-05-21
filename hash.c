#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST_HEADER printf("\n=====================%s====================\n",__FUNCTION__)

size_t HashDefault(Keytype key)
{
    return key%MaxSize;
}
void HashInit(HashTable *ht)
{
    if(ht==NULL)
    {
        return;
    }
    ht->size=0;
    ht->func=HashDefault;
    size_t i=0;
    for(i=0;i<MaxSize;i++)
    {
        ht->data[i]=NULL;
    }
}

void DestroyNode(HashElem* cur)
{
    free(cur);
    cur=NULL;
}
void HashDestroy(HashTable *ht)
{
    if(ht==NULL)
    {
        return;
    }
    if(ht->size==0)
    {
        return;
    }
    ht->size=0;
    ht->func=NULL;
    size_t i=0;
    for(i=0;i<MaxSize;i++)
    {
        HashElem* cur=ht->data[i];
        if(cur==NULL)
        {
            continue;
        }
        while(cur!=NULL)
        {
            HashElem* pre=cur;
            DestroyNode(cur);
            cur=pre->next;
        }
    }
}
HashElem* CreatNode(Keytype key,Valtype value)
{
    HashElem* new_node=(HashElem* )malloc(sizeof(HashElem));
    new_node->key=key;
    new_node->value=value;
    new_node->next=NULL;

    return new_node;
}
void HashInsert(HashTable *ht,Keytype key,Valtype value)
{
    if(ht==NULL)
    {
        return;
    }
    if(ht->size>=MaxSize)
    {
        return;
    }
    size_t offset=ht->func(key);
    HashElem* cur=ht->data[offset];
    while(1)
    {
        while(cur!=NULL)
        {
            if(cur->key==key)
            {
                return;
            }
            cur=cur->next;
        }
        HashElem* new_elem=CreatNode(key,value);
        new_elem->next=ht->data[offset];
        ht->data[offset]=new_elem;
        break;
    }
    ht->size++;
}
int HashFind(HashTable *ht,Keytype key,Valtype* value)
{
    if(ht==NULL)
    {
        return 0;
    }
    if(ht->size==0)
    {
        return 0;
    }
    size_t offset=ht->func(key);
    HashElem* cur=ht->data[offset];
    while(cur!=NULL)
    {
        if(cur->key==key)
        {
            *value=cur->value;
            return 1;
        }
        cur=cur->next;
    }
    return 0;
}

void HashRemove(HashTable *ht,Keytype key)
{
    if(ht==NULL)
    {
        return;
    }
    if(ht->size==0)
    {
        return;
    }
    size_t offset=ht->func(key);
    HashElem* cur=ht->data[offset];
    HashElem* pre=NULL;
    while(cur!=NULL)
    {
        if(cur->key==key)
        {
            break;
        }
        pre=cur;
        cur=cur->next;
    }
    if(cur==NULL)
    {
        return;
    }
    if(pre==NULL)
    {
        HashElem* tmp=ht->data[offset];
        ht->data[offset]=tmp->next;
        DestroyNode(tmp);
    }
    else
    {
        pre->next=cur->next;
        DestroyNode(cur);
    }
}
///////////////////////////////
//测试
///////////////////////////////
void TestInit()
{   
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht);
    printf("size expect 0,actual %lu\n",ht.size);
    HashDestroy(&ht);
    printf("size expect 0,actual %lu\n",ht.size);
}
void HashPrint(HashTable* ht,const char* msg)
{
    if(ht==NULL)
    {
        return;
    }
    printf("%s\n",msg);
    size_t i=0;
    for(i=0;i<MaxSize;i++)
    {
        HashElem* cur=ht->data[i];
        if(cur==NULL)
        {
            continue;
        }
        while(cur!=NULL)
        {
            printf("[%lu: %d,%d]",i,cur->key,cur->value);
            cur=cur->next;
        }
    }
    printf("\n");
}
void TestInsert()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht);
    HashInsert(&ht,1,1000);
    HashInsert(&ht,1,2000);
    HashInsert(&ht,2,3000);
    HashInsert(&ht,1001,4000);
    HashInsert(&ht,1002,5000);
    HashPrint(&ht,"插入若干个元素");

}
void TestFind()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht);
    HashInsert(&ht,1,1000);
    HashInsert(&ht,1,1000);
    HashInsert(&ht,1001,2000);
    HashInsert(&ht,2,3000);
    HashInsert(&ht,1002,4000);
    HashPrint(&ht,"插入若干个元素");
    Valtype value;
    int ret=HashFind(&ht,1,&value);
    printf("ret expect 1,actual %d\n",ret);
    printf("value expect 1000,actual %d\n",value);
    ret=HashFind(&ht,3,&value);
    printf("ret expect 0,actual %d\n",ret);


}
void TestRemove()
{
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht);
    HashInsert(&ht,1,1000);
    HashInsert(&ht,1,1000);
    HashInsert(&ht,1001,2000);
    HashInsert(&ht,2,3000);
    HashInsert(&ht,1002,4000);
    HashPrint(&ht,"插入若干个元素");
    HashRemove(&ht,1);
    HashPrint(&ht,"删除一个元素");

}

int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
