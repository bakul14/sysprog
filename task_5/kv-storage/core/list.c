#include "list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
  void *next;
  void *prev;
  void *data;
} Node_t;

typedef struct List {
  Node_t *first_node;
  Node_t *last_node;
  size_t size;
} List_t;

List_t *list_init()
{
  List_t *const list = malloc(sizeof(List_t));

  if (nullptr != list) {
    list->first_node = nullptr;
    list->last_node  = nullptr;
    list->size       = 0U;
  }

  return list;
}

void list_deinit(List_t *const list)
{
  while (list->size > 0U) {
    free(list->first_node->next);
    --(list->size);
  }
}

// inline void delete_list(List_t *const list)
// { free(list); }

// inline bool push_front(List_t *const list, Node_t *const node)
// {
//   bool ret = false;

//   if (nullptr != list && nullptr != node) {
//     list->head->next = list->head;
//     list->head->prev = node;
//     list->head       = node;
//     ret              = true;
//   }

//   return ret;
// }

// inline bool push_back(List_t *const list, Node_t *const node)
// {
//   bool ret = false;

//   if (nullptr != list && nullptr != node) {
//     list->tail->prev = list->tail;
//     list->tail->next = node;
//     list->tail       = node;
//     ret              = true;
//   }

//   return ret;
// }
