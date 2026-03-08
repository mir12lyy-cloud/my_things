#include<stdlib.h>

#define List(type) \
typedef struct type##_list{ \
    type data; \
    struct type##_list *prev; \
    struct type##_list *next; \
}type##_list; \
type##_list *head = NULL, *tail = NULL; \


