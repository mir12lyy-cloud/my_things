#include<stdlib.h>
#include<assert.h>

#define List(type) \
typedef struct type##_list{ \
    type data; \
    struct type##_list *prev; \
    struct type##_list *next; \
}type##_list; \
\
type##_list* creatList(){ \
    type##_list* bList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(bList != NULL); \
    bList -> next = NULL; bList -> prev = NULL; \
    return bList; \
}\
void push_back(type##_list* lList, type value){ \
    type##_list* eList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(eList != NULL); \
    eList -> data = value; \
    eList -> prev = lList; \
    eList -> next = NULL; \
} \ 


