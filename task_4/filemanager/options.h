#ifndef OPTIONS

#define OPTIONS

#include <getopt.h>

constexpr char k_fm_short_options[] = "c:d:h";

static const struct option k_fm_long_options[] = {

  {"create", required_argument, nullptr, 'c'},
  {"delete", required_argument, nullptr, 'd'},
  {"help", no_argument, nullptr, 'h'},
  {nullptr, 0, nullptr, 0}

};

#endif
