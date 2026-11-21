#include "app.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>
#include <sysexits.h>

int main(const int argc, char *argv[])
{
  HeapPolicy_t policy  = HEAP_POLICY_NOT_SET;
  const char *filepath = nullptr;
  bool options_ok      = true;
  int opt              = 0;

  while (-1 != (opt = getopt_long(argc, argv, k_app_short_options, k_app_long_options, nullptr))) {
    const bool policy_free = (HEAP_POLICY_NOT_SET == policy);

    // clang-format off
    switch (opt) {
      case 'm': { options_ok = options_ok && policy_free;           policy   = HEAP_POLICY_MIN; break; }
      case 'M': { options_ok = options_ok && policy_free;           policy   = HEAP_POLICY_MAX; break; }
      case 'f': { options_ok = options_ok && (nullptr == filepath); filepath = optarg;          break; }
      default:  { options_ok = false;                                                           break; }
    }
    // clang-format on
  }

  const int rest = argc - optind;

  const char *const numbers = (1 == rest) ? argv[optind] : nullptr;

  options_ok = options_ok && (rest <= 1);

  const int ret = options_ok ? app_process_request(policy, filepath, numbers) : EX_USAGE;

  if (EX_USAGE == ret) {
    fprintf(stderr, k_app_help_message, argv[0], argv[0]);
  }

  return ret;
}
