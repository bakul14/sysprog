#include "heap.h"

static inline bool is_higher_(const int64_t a, const int64_t b, const HeapPolicy_t policy)
{
  return (HEAP_POLICY_MIN == policy) ? (a > b) : (a < b);
}

static inline void swap_(int64_t *const a, int64_t *const b)
{
  const int64_t tmp = *a;
  *a                = *b;
  *b                = tmp;
}

static void sift_down_(
  int64_t *const items, const size_t count, const HeapPolicy_t policy, size_t parent)
{
  for (size_t child = (2U * parent) + 1U; child < count; child = (2U * parent) + 1U) {
    if (((child + 1U) < count) && is_higher_(items[child + 1U], items[child], policy)) {
      ++child;
    }
    if (!is_higher_(items[child], items[parent], policy)) {
      break;
    }
    swap_(&items[parent], &items[child]);
    parent = child;
  }
}

void heap_sort(int64_t *const items, const size_t count, const HeapPolicy_t policy)
{
  const bool policy_ok = (HEAP_POLICY_MIN == policy) || (HEAP_POLICY_MAX == policy);

  const size_t n = (policy_ok && (nullptr != items)) ? count : 0U;

  for (size_t i = n / 2U; i > 0U; --i) {
    sift_down_(items, n, policy, i - 1U);
  }

  for (size_t end = n; end > 1U; --end) {
    swap_(&items[0U], &items[end - 1U]);
    sift_down_(items, end - 1U, policy, 0U);
  }
}
