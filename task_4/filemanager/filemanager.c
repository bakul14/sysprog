#include "filemanager.h"

#include <stddef.h>
#include <stdio.h>

FM_ERROR_TYPE create_file(const char *const file, const char *const mode)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  if ((NULL != file) && (NULL != mode)) {
    if (NULL != fopen(file, mode)) { ret = FM_E_OK; }
  } else {
    ret = FM_E_INCORRECT_ARGUMENT;
  }

  return ret;
}

FM_ERROR_TYPE delete_file(const char *const file)
{
  FM_ERROR_TYPE ret = FM_E_INTERNAL_ERROR;

  if (NULL != file) {
    if (0 == remove(file)) { ret = FM_E_OK; }
  } else {
    ret = FM_E_INCORRECT_ARGUMENT;
  }

  return ret;
}
