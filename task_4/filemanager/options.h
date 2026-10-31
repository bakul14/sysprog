#ifndef OPTIONS

#define OPTIONS

#include <getopt.h>

static const struct option k_fm_options[] = {
  // clang-format off
  {"create", required_argument, NULL, 'c'},
  {"delete", required_argument, NULL, 'd'},
  {"help", no_argument, NULL, 'h'}
  // clang-format off
};

static const char* const k_help_message = "Usage:\n  --create <filename>\n  --delete <filename>\n";

#endif
