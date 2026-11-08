#include "cli_command_map.h"

#include "../core/stack.h"

#include <string.h>

static void command_push_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  Stack_t *const stack = context;

  if ((nullptr != stack) && (nullptr != print)) {
    if (1U != argc) {
      print("Usage: push <value>");
    } else if (stack_push(stack, argv[0], strlen(argv[0]) + 1U)) {
      print("OK");
    } else {
      print("ERROR: push failed");
    }
  }
}

static void command_pop_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  Stack_t *const stack = context;

  if ((nullptr != stack) && (nullptr != print)) {
    void *data  = nullptr;
    size_t size = 0U;

    if (0U != argc) {
      print("Usage: pop");
    } else if (stack_pop(stack, &data, &size)) {
      print((const char *)data);
      stack_data_free(&data);
    } else {
      print("ERROR: stack is empty");
    }
  }
}

static const ArgCallbackPair_t stack_commands_[] = {
  {.arg = "push", .help = "Push value onto the stack: push <value>", .callback = command_push_},
  {.arg = "pop", .help = "Pop value from the stack", .callback = command_pop_},
};

const CliCommandMap_t k_stack_command_map = {
  .arg_callback = stack_commands_, .num = sizeof(stack_commands_) / sizeof(stack_commands_[0])};
