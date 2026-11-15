#ifndef PARSER_H
#define PARSER_H

#include "../core/array.h"

/**
 * @brief Read whitespace-separated int64_t numbers and append them to @p array.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK       All numbers have been read.
 * @retval EX_NOINPUT  File could not be opened (errno is set by fopen).
 * @retval EX_DATAERR  Unexpected token or number out of range.
 * @retval EX_OSERR    Out of memory.
 * @retval EX_IOERR    Read error.
 */
[[nodiscard]] int parser_read_file(const char *const filepath, Array_t *const array);

[[nodiscard]] int parser_read_string(const char *const string, Array_t *const array);

void parser_print(const Array_t *const array);

#endif
