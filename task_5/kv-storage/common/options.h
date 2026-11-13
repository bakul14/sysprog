#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>

static constexpr char k_kvs_short_options[] = "ls";

static const struct option k_kvs_long_options[] = {

  {"list", no_argument, nullptr, 'l'},
  {"stack", no_argument, nullptr, 's'},
  {nullptr, 0, nullptr, 0}

};

#endif /* OPTIONS_H */
