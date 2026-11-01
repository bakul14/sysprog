#include "filemanager.h"
#include "options.h"

#include <getopt.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
  const int cli_opt = getopt_long(argc, argv, k_fm_short_options, k_fm_long_options, NULL);

  return fm_process_request(cli_opt, optarg);
}
