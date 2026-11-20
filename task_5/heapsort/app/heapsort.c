#include "heapsort.h"

#include "parser.h"
#include "../core/array.h"

#include <stdio.h>
#include <sysexits.h>

constexpr char k_invalid_input[] = "Invalid input: unexpected token or number out of range\n";
constexpr char k_out_of_memory[] = "Out of memory\n";
constexpr char k_read_error[]    = "Read error\n";

int hs_process_request(const HeapPolicy_t policy, const HsSource_t source, const char *const input)
{
  int ret = EX_SOFTWARE;

  const bool usage_ok = (HEAP_POLICY_NOT_SET != policy) && (nullptr != input);

  Array_t *const array = usage_ok ? array_init() : nullptr;

  if (!usage_ok) {
    ret = EX_USAGE;
  } else if (nullptr == array) {
    ret = EX_OSERR;
  } else {
    // clang-format off
    switch (source) {
      case HS_SOURCE_FILE:   { ret = parser_read_file(input, array);   break; }
      case HS_SOURCE_STRING: { ret = parser_read_string(input, array); break; }
      default:               { ret = EX_USAGE;                         break; }
    }
    // clang-format on
  }

  // clang-format off
  switch (ret) {
    case EX_OK:      { heap_sort(array, policy); parser_print(array); break; }
    case EX_USAGE:   {                                                break; }
    case EX_NOINPUT: { perror(input);                                 break; }
    case EX_DATAERR: { fputs(k_invalid_input, stderr);                break; }
    case EX_OSERR:   { fputs(k_out_of_memory, stderr);                break; }
    default:         { fputs(k_read_error, stderr);                   break; }
  }
  // clang-format on

  array_deinit(array);

  return ret;
}
