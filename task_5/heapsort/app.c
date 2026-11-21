#include "app.h"

#include "parser.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

constexpr char k_invalid_input[] = "Invalid input: unexpected token or number out of range\n";
constexpr char k_out_of_memory[] = "Out of memory\n";
constexpr char k_read_error[]    = "Read error\n";

static void print_(const int64_t *const items, const size_t count)
{
  for (size_t i = 0U; i < count; ++i) {
    printf((0U == i) ? "%" PRId64 : " %" PRId64, items[i]);
  }

  putchar('\n');
}

static void report_error_(const int code, const char *const filepath)
{
  // clang-format off
  switch (code) {
    case EX_USAGE:   {                                 break; }
    case EX_NOINPUT: { perror(filepath);               break; }
    case EX_DATAERR: { fputs(k_invalid_input, stderr); break; }
    case EX_OSERR:   { fputs(k_out_of_memory, stderr); break; }
    default:         { fputs(k_read_error, stderr);    break; }
  }
  // clang-format on
}

int app_process_request(
  const HeapPolicy_t policy, const char *const filepath, const char *const numbers)
{
  int ret        = EX_USAGE;
  int64_t *items = nullptr;
  size_t count   = 0U;

  const bool usage_ok =
    (HEAP_POLICY_NOT_SET != policy) && ((nullptr == filepath) != (nullptr == numbers));

  if (usage_ok) {
    ret = (nullptr != filepath) ? parser_read_file(filepath, &items, &count)
                                : parser_read_string(numbers, &items, &count);
  }

  if (EX_OK == ret) {
    heap_sort(items, count, policy);
    print_(items, count);
  } else {
    report_error_(ret, filepath);
  }

  free(items);

  return ret;
}
