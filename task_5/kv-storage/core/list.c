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
  size_t size;
} List_t;

List_t *list_init()
{
  List_t *list = malloc(sizeof(List_t));

  if (nullptr != list) {
    Node_t *const dummy_node = calloc(1, sizeof(Node_t));

    if (nullptr != dummy_node) {
      list->first_node = dummy_node;
      list->last_node  = dummy_node;
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

bool list_push_front(List_t *const list, const void *const data, const size_t size)
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

        Node_t *const dummy     = list->first_node;
        Node_t *const old_first = dummy->next;

        new_node->prev = dummy;
        new_node->next = old_first;
        dummy->next    = new_node;

        if (nullptr != old_first) {
          old_first->prev = new_node;
        } else {
          list->last_node = new_node;
        }

        ++(list->size);
        ret = true;
      } else {
        free(new_node);
      }
    }
  }

  return ret;
}

bool list_pop_back(List_t *const list, void **const data, size_t *const size)
{
  bool ret = false;

  if ((nullptr != list) && (list->size > 0U) && (nullptr != data) && (nullptr != size)) {
    Node_t *const node_to_remove = list->last_node;

    *data = node_to_remove->data;
    *size = node_to_remove->data_size;

    Node_t *const prev_node = node_to_remove->prev;
    prev_node->next         = nullptr;
    list->last_node         = prev_node;

    free(node_to_remove);
    --(list->size);

    ret = true;
  }

  return ret;
}

bool list_pop_front(List_t *const list, void **const data, size_t *const size)
{
  bool ret = false;

  if ((nullptr != list) && (list->size > 0U) && (nullptr != data) && (nullptr != size)) {
    Node_t *const dummy          = list->first_node;
    Node_t *const node_to_remove = dummy->next;

    *data = node_to_remove->data;
    *size = node_to_remove->data_size;

    Node_t *const next_node = node_to_remove->next;

    dummy->next = next_node;
    if (nullptr != next_node) {
      next_node->prev = dummy;
    } else {
      list->last_node = dummy;
    }

    free(node_to_remove);
    --(list->size);

    ret = true;
  }

  return ret;
}

void list_data_free(void **const data)
{
  if ((nullptr != data) && (nullptr != *data)) {
    free(*data);
    *data = nullptr;
  }
}

bool list_find(
  const List_t *const list, const ListMatch_t match, const void *const key, const void **data_out)
{
  bool ret = false;

  data_out = nullptr;

  if ((nullptr != list) && (nullptr != match)) {
    // clang-format off
    for (const Node_t *node = list->first_node->next;
        (nullptr != node) && (nullptr == data_out);
        (node = node->next))
    // clang-format on
    {
      if (match(node->data, node->data_size, key)) {
        *data_out = node->data;
        ret       = true;
      }
    }
  }

  return ret;
}
