#pragma once

#include <getopt.h>

constexpr char k_app_short_options[] = "f:Mm";

static const struct option k_app_long_options[] = {

  {"file", required_argument, nullptr, 'f'},
  {"max", no_argument, nullptr, 'M'},
  {"min", no_argument, nullptr, 'm'},
  {nullptr, 0, nullptr, 0}

};

constexpr char k_app_help_message[] =
  "Usage:\n    %s --min | --max --file <path>\n    %s --min | --max [--] \"<numbers>\"\n";
