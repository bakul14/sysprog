#include "list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  struct Node *next;
  struct Node *prev;
  void *data;
  size_t data_size;
} Node_t;

typedef struct List {
  Node_t *first_node;
  Node_t *last_node;
  Node_t *current;
  size_t size;
} List_t;

List_t *list_init()
{
  List_t *list = malloc(sizeof(List_t));

  if (nullptr != list) {
    Node_t *const dummy_node = calloc(1U, sizeof(Node_t));

    if (nullptr != dummy_node) {
      list->first_node = dummy_node;
      list->last_node  = dummy_node;
      list->current    = dummy_node;
      list->size       = 0U;
    } else {
      free(list);
      list = nullptr;
    }
  }

  return list;
}

void list_deinit(List_t *const list)
{
  if (nullptr != list) {
    Node_t *current   = list->first_node;
    Node_t *next_node = nullptr;

    while (nullptr != current) {
      next_node = current->next;
      free(current->data);
      free(current);
      current = next_node;
    }

    free(list);
  }
}

bool list_push_back(List_t *const list, const void *const data, const size_t size)
{
  bool ret = false;

  if ((nullptr != list) && (nullptr != data) && (size > 0U)) {
    Node_t *new_node = malloc(sizeof(Node_t));

    if (nullptr != new_node) {
      void *const data_copy = malloc(size);

      if (nullptr != data_copy) {
        memcpy(data_copy, data, size);
        new_node->data      = data_copy;
        new_node->data_size = size;
        new_node->next      = nullptr;

        new_node->prev        = list->last_node;
        list->last_node->next = new_node;

        list->last_node = new_node;
        ++(list->size);

        ret = true;

      } else {
        free(new_node);
      }
    }
  }

  return ret;
}

static Node_t *find_node_(const List_t *const list, const ListMatch_t match, const void *const key)
{
  Node_t *ret = nullptr;

  if ((nullptr != list) && (nullptr != match)) {
    for (Node_t *node = list->first_node->next; (nullptr != node) && (nullptr == ret);
         node         = node->next)
    {
      if (match(node->data, node->data_size, key)) {
        ret = node;
      }
    }
  }

  return ret;
}

// clang-format off
bool list_find(
  const List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void **const data_out)
// clang-format on
{
  bool ret = false;

  if (nullptr != data_out) {
    const Node_t *const node = find_node_(list, match, key);

    *data_out = (nullptr != node) ? node->data : nullptr;
    ret       = (nullptr != node);
  }

  return ret;
}

// clang-format off
bool list_seek(
  List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void **const data_out)
// clang-format on
{
  bool ret = false;

  if (nullptr != data_out) {
    Node_t *const node = find_node_(list, match, key);

    if (nullptr != node) {
      list->current = node;
      *data_out     = node->data;
      ret           = true;
    }
  }

  return ret;
}

bool list_next(List_t *const list, const void **const data_out)
{
  bool ret = false;

  if ((nullptr != list) && (nullptr != data_out) && (nullptr != list->current->next)) {
    list->current = list->current->next;
    *data_out     = list->current->data;
    ret           = true;
  }

  return ret;
}

bool list_prev(List_t *const list, const void **const data_out)
{
  bool ret = false;

  // clang-format off
  if ((nullptr != list)                       &&
      (nullptr != data_out)                   &&
      (list->current != list->first_node)     &&
      (list->current->prev != list->first_node))
  // clang-format on
  {
    list->current = list->current->prev;
    *data_out     = list->current->data;
    ret           = true;
  }

  return ret;
}

// clang-format off
bool list_edit(
  List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void *const data,
  const size_t size)
// clang-format on
{
  bool ret = false;

  Node_t *const node = find_node_(list, match, key);

  if ((nullptr != node) && (nullptr != data) && (size > 0U)) {
    void *const data_copy = malloc(size);

    if (nullptr != data_copy) {
      memcpy(data_copy, data, size);
      free(node->data);
      node->data      = data_copy;
      node->data_size = size;
      ret             = true;
    }
  }

  return ret;
}

bool list_remove(List_t *const list, const ListMatch_t match, const void *const key)
{
  bool ret = false;

  Node_t *const node_to_remove = find_node_(list, match, key);

  if (nullptr != node_to_remove) {
    Node_t *const prev_node = node_to_remove->prev;
    Node_t *const next_node = node_to_remove->next;

    prev_node->next = next_node;

    if (nullptr != next_node) {
      next_node->prev = prev_node;
    } else {
      list->last_node = prev_node;
    }

    if (list->current == node_to_remove) {
      list->current = prev_node;
    }

    free(node_to_remove->data);
    free(node_to_remove);
    --(list->size);

    ret = true;
  }

  return ret;
}

void list_foreach(const List_t *const list, const ListVisit_t visit, void *const context)
{
  if ((nullptr != list) && (nullptr != visit)) {
    for (const Node_t *node = list->first_node->next; nullptr != node; node = node->next) {
      visit(node->data, node->data_size, context);
    }
  }
}
