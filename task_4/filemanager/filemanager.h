#ifndef FILEMANAGER

#define FILEMANAGER

typedef enum
{
  FM_E_OK                 = 0,
  FM_E_INCORRECT_ARGUMENT = 1,
  FM_E_INTERNAL_ERROR     = 255,
} FM_ERROR_TYPE;

FM_ERROR_TYPE process_request(const int req, const char *const arg);

#endif
