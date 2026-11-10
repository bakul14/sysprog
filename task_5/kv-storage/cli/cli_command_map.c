#include "cli_command_map.h"

#include "../core/list.h"
#include "../core/stack.h"

#include <string.h>

static void command_push_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  Stack_t *const stack = ((CliCommandContext_t *)context)->stack;

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

  Stack_t *const stack = ((CliCommandContext_t *)context)->stack;

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

static void command_add_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  List_t *const list = ((CliCommandContext_t *)context)->list;

  if ((nullptr != list) && (nullptr != print)) {
    if (1U != argc) {
      print("Usage: add <value>");
    } else if (list_push_back(list, argv[0], strlen(argv[0]) + 1U)) {
      print("OK");
    } else {
      print("ERROR: add failed");
    }
  }
}

static void command_rm_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  List_t *const list = ((CliCommandContext_t *)context)->list;

  if ((nullptr != list) && (nullptr != print)) {
    void *data  = nullptr;
    size_t size = 0U;

    if (0U != argc) {
      print("Usage: rm");
    } else if (list_pop_back(list, &data, &size)) {
      print((const char *)data);
      list_data_free(&data);
    } else {
      print("ERROR: list is empty");
    }
  }
}

static const ArgCallbackPair_t cli_commands_[] = {
  {.arg = "push", .help = "Push value onto the stack: push <value>", .callback = command_push_},
  {.arg = "pop", .help = "Pop value from the stack", .callback = command_pop_},
  {.arg = "add", .help = "Add value to the list", .callback = command_add_},
  {.arg = "rm", .help = "Remove value from the list", .callback = command_rm_},
};

const CliCommandMap_t k_stack_command_map = {
  .arg_callback = cli_commands_, .num = sizeof(cli_commands_) / sizeof(cli_commands_[0])};
