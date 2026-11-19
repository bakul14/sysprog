#pragma once

#include "array.h"

typedef enum HeapPolicy
{
  HEAP_POLICY_NOT_SET = 0,
  HEAP_POLICY_MIN,
  HEAP_POLICY_MAX,
} HeapPolicy_t;

void heap_sort(Array_t *const array, const HeapPolicy_t policy);
