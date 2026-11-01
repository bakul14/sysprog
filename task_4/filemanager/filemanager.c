#include "filemanager.h"
#include "options.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sysexits.h>

static const char *const k_help_message =
  "Usage:\n  -c, --create <filename>\n  -d, --delete <filename>\n  -h, --help\n";
static const char *const k_file_close_failed =
  "File %s has been created, but could not be closed\n";
static const char *const k_file_created     = "File %s has been created\n";
static const char *const k_file_deleted     = "File %s has been deleted\n";
static const char *const k_file_exists      = "File %s already exists\n";
static const char *const k_file_not_created = "File %s has not been created\n";
static const char *const k_file_not_deleted = "File %s has not been deleted\n";
static const char *const k_file_not_exists  = "File %s does not exist, nothing to delete\n";
static const char *const k_no_file_path     = "File path is not specified\n";

static const char *create_file(const char *const file, int *const status)
{
  const char *msg = k_no_file_path;

  if (NULL != file) {
    errno = 0;

    FILE *const fp = fopen(file, "wx");

    if (NULL == fp) {
      msg     = (EEXIST == errno) ? k_file_exists : k_file_not_created;
      *status = EX_CANTCREAT;
    } else if (0 != fclose(fp)) {
      msg     = k_file_close_failed;
      *status = EX_IOERR;
    } else {
      msg     = k_file_created;
      *status = EX_OK;
    }
  } else {
    *status = EX_USAGE;
  }

  return msg;
}

static const char *delete_file(const char *const file, int *const status)
{
  const char *msg = k_no_file_path;

  if (NULL != file) {
    errno = 0;

    if (0 == remove(file)) {
      msg     = k_file_deleted;
      *status = EX_OK;
    } else {
      msg     = (ENOENT == errno) ? k_file_not_exists : k_file_not_deleted;
      *status = EX_NOINPUT;
    }
  } else {
    *status = EX_USAGE;
  }

  return msg;
}

int fm_process_request(const int req, const char *const arg)
{
  int ret = EX_SOFTWARE;

  const char *msg = k_help_message;

  switch (req) {
    case 'c': {
      msg = create_file(arg, &ret);
      break;
    }
    case 'd': {
      msg = delete_file(arg, &ret);
      break;
    }
    case 'h': {
      ret = EX_OK;
      break;
    }
    default: {
      ret = EX_USAGE;
      break;
    }
  }

  printf(msg, arg);

  return ret;
}
