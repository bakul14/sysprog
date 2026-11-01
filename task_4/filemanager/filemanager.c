#include "filemanager.h"
#include "options.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sysexits.h>

static const char *const k_help_message =
  "\nA simple file manager that allows to create or delete one file per launch.\n\n"
  "Usage:\n  -c, --create <filename>\n  -d, --delete <filename>\n  -h, --help\n\n";
static const char *const k_file_close_failed =
  "File %s has been created, but could not be closed\n";
static const char *const k_file_created       = "File %s has been created\n";
static const char *const k_file_deleted       = "File %s has been deleted\n";
static const char *const k_file_exists        = "File %s already exists\n";
static const char *const k_file_not_created   = "File %s has not been created\n";
static const char *const k_file_not_deleted   = "File %s has not been deleted\n";
static const char *const k_file_not_exists    = "File %s does not exist, nothing to delete\n";
static const char *const k_file_create_denied = "File %s has not been created: permission denied\n";
static const char *const k_file_delete_denied = "File %s has not been deleted: permission denied\n";
static const char *const k_no_file_path       = "File path is not specified\n";

static const char *create_file(const char *const file, int *const status)
{
  const char *msg = k_no_file_path;

  if (NULL != file) {
    FILE *const fp = fopen(file, "wx");

    if (NULL == fp) {
      switch (errno) {
        case EEXIST: {
          msg     = k_file_exists;
          *status = EX_CANTCREAT;
          break;
        }
        case EACCES: /* [[fallthrough]] */
        case EPERM:  /* [[fallthrough]] */
        case EROFS: {
          msg     = k_file_create_denied;
          *status = EX_NOPERM;
          break;
        }
        default: {
          msg     = k_file_not_created;
          *status = EX_CANTCREAT;
          break;
        }
      }
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
    if (0 == remove(file)) {
      msg     = k_file_deleted;
      *status = EX_OK;
    } else {
      switch (errno) {
        case ENOENT: {
          msg     = k_file_not_exists;
          *status = EX_NOINPUT;
          break;
        }
        case EACCES: {
          [[fallthrough]];
        }
        case EPERM: {
          [[fallthrough]];
        }
        case EROFS: {
          msg     = k_file_delete_denied;
          *status = EX_NOPERM;
          break;
        }
        default: {
          msg     = k_file_not_deleted;
          *status = EX_NOINPUT;
          break;
        }
      }
    }

  } else {
    *status = EX_USAGE;
  }

  return msg;
}

int fm_process_request(const int option, const char *const filepath)
{
  int ret = EX_SOFTWARE;

  const char *msg = k_help_message;

  switch (option) {
    case 'c': {
      msg = create_file(filepath, &ret);
      break;
    }
    case 'd': {
      msg = delete_file(filepath, &ret);
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

  printf(msg, filepath);

  return ret;
}
