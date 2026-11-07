#ifndef CLI_H
#define CLI_H

typedef struct ArgCallbackPair {
  const char *arg;
  void (*callback)();
} ArgCallbackPair_t;

typedef struct Cli {
  ArgCallbackPair_t *arg_callback;
  int num;
} Cli_t;

bool cli_init(Cli_t *const cli);

void cli_deinit(Cli_t *const cli);

void cli_process(Cli_t *const cli);

#endif
