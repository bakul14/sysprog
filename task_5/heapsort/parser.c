#define _POSIX_C_SOURCE 200809L /* for fmemopen(...) with the '-std=c23' flag */

#include "parser.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
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

constexpr size_t k_initial_capacity = 64U;

static bool grow_(int64_t **const items, size_t *const capacity)
{
  const bool size_ok        = *capacity <= (SIZE_MAX / (2U * sizeof(**items)));
  const size_t new_capacity = (0U == *capacity) ? k_initial_capacity : (2U * *capacity);

  int64_t *const new_items = size_ok ? realloc(*items, new_capacity * sizeof(**items)) : nullptr;

  if (nullptr != new_items) {
    *items    = new_items;
    *capacity = new_capacity;
  }

  return nullptr != new_items;
}

static int parse_stream_(FILE *const stream, int64_t **const items, size_t *const count)
{
  int ret = EX_OK;

  int64_t *buffer = nullptr;
  size_t used     = 0U;
  size_t capacity = 0U;

  char token[32U] = {};
  int64_t item    = 0;

  while ((EX_OK == ret) && (1 == fscanf(stream, "%31s", token))) {
    const int next = fgetc(stream);

    if (((EOF != next) && !isspace(next)) || !parse_item_(token, &item)) {
      ret = EX_DATAERR;
    } else if ((used == capacity) && !grow_(&buffer, &capacity)) {
      ret = EX_OSERR;
    } else {
      buffer[used] = item;
      ++used;
    }
  }

  if ((EX_OK == ret) && (ferror(stream) || !feof(stream))) {
    ret = EX_IOERR;
  }

  if (EX_OK == ret) {
    *items = buffer;
    *count = used;
  } else {
    free(buffer);
  }

  return ret;
}

int parser_read_file(const char *const filepath, int64_t **const items, size_t *const count)
{
  int ret = EX_NOINPUT;

  *items = nullptr;
  *count = 0U;

  FILE *const stream = fopen(filepath, "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, items, count);
    fclose(stream);
  }

  return ret;
}

int parser_read_string(const char *const string, int64_t **const items, size_t *const count)
{
  int ret = EX_OSERR;

  *items = nullptr;
  *count = 0U;

  const char *const buffer = ('\0' != *string) ? string : " ";

  FILE *const stream = fmemopen((void *)buffer, strlen(buffer), "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, items, count);
    fclose(stream);
  }

  return ret;
}
