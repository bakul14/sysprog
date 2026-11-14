#define _POSIX_C_SOURCE 200809L /* for nanosleep(...) */

#include "common/options.h"

#include "cli/cli.h"
#include "cli/cli_command_map.h"
#include "core/list.h"
#include "core/stack.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

constexpr struct timespec k_main_loop_period = {.tv_sec = 0, .tv_nsec = 10000000};

int main(const int argc, char *argv[])
{
  int ret = EXIT_FAILURE;

  const int option = getopt_long(argc, argv, k_kvs_short_options, k_kvs_long_options, nullptr);

  List_t *const list   = ('l' == option) ? list_init() : nullptr;
  Stack_t *const stack = ('s' == option) ? stack_init() : nullptr;

  bool init_ok = true;

  init_ok = init_ok && cli_init();
  init_ok = init_ok && (list || stack);
  init_ok = init_ok && (!stack || cli_add_commands(&k_stack_commands, stack));
  init_ok = init_ok && (!list || cli_add_commands(&k_list_commands, list));

  if (init_ok) {
    while (cli_process()) {
      nanosleep(&k_main_loop_period, nullptr);
    }
    ret = EXIT_SUCCESS;
  } else {
    fprintf(stderr, k_help_message, argv[0], argv[0]);
  }

  cli_deinit();
  stack_deinit(stack);
  list_deinit(list);

  return ret;
}
