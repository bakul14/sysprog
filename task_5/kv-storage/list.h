#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
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
{
  return (List *)malloc(sizeof(List));
}

inline void delete_list(List *const list)
{
  free(list);
}

inline bool push_front(List *const list, Node *const node)
{
  bool ret = false;

  if (nullptr != list && nullptr != node) {
    list->head->next = list->head;
    list->head->prev = node;
    list->head       = node;
    ret              = true;
  }

  return ret;
}

inline bool push_back(List *const list, Node *const node)
{
  bool ret = false;

  if (nullptr != list && nullptr != node) {
    list->tail->prev = list->tail;
    list->tail->next = node;
    list->tail       = node;
    ret              = true;
  }

  return ret;
}

#endif
