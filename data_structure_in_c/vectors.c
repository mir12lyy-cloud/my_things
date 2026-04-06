#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define NORMAL_SIZE 1000

#define Vector(type) \
typedef struct{ \
    type* data_; \
    type* elem_end_; \
    type* end_; \
}type##_vector; \
type##_vector creatVector(const size_t size){ \
    size_t proportion_ = (size + NORMAL_SIZE - 1) / NORMAL_SIZE; \
    size_t capacity = 0; \
    if(!proportion_) capacity = NORMAL_SIZE; \
    else capacity = proportion_ * NORMAL_SIZE; \
    type##_vector returnVector; \
    returnVector.data_ = malloc(capacity * sizeof(type)); \
    if(returnVector.data_ == NULL){ \
        printf("Fail.\n"); \
        returnVector.elem_end_ = NULL; \
        returnVector.end_ = NULL; \
        return returnVector; \
    } \
    returnVector.end_ = returnVector.data_ + capacity; \
    returnVector.elem_end_ = returnVector.data_ + size; \
    return returnVector; \
} \
void destroyVector(type##_vector* aVector){ \
    if(aVector == NULL){ \
        printf("Illegal input.\n"); \
        return; \
    } \
    if(aVector -> data_ == NULL){ \
        printf("Fail.\n"); \
        return; \
    } \
    free(aVector -> data_); \
    aVector -> elem_end_ = NULL; \
    aVector -> end_ = NULL; \
    aVector -> data_ = NULL; \
} \
type* begin(const type##_vector* aVector) {return aVector -> data_;}\
type* end(const type##_vector* aVector) {return aVector -> elem_end_;}\
size_t getSize(const type##_vector* aVector) {return aVector -> elem_end_ - aVector -> data_;}\
size_t getCapacity(const type##_vector* aVector) {return aVector -> end_ - aVector -> data_;}\
void reserve(type##_vector* aVector, const size_t capacity){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newsize = getSize(aVector);\
    if(getCapacity(aVector) >= capacity) return;\
    size_t alloc = ((capacity + NORMAL_SIZE - 1) / NORMAL_SIZE) * NORMAL_SIZE;\
    type* newto = realloc(aVector -> data_, alloc * sizeof(type));\
    if(newto == NULL){\
        printf("Fail to reserve.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
    aVector -> end_ = aVector -> data_ + alloc;\
}\
void shrink(type##_vector* aVector){\
     if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newsize = getSize(aVector);\
    type* newto = realloc(aVector -> data_, getSize(aVector) * sizeof(type));\
    if(newto == NULL){\
        printf("Fail to shrink.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
    aVector -> end_ = aVector -> data_ + newsize;\
}\
void expand(type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newcapcity = 2 * getCapacity(aVector), newsize = getSize(aVector); \
    type* newto = realloc(aVector -> data_, newcapcity * sizeof(type));\
    if(newto == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> end_ = aVector -> data_ + newcapcity;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
}\
void resize(type##_vector* aVector, const size_t newsize){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail to resize\n");\
        return;\
    }\
    if(newsize <= getCapacity(aVector)){\
        aVector -> elem_end_ = aVector -> data_ + newsize;\
        return;\
    }\
    reserve(aVector, newsize);\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
}\
void clear(type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail to clear\n");\
        return;\
    }\
    aVector -> elem_end_ = aVector -> data_;\
}\
void push_back(type##_vector* aVector, const type value){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail\n");\
        return;\
    }\
    if(aVector -> end_ == aVector -> elem_end_) expand(aVector);\
    if(aVector -> end_ == aVector -> elem_end_){\
        printf("Fail to push\n");\
        return;\
    }\
    *(aVector -> elem_end_) = value;\
    ++(aVector -> elem_end_);\
}\
void pop_back(type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail\n");\
        return;\
    }\
    if(aVector -> elem_end_ == aVector -> data_){\
        printf("Fail to pop\n");\
        return;\
    }\
    --(aVector -> elem_end_);\
}\

#define Vector_with_object(type) \
typedef struct{ \
    type** data_; \
    type** elem_end_; \
    type** end_; \
}object_##type##_vector; \
object_##type##_vector creatVector(const size_t size){ \
    size_t proportion_ = (size + NORMAL_SIZE - 1) / NORMAL_SIZE; \
    size_t capacity = 0; \
    if(!proportion_) capacity = NORMAL_SIZE; \
    else capacity = proportion_ * NORMAL_SIZE; \
    object_##type##_vector returnVector; \
    returnVector.data_ = (type**)malloc(capacity * sizeof(type*)); \
    if(returnVector.data_ == NULL){ \
        printf("Fail.\n"); \
        returnVector.elem_end_ = NULL; \
        returnVector.end_ = NULL; \
        return returnVector; \
    } \
    returnVector.end_ = returnVector.data_ + capacity; \
    returnVector.elem_end_ = returnVector.data_ + size; \
    return returnVector; \
} \
void destroyVector(object_##type##_vector* aVector){ \
    if(aVector == NULL){ \
        printf("Illegal input.\n"); \
        return; \
    } \
    if(aVector -> data_ == NULL){ \
        printf("Fail.\n"); \
        return; \
    } \
    for(type* it = data_; it != end_; ++it) free(*it); \
    free(aVector -> data_); \
    aVector -> elem_end_ = NULL; \
    aVector -> end_ = NULL; \
    aVector -> data_ = NULL; \
} \
type* begin(const object_##type##_vector* aVector) {return aVector -> data_;}\
type* end(const object_##type##_vector* aVector) {return aVector -> elem_end_;}\
size_t getSize(const object_##type##_vector* aVector) {return aVector -> elem_end_ - aVector -> data_;}\
size_t getCapacity(const object_##type##_vector* aVector) {return aVector -> end_ - aVector -> data_;}\
void reserve(object_##type##_vector* aVector, const size_t capacity){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newsize = getSize(aVector);\
    if(getCapacity(aVector) >= capacity) return;\
    size_t alloc = ((capacity + NORMAL_SIZE - 1) / NORMAL_SIZE) * NORMAL_SIZE;\
    type** newto = (type**)realloc(aVector -> data_, alloc * sizeof(type*));\
    if(newto == NULL){\
        printf("Fail to reserve.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
    aVector -> end_ = aVector -> data_ + alloc;\
}\
void shrink(object_##type##_vector* aVector){\
     if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newsize = getSize(aVector);\
    type* newto = realloc(aVector -> data_, getSize(aVector) * sizeof(type));\
    if(newto == NULL){\
        printf("Fail to shrink.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
    aVector -> end_ = aVector -> data_ + newsize;\
}\
void expand(object_##type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    size_t newcapcity = 2 * getCapacity(aVector), newsize = getSize(aVector); \
    type* newto = realloc(aVector -> data_, newcapcity * sizeof(type));\
    if(newto == NULL){\
        printf("Fail.\n");\
        return;\
    }\
    aVector -> data_ = newto;\
    aVector -> end_ = aVector -> data_ + newcapcity;\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
}\
void resize(object_##type##_vector* aVector, const size_t newsize){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail to resize\n");\
        return;\
    }\
    if(newsize <= getCapacity(aVector)){\
        aVector -> elem_end_ = aVector -> data_ + newsize;\
        return;\
    }\
    reserve(aVector, newsize);\
    aVector -> elem_end_ = aVector -> data_ + newsize;\
}\
void clear(object_##type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail to clear\n");\
        return;\
    }\
    aVector -> elem_end_ = aVector -> data_;\
}\
void push_back(type##_vector* aVector, const type value){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail\n");\
        return;\
    }\
    if(aVector -> end_ == aVector -> elem_end_) expand(aVector);\
    if(aVector -> end_ == aVector -> elem_end_){\
        printf("Fail to push\n");\
        return;\
    }\
    *(aVector -> elem_end_) = value;\
    ++(aVector -> elem_end_);\
}\
void pop_back(object_##type##_vector* aVector){\
    if(aVector == NULL){\
        printf("Illegal input.\n");\
        return;\
    }\
    if(aVector -> data_ == NULL){\
        printf("Fail\n");\
        return;\
    }\
    if(aVector -> elem_end_ == aVector -> data_){\
        printf("Fail to pop\n");\
        return;\
    }\
    --(aVector -> elem_end_);\
    free(*(aVector -> elem_end_));\
}\

Vector(char)

int main(){
    char_vector myvector = creatVector(10);
    for(char* ptr = begin(&myvector); ptr != end(&myvector); ++ptr) scanf(" %c", ptr);
    for(char* ptr = begin(&myvector); ptr != end(&myvector); ++ptr) printf("%c ", *ptr);
    for(int i = 11; i <= 20; i++) push_back(&myvector, 'a');
    printf("\n");
    for(char* ptr = begin(&myvector); ptr != end(&myvector); ++ptr) printf("%c ", *ptr);
    printf("\n");
    push_back(&myvector, '\0');
    printf("%s", begin(&myvector));
    destroyVector(&myvector);
    return 0;
}
