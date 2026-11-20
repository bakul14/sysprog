#pragma once

#include <stddef.h>

typedef struct List List_t;

List_t *list_init();

void list_deinit(List_t *const list);

bool list_push_back(List_t *const list, const void *const data, const size_t size);

typedef bool (*ListMatch_t)(const void *const data, const size_t size, const void *const key);

// clang-format off
bool list_find(
  const List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void **const data_out);
// clang-format on

// clang-format off
bool list_edit(
  List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void *const data,
  const size_t size);
// clang-format on

bool list_remove(List_t *const list, const ListMatch_t match, const void *const key);

// clang-format off
bool list_seek(
  List_t *const list,
  const ListMatch_t match,
  const void *const key,
  const void **const data_out);
// clang-format on

bool list_next(List_t *const list, const void **const data_out);

bool list_prev(List_t *const list, const void **const data_out);

typedef void (*ListVisit_t)(const void *const data, const size_t size, void *const context);

void list_foreach(const List_t *const list, const ListVisit_t visit, void *const context);
