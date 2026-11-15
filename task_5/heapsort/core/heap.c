#include "heap.h"

#include <stddef.h>

static inline bool is_higher_(
  const Array_t *const array, const HeapPolicy_t policy, const size_t lhs, const size_t rhs)
{
  const long long a = array_at(array, lhs);
  const long long b = array_at(array, rhs);

  return (HEAP_POLICY_MIN == policy) ? (a > b) : (a < b);
}

static void sift_down_(
  Array_t *const array, const HeapPolicy_t policy, const size_t count, size_t parent)
{
  for (size_t child = (2U * parent) + 1U; child < count; child = (2U * parent) + 1U) {
    if (((child + 1U) < count) && is_higher_(array, policy, child + 1U, child)) {
      ++child;
    }
    if (!is_higher_(array, policy, child, parent)) {
      break;
    }
    array_swap(array, parent, child);
    parent = child;
  }
}

void heap_sort(Array_t *const array, const HeapPolicy_t policy)
{
  const size_t count = array_size(array);

  for (size_t i = count / 2U; i > 0U; --i) {
    sift_down_(array, policy, count, i - 1U);
  }

  for (size_t end = count; end > 1U; --end) {
    array_swap(array, 0U, end - 1U);
    sift_down_(array, policy, end - 1U, 0U);
  }
}
