#define _POSIX_C_SOURCE 200809L /* for nanosleep(...) */

#include "cli/cli.h"
#include "cli/cli_command_map.h"
#include "core/list.h"
#include "core/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

constexpr struct timespec k_main_loop_period = {.tv_sec = 0, .tv_nsec = 10000000};

int main(const int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  int ret = EXIT_FAILURE;

  bool init_status = true;

  List_t *const list   = list_init();
  Stack_t *const stack = stack_init();

  init_status = init_status && (nullptr != stack);
  init_status = init_status && (nullptr != list);
  init_status = init_status && cli_init();
  init_status = init_status && cli_add_commands(&k_stack_commands, stack);
  init_status = init_status && cli_add_commands(&k_list_commands, list);

  if (init_status) {
    while (cli_process()) {
      nanosleep(&k_main_loop_period, nullptr);
    }
    ret = EXIT_SUCCESS;
  } else {
    fputs("Application has not been inited\n", stderr);
  }

  cli_deinit();
  stack_deinit(stack);
  list_deinit(list);

  return ret;
}
