#include <getopt.h>
#include <stdio.h>
#include <sysexits.h>

#include "filemanager.h"
#include "options.h"

static inline int convert_fmerr_to_syserr(const FM_ERROR_TYPE fm_err)
{
  // clang-format off
  switch (fm_err) {
    case FM_E_OK: return EX_OK;
    case FM_E_INCORRECT_ARGUMENT: return EX_NOINPUT;
    case FM_E_INTERNAL_ERROR: return EX_SOFTWARE;
    default: return EX_SOFTWARE;
  }
  // clang-format on
}

int main(int argc, char *argv[])
{
  FM_ERROR_TYPE fm_ret = FM_E_INTERNAL_ERROR;

  if (1 == argc) {
    fm_ret = FM_E_INCORRECT_ARGUMENT;
    process_request('h', "");

  } else {
    int cli_opt = -1;
    while ((cli_opt = getopt_long(argc, argv, "", k_fm_options, NULL)) != -1) {
      fm_ret = process_request(cli_opt, optarg);
      if (FM_E_OK != fm_ret) { break; }
    }
  }

  return convert_fmerr_to_syserr(fm_ret);
}
