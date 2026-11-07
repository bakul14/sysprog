#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
  void *next;
  void *prev;
  void *data;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  size_t size;
} List;

inline List *create_list()
{ return (List *)malloc(sizeof(List)); }

inline void delete_list(List *const list)
{ free(list); }

#endif
