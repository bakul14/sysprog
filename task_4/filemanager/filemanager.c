#include <argp.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <sysexits.h>
#include <unistd.h>

typedef enum
{
  FM_E_OK                 = 0,
  FM_E_INCORRECT_ARGUMENT = 1,
  FM_E_INTERNAL_ERROR     = 255,
} FM_ERROR_TYPE;

static void show_help_message()
{
  printf("Usage:\n\r    filemanager --create <file>\n\r    filemanager --delete <file>\n\r");
}

static FM_ERROR_TYPE create_file(const char *const file, const char *const mode)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  if ((NULL != file) && (NULL != mode)) {
    if (NULL != fopen(file, mode)) { ret = FM_E_OK; }
  } else {
    ret = FM_E_INCORRECT_ARGUMENT;
  }

  return ret;
}

static FM_ERROR_TYPE delete_file(const char *const file)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  if (NULL != file) {
    if (0 == remove(file)) { ret = FM_E_OK; }
  } else {
    ret = FM_E_INCORRECT_ARGUMENT;
  }

  return ret;
}

int main(int argc, char *argv[])
{
  show_help_message();

  const char *const filename = "aboba.txt";

  int ret = EX_SOFTWARE;

  if (FM_E_OK == create_file(filename, "w")) {
    printf("File %s has been created\n\r", filename);
    ret = EX_OK;
  }

  if (FM_E_OK == delete_file(filename)) {
    printf("File %s has been deleted\n\r", filename);
    ret = EX_OK;
  }

  return ret;
}
