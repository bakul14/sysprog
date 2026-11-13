#include "cli_command_map.h"

#include "../core/list.h"
#include "../core/secret.h"
#include "../core/stack.h"

#include <stdio.h>

static void print_secret_(const CliPrint_t print, const void *const data)
{
  const SecretData_t *const secret = data;

  char line[2U * k_secret_field_size + 8U] = {};
  snprintf(line, sizeof(line), "%s: %s", secret->service, secret->password);
  print(line);
}

static void print_service_(const void *const data, const size_t size, void *const context)
{
  const CliPrint_t *const print = context;

  if (sizeof(SecretData_t) == size) {
    (*print)(((const SecretData_t *)data)->service);
  }
}

static void command_stack_push_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  Stack_t *const stack = context;
  SecretData_t secret  = {};

  if (2U != argc) {
    print("Usage: push <service> <password>");
  } else if (!secret_fill(&secret, argv[0], argv[1])) {
    print("ERROR: service and password must be shorter than 64 chars");
  } else if (stack_push(stack, &secret, sizeof(secret))) {
    print("OK");
  } else {
    print("ERROR: push failed");
  }
}

static void command_stack_pop_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  Stack_t *const stack = context;
  void *data           = nullptr;
  size_t size          = 0U;

  if (0U != argc) {
    print("Usage: pop");
  } else if (stack_pop(stack, &data, &size)) {
    print_secret_(print, data);
    stack_data_free(&data);
  } else {
    print("ERROR: stack is empty");
  }
}

static void command_stack_find_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  const Stack_t *const stack = context;
  const void *data           = nullptr;

  if (1U != argc) {
    print("Usage: find <service>");
  } else if (stack_find(stack, secret_match_service, argv[0], &data)) {
    print_secret_(print, data);
  } else {
    print("ERROR: not found");
  }
}

static void command_stack_edit_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  Stack_t *const stack = context;
  SecretData_t secret  = {};

  if (2U != argc) {
    print("Usage: edit <service> <password>");
  } else if (!secret_fill(&secret, argv[0], argv[1])) {
    print("ERROR: service and password must be shorter than 64 chars");
  } else if (stack_edit(stack, secret_match_service, argv[0], &secret, sizeof(secret))) {
    print("OK");
  } else {
    print("ERROR: not found");
  }
}

static void command_stack_show_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  const Stack_t *const stack = context;
  CliPrint_t print_copy      = print;

  if (0U != argc) {
    print("Usage: show");
  } else {
    stack_foreach(stack, print_service_, &print_copy);
  }
}

static void command_list_add_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  List_t *const list  = context;
  SecretData_t secret = {};

  if (2U != argc) {
    print("Usage: add <service> <password>");
  } else if (!secret_fill(&secret, argv[0], argv[1])) {
    print("ERROR: service and password must be shorter than 64 chars");
  } else if (list_push_back(list, &secret, sizeof(secret))) {
    print("OK");
  } else {
    print("ERROR: add failed");
  }
}

static void command_list_rm_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  List_t *const list = context;

  if (0U != argc) {
    print("Usage: rm");
  } else if (list_remove(list)) {
    print("OK");
  } else {
    print("ERROR: no item selected");
  }
}

static void command_list_next_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  List_t *const list = context;
  const void *data   = nullptr;

  if (0U != argc) {
    print("Usage: next");
  } else if (list_next(list, &data)) {
    print_secret_(print, data);
  } else {
    print("ERROR: end of list");
  }
}

static void command_list_prev_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  List_t *const list = context;
  const void *data   = nullptr;

  if (0U != argc) {
    print("Usage: prev");
  } else if (list_prev(list, &data)) {
    print_secret_(print, data);
  } else {
    print("ERROR: beginning of list");
  }
}

static void command_list_edit_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  List_t *const list  = context;
  SecretData_t secret = {};

  if (2U != argc) {
    print("Usage: edit <service> <password>");
  } else if (!secret_fill(&secret, argv[0], argv[1])) {
    print("ERROR: service and password must be shorter than 64 chars");
  } else if (list_edit(list, &secret, sizeof(secret))) {
    print("OK");
  } else {
    print("ERROR: no item selected");
  }
}

static void command_list_find_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  List_t *const list = context;
  const void *data   = nullptr;

  if (1U != argc) {
    print("Usage: find <service>");
  } else if (list_find(list, secret_match_service, argv[0], &data)) {
    print_secret_(print, data);
  } else {
    print("ERROR: not found");
  }
}

static void command_list_cur_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  const List_t *const list = context;
  const void *data         = nullptr;

  if (0U != argc) {
    print("Usage: cur");
  } else if (list_current(list, &data)) {
    print_secret_(print, data);
  } else {
    print("ERROR: no item selected");
  }
}

static void command_list_show_(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print)
{
  (void)argv;

  const List_t *const list = context;
  CliPrint_t print_copy    = print;

  if (0U != argc) {
    print("Usage: show");
  } else {
    list_foreach(list, print_service_, &print_copy);
  }
}

static const ArgCallbackPair_t stack_commands_[] = {
  {.arg = "push", .help = "Push secret: push <service> <password>", .callback = command_stack_push_},
  {.arg = "pop", .help = "Pop and show the top secret", .callback = command_stack_pop_},
  {.arg = "find", .help = "Show secret: find <service>", .callback = command_stack_find_},
  {.arg = "edit", .help = "Change password: edit <service> <password>", .callback = command_stack_edit_},
  {.arg = "show", .help = "Show all services", .callback = command_stack_show_},
};

// clang-format off
static const ArgCallbackPair_t list_commands_[] = {
  {.arg = "add",  .help = "Add secret: add <service> <password>", .callback = command_list_add_},
  {.arg = "rm",   .help = "Remove the selected secret", .callback = command_list_rm_},
  {.arg = "next", .help = "Select and show the next secret", .callback = command_list_next_},
  {.arg = "prev", .help = "Select and show the previous secret", .callback = command_list_prev_},
  {.arg = "edit", .help = "Replace the selected secret: edit <service> <password>", .callback = command_list_edit_},
  {.arg = "find", .help = "Select and show secret: find <service>", .callback = command_list_find_},
  {.arg = "cur",  .help = "Show the selected secret", .callback = command_list_cur_},
  {.arg = "show", .help = "Show all services", .callback = command_list_show_},
};
//clang-format on

const CliCommandMap_t k_stack_commands = {
  .arg_callback = stack_commands_, .num = sizeof(stack_commands_) / sizeof(stack_commands_[0])};

const CliCommandMap_t k_list_commands = {
  .arg_callback = list_commands_, .num = sizeof(list_commands_) / sizeof(list_commands_[0])};
