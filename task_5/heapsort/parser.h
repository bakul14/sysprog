#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Read whitespace-separated int64_t numbers into a newly allocated buffer.
 *
 * @param[out] items  On EX_OK - buffer to be released with free(), otherwise nullptr.
 * @param[out] count  On EX_OK - number of read items, otherwise 0.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK       All numbers have been read.
 * @retval EX_NOINPUT  File could not be opened (errno is set by fopen).
 * @retval EX_DATAERR  Unexpected token or number out of range.
 * @retval EX_OSERR    Out of memory.
 * @retval EX_IOERR    Read error.
 */
[[nodiscard]] int parser_read_file(
  const char *const filepath, int64_t **const items, size_t *const count);

[[nodiscard]] int parser_read_string(
  const char *const string, int64_t **const items, size_t *const count);
