#include "cli/cli.h"
#include "cli/cli_command_map.h"
#include "core/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(const int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  int ret = EXIT_FAILURE;

  bool init_status = true;

  Stack_t *const stack = stack_init();

  init_status = init_status && (nullptr != stack);
  init_status = init_status && cli_init(&k_stack_command_map, stack);

  if (init_status) {
    const struct timespec ts = {.tv_sec = 0, .tv_nsec = 10000000};
    while (cli_process()) { nanosleep(&ts, nullptr); }
    ret = EXIT_SUCCESS;
  } else {
    fputs("Application has not been inited\n", stderr);
  }

  cli_deinit();
  stack_deinit(stack);

  return ret;
}
