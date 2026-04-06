#include<stdlib.h>

#define List(type)\
typedef struct type##_list{ \
    type value; \
    struct type##_list* next; \
}type##_list; \
type##_list *ptr, *head, *end; \
ptr = malloc(sizeof(type##_list)); \
head = ptr, end = ptr; \
head -> next = NULL; \


