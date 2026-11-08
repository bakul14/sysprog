#ifndef CLI_H
#define CLI_H

#include <stdbool.h>
#include <stddef.h>

typedef void (*CliPrint_t)(const char *const string);

typedef void (*CliCallback_t)(
  void *const context, const size_t argc, const char *const argv[], const CliPrint_t print);

typedef struct ArgCallbackPair {
  const char *arg;
  const char *help;
  CliCallback_t callback;
} ArgCallbackPair_t;

typedef struct CliCommandMap {
  const ArgCallbackPair_t *arg_callback;
  size_t num;
} CliCommandMap_t;

bool cli_init(const CliCommandMap_t *const map, void *const context);

bool cli_process(void);

void cli_deinit(void);

#endif
