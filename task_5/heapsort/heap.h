#pragma once

#include <stddef.h>
#include <stdint.h>

typedef enum HeapPolicy
{
  HEAP_POLICY_NOT_SET = 0,
  HEAP_POLICY_MIN,
  HEAP_POLICY_MAX,
} HeapPolicy_t;

void heap_sort(int64_t *const items, const size_t count, const HeapPolicy_t policy);
