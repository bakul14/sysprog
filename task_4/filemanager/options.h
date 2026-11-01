#ifndef OPTIONS

#define OPTIONS

#include <getopt.h>
#include <stddef.h>

static const char *const k_fm_short_options = "c:d:h";

static const struct option k_fm_long_options[] = {
  // clang-format off
  {"create", required_argument, NULL, 'c'},
  {"delete", required_argument, NULL, 'd'},
  {"help", no_argument, NULL, 'h'},
  {NULL, 0, NULL, 0}
  // clang-format on
};

static const char *const k_help_message =
  "Usage:\n  -c, --create <filename>\n  -d, --delete <filename>\n  -h, --help\n";

#endif
