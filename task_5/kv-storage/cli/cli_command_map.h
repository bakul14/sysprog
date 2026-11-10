#ifndef CLI_COMMAND_MAP_H
#define CLI_COMMAND_MAP_H

#include "cli.h"

#include "../core/list.h"
#include "../core/stack.h"

extern const CliCommandMap_t k_stack_command_map;

typedef struct CliCommandContext {
  List_t *const list;
  Stack_t *const stack;
} CliCommandContext_t;

#endif
