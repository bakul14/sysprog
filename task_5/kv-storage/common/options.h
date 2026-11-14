#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>

static constexpr char k_kvs_short_options[] = "ls";

static const struct option k_kvs_long_options[] = {

  {"list", no_argument, nullptr, 'l'},
  {"stack", no_argument, nullptr, 's'},
  {nullptr, 0, nullptr, 0}

};

constexpr char k_help_message[] = "Usage: \n\r    %s --list\n\r    %s --stack\n\r";

#endif /* OPTIONS_H */
