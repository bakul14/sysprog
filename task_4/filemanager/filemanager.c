#include "filemanager.h"
#include "options.h"

#include <stddef.h>
#include <stdio.h>
#include <sysexits.h>

static const char *const k_msg_created      = "File %s has been created\n";
static const char *const k_msg_not_created  = "File %s has not been created\n";
static const char *const k_msg_close_failed = "File %s has been created, but could not be closed\n";
static const char *const k_msg_deleted      = "File %s has been deleted\n";
static const char *const k_msg_not_deleted  = "File %s has not been deleted\n";
static const char *const k_msg_no_file_path = "File path is not specified\n";

static const char *create_file(const char *const file, int *const status)
{
  const char *msg = k_msg_no_file_path;

  if (NULL != file) {
    FILE *const fp = fopen(file, "w");

    if (NULL == fp) {
      msg     = k_msg_not_created;
      *status = EX_CANTCREAT;
    } else if (0 != fclose(fp)) {
      msg     = k_msg_close_failed;
      *status = EX_IOERR;
    } else {
      msg     = k_msg_created;
      *status = EX_OK;
    }
  } else {
    *status = EX_USAGE;
  }

  return msg;
}

static const char *delete_file(const char *const file, int *const status)
{
  const char *msg = k_msg_no_file_path;

  if (NULL != file) {
    if (0 == remove(file)) {
      msg     = k_msg_deleted;
      *status = EX_OK;
    } else {
      msg     = k_msg_not_deleted;
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
