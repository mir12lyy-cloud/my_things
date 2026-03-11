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
void destroy_list(type##_list** bList){\
    if(bList == NULL || bList == NULL || *bList -> next == NULL) return; \
    type##_list* begin = *bList; \  
    type##_list* nList = NULL; \
    while(begin != NULL){\
        nList = begin -> next;\
        free(begin);\
        begin = nList; \
    } \
    *bList = NULL; \
}\
type##_list* push_back(type##_list** lList, type value){ \
    assert(bList != NULL && *bList != NULL); \
    type##_list* eList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(eList != NULL); \
    eList -> data = value; \
    eList -> prev = *lList; \
    eList -> next = NULL; \
    return eList; \
} \ 
void push_front(type##_list** bList, type value){ \
    assert(bList != NULL && *bList != NULL); \
    type##_list* nList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(nList != NULL); \
    nList -> data = value; \
    type##_list* fList = bList -> next; \
    fList -> prev = nList; \
    nList -> prev = *bList; \
    nList -> next = fList; \
    *bList -> next = nList; \
}\
void pop_front(type##_list** bList){\
    assert(bList != NULL && *bList == NULL); \
    if(*bList -> next = NULL) return; \
    type##_list* eList = *bList -> next;\
    type##_list* nList = *eList -> next;\
    *bList -> next = nList; \
    nList -> prev = *bList; \
    free(eList); \
    eList = NULL; \
}\
void pop_back(type##_list** eList){\
    assert(eList != NULL && *eList == NULL); \
    if(*eList -> prev = NULL) return; \
    type##_list* nList = *eList -> prev;\
    nList -> next = NULL; \
    free(*eList); \
    *eList = nList; \
}\
type##_list* get_value(type##_list* bList, size_t index){ \
    assert(bList != NULL);\
    type##_list* resPtr = NULL;\
    type##_list* nList = bList;\
    while(index--){\
        resPtr = nList -> next;\
        nList = resPtr;\
    } \
    return resPtr;\
} \
type##_list* rget_value(type##_list* rbList, size_t index){ \
    assert(rbList != NULL);\
    type##_list* resPtr = NULL;\
    type##_list* nList = rbList;\
    while(index--){\
        resPtr = nList -> prev;\
        nList = resPtr;\
    } \
    return resPtr;\
} \
size_t getSize(type##_list* bList){\
    assert(bList != NULL);\
    size_t size = 0;\
    for(type##_list* begin = bList; begin -> next != NULL; begin = begin -> next, ++size); \
    return size; \
}\


#define List_with_object(type) \
typedef struct type##_list{ \
    type* data; \
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
void destroy_list(type##_list** bList){\
    if(bList == NULL || bList == NULL || *bList -> next == NULL) return; \
    type##_list* begin = *bList; \  
    type##_list* nList = NULL; \
    while(begin != NULL){\
        nList = begin -> next;\
        free(begin -> data);\
        free(begin);\
        begin = nList; \
    } \
    *bList = NULL; \
}\
type##_list* push_back(type##_list** lList, type* value){ \
    assert(bList != NULL && *bList != NULL); \
    type##_list* eList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(eList != NULL); \
    eList -> data = value; \
    eList -> prev = *lList; \
    eList -> next = NULL; \
    return eList; \
} \ 
void push_front(type##_list** bList, type* value){ \
    assert(bList != NULL && *bList != NULL); \
    type##_list* nList = (type##_list*)malloc(sizeof(type##_list)); \
    assert(nList != NULL); \
    nList -> data = value; \
    type##_list* fList = bList -> next; \
    fList -> prev = nList; \
    nList -> prev = *bList; \
    nList -> next = fList; \
    *bList -> next = nList; \
}\
void pop_front(type##_list** bList){\
    assert(bList != NULL && *bList == NULL); \
    if(*bList -> next = NULL) return; \
    type##_list* eList = *bList -> next;\
    type##_list* nList = *eList -> next;\
    *bList -> next = nList; \
    nList -> prev = *bList; \
    free(eList -> data); \
    free(eList); \
    eList = NULL; \
}\
void pop_back(type##_list** eList){\
    assert(eList != NULL && *eList == NULL); \
    if(*eList -> prev = NULL) return; \
    type##_list* nList = *eList -> prev;\
    nList -> next = NULL; \
    free(*eList); \
    *eList = nList; \
}\
type##_list* get_value(type##_list* bList, size_t index){ \
    assert(bList != NULL);\
    type##_list* resPtr = NULL;\
    type##_list* nList = bList;\
    while(index--){\
        resPtr = nList -> next;\
        nList = resPtr;\
    } \
    return resPtr;\
} \
type##_list* rget_value(type##_list* rbList, size_t index){ \
    assert(rbList != NULL);\
    type##_list* resPtr = NULL;\
    type##_list* nList = rbList;\
    while(index--){\
        resPtr = nList -> prev;\
        nList = resPtr;\
    } \
    return resPtr;\
} \
size_t getSize(type##_list* bList){\
    assert(bList != NULL);\
    size_t size = 0;\
    for(type##_list* begin = bList; begin -> next != NULL; begin = begin -> next, ++size); \
    return size; \
}\