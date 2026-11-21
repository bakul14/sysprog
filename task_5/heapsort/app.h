#pragma once

#include "heap.h"

/**
 * @brief Read numbers, sort them and print the result to stdout.
 *
 * Exactly one of @p filepath and @p numbers must be set.
 *
 * @param[in] policy    Sort order, must not be HEAP_POLICY_NOT_SET.
 * @param[in] filepath  Path to a file with numbers, or nullptr.
 * @param[in] numbers   String with numbers, or nullptr.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK       Numbers have been sorted and printed.
 * @retval EX_USAGE    Invalid request, nothing is printed.
 * @retval EX_NOINPUT  Input file could not be opened.
 * @retval EX_DATAERR  Unexpected token or number out of range.
 * @retval EX_OSERR    Out of memory.
 * @retval EX_IOERR    Read error.
 */
[[nodiscard]] int app_process_request(
  const HeapPolicy_t policy, const char *const filepath, const char *const numbers);
