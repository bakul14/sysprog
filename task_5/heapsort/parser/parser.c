#define _POSIX_C_SOURCE 200809L /* for fmemopen(...) with the '-std=c23' flag */

#include "parser.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

constexpr char k_invalid_input[] = "Invalid input: unexpected token or number out of range\n";

static bool parse_stream_(FILE *const stream, Array_t *const array)
{
  bool ok        = true;
  long long item = 0;

  errno = 0;
  while (ok && (1 == fscanf(stream, "%lld", &item))) {
    const int next = fgetc(stream);
    ok = (ERANGE != errno) && ((EOF == next) || isspace(next)) && array_push(array, item);
  }

  ok = ok && feof(stream) && !ferror(stream);

  if (!ok) {
    fputs(k_invalid_input, stderr);
  }

  return ok;
}

bool parser_read_file(const char *const filepath, Array_t *const array)
{
  bool ret = false;

  FILE *const stream = fopen(filepath, "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, array);
    fclose(stream);
  } else {
    perror(filepath);
  }

  return ret;
}

bool parser_read_string(const char *const string, Array_t *const array)
{
  bool ret = false;

  const char *const buffer = ('\0' != *string) ? string : " ";

  FILE *const stream = fmemopen((void *)buffer, strlen(buffer), "r");

  if (nullptr != stream) {
    ret = parse_stream_(stream, array);
    fclose(stream);
  } else {
    perror("input string");
  }

  return ret;
}

void parser_print(const Array_t *const array)
{
  const size_t count = array_size(array);

  for (size_t i = 0U; i < count; ++i) {
    printf((0U == i) ? "%lld" : " %lld", array_at(array, i));
  }
  
  putchar('\n');
}
