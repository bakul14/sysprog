#include <argp.h>
#include <stdio.h>
#include <sysexits.h>

#include "filemanager.h"

static const char *const k_program_desc =
  "A simple file manager to create and delete writable text files";

static const struct argp_option argp_cli_opt[] = {
  // clang-format off
  {"create", 'c', "FILE", 0, "Создание файла"},
  {"delete", 'd', "FILE", 0, "Удаление файла"},
  {0}
  // clang-format on
};

static const char *create_filename = NULL;
static const char *delete_filename = NULL;

static error_t argp_cli_cb(const int key, char *const arg, struct argp_state *const state)
{
  error_t ret = 0;

  switch (key) {
    case 'c': {
      create_filename = arg;
      break;
    }
    case 'd': {
      delete_filename = arg;
      break;
    }
    default: {
      ret = ARGP_ERR_UNKNOWN;
      break;
    }
  }

  return ret;
}

int main(int argc, char *argv[])
{
  const struct argp argp = {argp_cli_opt, argp_cli_cb, 0, k_program_desc};

  argp_parse(&argp, argc, argv, 0, 0, 0);

  if (!create_filename && !delete_filename) {
    fprintf(stderr, "Call filemanager with the --help flag to see usages\n");
    return EX_USAGE;
  }

  int ret = EX_OK; /* provided by sysexits */

  if (create_filename) {
    int err = EX_OK;

    switch (create_file(create_filename, "w")) {
      case FM_E_OK: {
        printf("File %s has been created\n\r", create_filename);
        break;
      }
      case FM_E_INCORRECT_ARGUMENT: {
        fprintf(stderr, "Incorrect file path: %s\n\r", create_filename);
        err = EX_NOINPUT;
        break;
      }
      default: {
        fprintf(stderr, "Failed to create file %s\n\r", create_filename);
        err = EX_CANTCREAT;
        break;
      }
    }

    if (EX_OK == ret) { ret = err; }
  }

  if (delete_filename) {
    int err = EX_OK;

    switch (delete_file(delete_filename)) {
      case FM_E_OK: {
        printf("File %s has been deleted\n\r", delete_filename);
        break;
      }
      case FM_E_INCORRECT_ARGUMENT: {
        fprintf(stderr, "Incorrect file path: %s\n\r", delete_filename);
        err = EX_NOINPUT;
        break;
      }
      default: {
        fprintf(stderr, "Failed to delete file %s\n\r", delete_filename);
        err = EX_SOFTWARE;
        break;
      }
    }

    if (EX_OK == ret) { ret = err; }
  }

  return ret;
}
