#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct List List_t;

List_t *list_init();

void list_deinit(List_t *const list);

bool list_push_back(List_t *const list, const void *const data, const size_t size);

bool list_push_front(List_t *const list, const void *const data, const size_t size);

bool list_pop_back(List_t *const list, void **const data, size_t *const size);

bool list_pop_front(List_t *const list, void **const data, size_t *const size);

void list_data_free(void **const data);

typedef bool (*ListMatch_t)(const void *const data, const size_t size, const void *const key);

bool list_find(
  const List_t *const list, const ListMatch_t match, const void *const key, const void **data_out);

#endif
