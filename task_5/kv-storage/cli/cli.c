#include "cli.h"

#include "embedded_cli.h"

#include <stddef.h>
#include <termios.h>
#include <unistd.h>

static EmbeddedCli *embedded_cli_ = nullptr;

static struct termios original_stdin_ = {};

static void write_char(EmbeddedCli *const cli, const char c)
{
  (void)cli;
  size_t null = 0U;
  null        = write(STDOUT_FILENO, &c, 1);
  (void)null;
}

bool cli_init(Cli_t *const cli)
{
  (void)cli;

  bool ret = false;

  embedded_cli_ = embeddedCliNewDefault();

  if (nullptr != embedded_cli_) {
    embedded_cli_->writeChar = write_char;
    struct termios raw_stdin;
    tcgetattr(STDIN_FILENO, &original_stdin_);
    raw_stdin = original_stdin_;
    // cfmakeraw(&raw_stdin); не компилируется
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_stdin);
    ret = true;
  }

  return ret;
}

void cli_deinit(Cli_t *const cli)
{
  (void)cli;
  tcsetattr(STDIN_FILENO, TCSANOW, &original_stdin_);
}

void cli_process(Cli_t *const cli)
{
  (void)cli;
  char c;
  if (read(STDIN_FILENO, &c, 1) > 0) {
    embeddedCliReceiveChar(embedded_cli_, c);
    embeddedCliProcess(embedded_cli_);
  }
}
