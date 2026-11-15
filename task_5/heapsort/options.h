#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>

constexpr char k_hs_short_options[] = "f:";

static const struct option k_hs_long_options[] = {

  {"file", required_argument, nullptr, 'f'},
  {"max", no_argument, nullptr, 'M'},
  {"min", no_argument, nullptr, 'm'},
  {nullptr, 0, nullptr, 0}

};

constexpr char k_help_message[] =
  "Usage:\n    %s --min | --max -f, --file <path>\n    %s --min | --max [--] \"<numbers>\"\n";

#endif /* OPTIONS_H */
