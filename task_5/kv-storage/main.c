#define _POSIX_C_SOURCE 200809L /* for nanosleep(...) */

#include "cli/cli.h"
#include "cli/cli_command_map.h"
#include "core/list.h"
#include "core/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

constexpr struct timespec k_main_loop_period = {.tv_sec = 0, .tv_nsec = 10000000};

int main(const int argc, char *argv[])
{
  int ret = EXIT_FAILURE;

  const bool use_stack = (2 == argc) && (0 == strcmp(argv[1], "--stack"));
  const bool use_list  = (2 == argc) && (0 == strcmp(argv[1], "--list"));

  Stack_t *stack = nullptr;
  List_t *list   = nullptr;

  const CliCommandMap_t *commands = nullptr;
  void *container                 = nullptr;

  if (use_stack) {
    stack     = stack_init();
    commands  = &k_stack_commands;
    container = stack;
  } else if (use_list) {
    list      = list_init();
    commands  = &k_list_commands;
    container = list;
  } else {
    fprintf(stderr, "Usage: %s --stack | --list\n", argv[0]);
  }

  // clang-format off
  const bool init_status = (nullptr != container) &&
                           cli_init()             &&
                           cli_add_commands(commands, container);
  // clang-format on

  if (init_status) {
    while (cli_process()) {
      nanosleep(&k_main_loop_period, nullptr);
    }
    ret = EXIT_SUCCESS;
  } else if (nullptr != commands) {
    fputs("Application has not been inited\n", stderr);
  }

  cli_deinit();
  stack_deinit(stack);
  list_deinit(list);

  return ret;
}
