#include "filemanager.h"
#include "options.h"

#include <stddef.h>
#include <stdio.h>

static FM_ERROR_TYPE create_file(const char *const file, const char *const mode)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  if ((NULL != file) && (NULL != mode)) {
    FILE *const fp = fopen(file, mode);

    if (NULL != fp) {
      if (0 == fclose(fp)) { ret = FM_E_OK; }
    }

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

FM_ERROR_TYPE process_request(const int req, const char *const arg)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  switch (req) {
    case 'c': {
      ret = create_file(arg, "w");
      if (FM_E_OK == ret) {
        printf("File %s has been created\n", arg);
      } else {
        printf("File %s has not been created\n", arg);
      }
      break;
    }
    case 'd': {
      ret = delete_file(arg);
      if (FM_E_OK == ret) {
        printf("File %s has been deleted\n", arg);
      } else {
        printf("File %s has not been deleted\n", arg);
      }
      break;
    }
    case 'h': {
      /* [[fallthrough]] */
    }
    default: {
      printf("%s", k_help_message);
      ret = FM_E_OK;
      break;
    }
  }

  return ret;
}
