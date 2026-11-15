#include "options.h"

#include "core/array.h"
#include "core/heap.h"
#include "parser/parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char *argv[])
{
  int ret = EXIT_FAILURE;

  int policy        = 0;
  const char *file  = nullptr;
  bool arguments_ok = true;
  int opt           = 0;

  while (-1 != (opt = getopt_long(argc, argv, k_hs_short_options, k_hs_long_options, nullptr))) {
    // clang-format off
    switch (opt) {
      case 'm': [[fallthrough]];
      case 'M': { arguments_ok = arguments_ok && (0 == policy); policy = opt;    break; }
      case 'f': { arguments_ok = arguments_ok && !file;         file   = optarg; break; }
      default:  { arguments_ok = false;                                          break; }
    }
    // clang-format on
  }

  const char *const string = (!file && ((optind + 1) == argc)) ? argv[optind++] : nullptr;

  const ParserRead_t read  = file ? parser_read_file : parser_read_string;
  const char *const source = file ? file : string;

  Array_t *const array = array_init();

  const bool init_ok = arguments_ok && (optind == argc) && (0 != policy) && source && array;

  if (init_ok && read(source, array)) {
    heap_sort(array, ('m' == policy) ? HEAP_POLICY_MIN : HEAP_POLICY_MAX);
    parser_print(array);
    ret = EXIT_SUCCESS;
  }

  if (!init_ok) {
    fprintf(stderr, k_help_message, argv[0], argv[0]);
  }

  array_deinit(array);

  return ret;
}
