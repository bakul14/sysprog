#define _POSIX_C_SOURCE 200809L /* for fmemopen(...) with the '-std=c23' flag */

#include "parser.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

static bool parse_item_(const char *const token, int64_t *const item)
{
  char *end = nullptr;

  errno                = 0;
  const intmax_t value = strtoimax(token, &end, 10);

  // clang-format off
  const bool ok = (end != token)       &&
                  ('\0' == *end)       &&
                  (ERANGE != errno)    &&
                  (value >= INT64_MIN) &&
                  (value <= INT64_MAX);
  // clang-format on

  if (ok) {
    *item = (int64_t)value;
  }

  return ok;
}

static int parse_stream_(FILE *const stream, Array_t *const array)
{
  int ret = EX_OK;

  char token[32U] = {};
  int64_t item    = 0;

  while ((EX_OK == ret) && (1 == fscanf(stream, "%31s", token))) {
    const int next = fgetc(stream);

    if (((EOF != next) && !isspace(next)) || !parse_item_(token, &item)) {
      ret = EX_DATAERR;
    } else if (!array_push(array, item)) {
      ret = EX_OSERR;
    }
  }

  if ((EX_OK == ret) && (ferror(stream) || !feof(stream))) {
    ret = EX_IOERR;
  }

  return ret;
}

int parser_read_file(const char *const filepath, Array_t *const array)
{
  int ret = EX_NOINPUT;

  FILE *const stream = fopen(filepath, "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, array);
    fclose(stream);
  }

  return ret;
}

int parser_read_string(const char *const string, Array_t *const array)
{
  int ret = EX_OSERR;

  const char *const buffer = ('\0' != *string) ? string : " ";

  FILE *const stream = fmemopen((void *)buffer, strlen(buffer), "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, array);
    fclose(stream);
  }

  return ret;
}

void parser_print(const Array_t *const array)
{
  const size_t count = array_size(array);

  for (size_t i = 0U; i < count; ++i) {
    printf((0U == i) ? "%" PRId64 : " %" PRId64, array_at(array, i));
  }

  putchar('\n');
}
