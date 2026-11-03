#include "filemanager.h"

#include <errno.h>
#include <stdio.h>
#include <sysexits.h>

constexpr char k_help_message[] =
  "\nA simple file manager that allows to create or delete one file per launch.\n\n"
  "Usage:\n  -c, --create <filename>\n  -d, --delete <filename>\n  -h, --help\n\n";
constexpr char k_file_close_failed[]  = "File %s has been created, but could not be closed\n";
constexpr char k_file_created[]       = "File %s has been created\n";
constexpr char k_file_deleted[]       = "File %s has been deleted\n";
constexpr char k_file_exists[]        = "File %s already exists\n";
constexpr char k_file_not_created[]   = "File %s has not been created\n";
constexpr char k_file_not_deleted[]   = "File %s has not been deleted\n";
constexpr char k_file_not_exists[]    = "File %s does not exist, nothing to delete\n";
constexpr char k_file_create_denied[] = "File %s has not been created: permission denied\n";
constexpr char k_file_delete_denied[] = "File %s has not been deleted: permission denied\n";
constexpr char k_no_file_path[]       = "File path is not specified\n";

static const char *create_file(const char *const filepath, int *const status)
{
  const char *msg = k_no_file_path;

  if (nullptr != filepath) {
    FILE *const fp = fopen(filepath, "wx");
    if (nullptr != fp) {
      const int close_result = fclose(fp);
      msg                    = (0 == close_result) ? k_file_created : k_file_close_failed;
      *status                = (0 == close_result) ? EX_OK : EX_IOERR;
    } else {
      // clang-format off
        switch (errno) {
          case EEXIST: { msg = k_file_exists;        *status = EX_CANTCREAT; break; }
          case EACCES: { [[fallthrough]]; }
          case EPERM:  { [[fallthrough]]; }
          case EROFS:  { msg = k_file_create_denied; *status = EX_NOPERM;    break; }
          default:     { msg = k_file_not_created;   *status = EX_CANTCREAT; break; }
        }
      // clang-format on
    }
  } else {
    *status = EX_USAGE;
  }

  return msg;
}

static const char *delete_file(const char *const filepath, int *const status)
{
  const char *msg = k_no_file_path;

  if (nullptr != filepath) {
    if (0 == remove(filepath)) {
      msg     = k_file_deleted;
      *status = EX_OK;
    } else {
      // clang-format off
      switch (errno) {
        case ENOENT: { msg = k_file_not_exists;    *status = EX_NOINPUT; break; }
        case EACCES: { [[fallthrough]]; }
        case EPERM:  { [[fallthrough]]; }
        case EROFS:  { msg = k_file_delete_denied; *status = EX_NOPERM;  break; }
        default:     { msg = k_file_not_deleted;   *status = EX_NOINPUT; break; }
      }
      // clang-firmat on
    }
  } else {
    *status = EX_USAGE;
  }

  return msg;
}

int fm_process_request(const int option, const char *const filepath)
{
  int ret         = EX_SOFTWARE;
  const char *msg = k_help_message;
  // clang-format off
  switch (option) {
    case 'c': { msg = create_file(filepath, &ret); break; }
    case 'd': { msg = delete_file(filepath, &ret); break; }
    case 'h': { ret = EX_OK;                       break; }
    default:  { ret = EX_USAGE;                    break; }
  }
  // clang-foramt on
  printf(msg, filepath);
  return ret;
}
