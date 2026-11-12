#define _DEFAULT_SOURCE /* It is used to compile cfmakeraw() */

#include "cli.h"

#include "embedded_cli.h"

#include <stddef.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

constexpr size_t k_max_commands = 16U;
constexpr size_t k_max_args     = 8U;

static EmbeddedCli *embedded_cli_ = nullptr;

typedef struct CliBinding {
  CliCallback_t callback;
  void *context;
} CliBinding_t;

static CliBinding_t bindings_[k_max_commands] = {};

static size_t bindings_num_ = 0U;

static struct termios original_stdin_ = {};

static bool is_raw_mode_ = false;

static bool is_running_ = false;

static void write_char(EmbeddedCli *const cli, const char c)
{
  (void)cli;
  ssize_t null = 0U;
  null         = write(STDOUT_FILENO, &c, 1);
  (void)null;
}

static void print_(const char *const string)
{
  embeddedCliPrint(embedded_cli_, string);
}

static void on_binding_(EmbeddedCli *const cli, char *const args, void *const binding_ptr)
{
  (void)cli;

  const size_t token_count = embeddedCliGetTokenCount(args);

  if (token_count <= k_max_args) {
    const char *argv[k_max_args] = {};

    for (size_t i = 0U; i < token_count; ++i) {
      argv[i] = embeddedCliGetToken(args, (uint16_t)(i + 1U));
    }

    const CliBinding_t *const binding = binding_ptr;
    binding->callback(binding->context, token_count, argv, print_);

  } else {
    print_("Too many arguments");
  }
}

static void on_exit_(EmbeddedCli *const cli, char *const args, void *const context)
{
  (void)cli;
  (void)args;
  (void)context;
  bindings_num_ = 0U;
  is_running_   = false;
}

static bool add_exit_command_()
{
  const CliCommandBinding binding = {
    .name         = "exit",
    .help         = "Exit the application",
    .tokenizeArgs = false,
    .context      = nullptr,
    .binding      = on_exit_};

  return embeddedCliAddBinding(embedded_cli_, binding);
}

static void enable_raw_mode_()
{
  if (0 == tcgetattr(STDIN_FILENO, &original_stdin_)) {
    struct termios raw_stdin = original_stdin_;
    cfmakeraw(&raw_stdin);
    is_raw_mode_ = (0 == tcsetattr(STDIN_FILENO, TCSANOW, &raw_stdin));
  }
}

static bool backend_init_()
{
  bool ret = false;

  if (nullptr == embedded_cli_) {
    EmbeddedCliConfig *const config = embeddedCliDefaultConfig();
    config->maxBindingCount         = (uint16_t)(k_max_commands + 1U); /* +1 for exit */
    config->cmdBufferSize           = 256U;

    embedded_cli_ = embeddedCliNew(config);

    if (nullptr != embedded_cli_) {
      embedded_cli_->writeChar = write_char;

      if (add_exit_command_()) {
        enable_raw_mode_();
        is_running_ = true;
        ret         = true;
      } else {
        cli_deinit();
      }
    }
  }

  return ret;
}

bool cli_init()
{
  const bool ret = backend_init_();

  if (ret) {
    /* prints the first invitation */
    embeddedCliProcess(embedded_cli_);
  }

  return ret;
}

bool cli_add_commands(const CliCommandMap_t *const map, void *const context)
{
  // clang-format off
  bool ret = (nullptr != embedded_cli_)     &&
             (nullptr != map)               &&
             (nullptr != map->arg_callback) &&
             (map->num <= (k_max_commands - bindings_num_));
  // clang-format on

  for (size_t i = 0U; ret && (i < map->num); ++i) {
    const ArgCallbackPair_t *const command = &map->arg_callback[i];
    CliBinding_t *const slot               = &bindings_[bindings_num_];

    *slot = (CliBinding_t){.callback = command->callback, .context = context};

    const CliCommandBinding binding = {
      .name         = command->arg,
      .help         = command->help,
      .tokenizeArgs = true,
      .context      = slot,
      .binding      = on_binding_};

    // clang-format off
    ret = (nullptr != command->arg)      &&
          (nullptr != command->callback) &&
          embeddedCliAddBinding(embedded_cli_, binding);
    // clang-format on

    if (ret) {
      ++bindings_num_;
    }
  }

  return ret;
}

void cli_deinit()
{
  if (is_raw_mode_) {
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &original_stdin_);
    is_raw_mode_ = false;
  }

  if (nullptr != embedded_cli_) {
    embeddedCliFree(embedded_cli_);
    embedded_cli_ = nullptr;
  }

  is_running_ = false;
}

bool cli_process()
{
  bool ret = false;

  char c = '\0';
  if (is_running_ && (read(STDIN_FILENO, &c, 1) > 0)) {
    embeddedCliReceiveChar(embedded_cli_, c);
    embeddedCliProcess(embedded_cli_);
    ret = true;
  }

  return ret;
}
