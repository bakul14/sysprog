#include "app/heapsort.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>
#include <sysexits.h>

static bool take_numbers_(
  const int argc, char *argv[], HsSource_t *const source, const char **const input)
{
  bool ok         = true;
  const int count = argc - optind;

  if (1 == count) {
    ok      = (HS_SOURCE_NOT_SET == *source);
    *source = HS_SOURCE_STRING;
    *input  = argv[optind];
  } else {
    ok = (0 == count);
  }

  return ok;
}

int main(const int argc, char *argv[])
{
  HeapPolicy_t policy = HEAP_POLICY_NOT_SET;
  HsSource_t source   = HS_SOURCE_NOT_SET;
  const char *input   = nullptr;
  bool options_ok     = true;
  int opt             = 0;

  while (-1 != (opt = getopt_long(argc, argv, k_hs_short_options, k_hs_long_options, nullptr))) {
    const bool policy_free = (HEAP_POLICY_NOT_SET == policy);
    const bool source_free = (HS_SOURCE_NOT_SET == source);

    // clang-format off
    switch (opt) {
      case 'm': { options_ok = options_ok && policy_free; policy = HEAP_POLICY_MIN;                break; }
      case 'M': { options_ok = options_ok && policy_free; policy = HEAP_POLICY_MAX;                break; }
      case 'f': { options_ok = options_ok && source_free; source = HS_SOURCE_FILE; input = optarg; break; }
      default:  { options_ok = false;                                                              break; }
    }
    // clang-format on
  }

  options_ok = options_ok && take_numbers_(argc, argv, &source, &input);

  const int ret = options_ok ? hs_process_request(policy, source, input) : EX_USAGE;

  if (EX_USAGE == ret) {
    fprintf(stderr, k_help_message, argv[0], argv[0]);
  }

  return ret;
}
