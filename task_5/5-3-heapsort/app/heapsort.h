#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../core/heap.h"

typedef enum HsSource
{
  HS_SOURCE_NOT_SET = 0,
  HS_SOURCE_FILE,
  HS_SOURCE_STRING,
} HsSource_t;

/**
 * @brief Read numbers, sort them and print the result to stdout.
 *
 * @param[in] policy  Sort order, must not be HEAP_POLICY_NOT_SET.
 * @param[in] source  Kind of @p input, must not be HS_SOURCE_NOT_SET.
 * @param[in] input   HS_SOURCE_FILE   - path to a file with numbers;
 *                    HS_SOURCE_STRING - string with numbers.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK       Numbers have been sorted and printed.
 * @retval EX_USAGE    Invalid request, nothing is printed.
 * @retval EX_NOINPUT  Input file could not be opened.
 * @retval EX_DATAERR  Unexpected token or number out of range.
 * @retval EX_OSERR    Out of memory.
 * @retval EX_IOERR    Read error.
 */
[[nodiscard]] int hs_process_request(
  const HeapPolicy_t policy, const HsSource_t source, const char *const input);

#endif /* HEAPSORT_H */
