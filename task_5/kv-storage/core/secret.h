#ifndef SECRET_H
#define SECRET_H

#include <stddef.h>
#include <string.h>

static constexpr size_t k_secret_field_size = 64U;

typedef struct SecretData {
  char service[k_secret_field_size];
  char password[k_secret_field_size];
} SecretData_t;

static inline bool secret_fill(
  SecretData_t *const secret, const char *const service, const char *const password)
{
  bool ret = false;

  const bool input_ok = (nullptr != secret) && (nullptr != service) && (nullptr != password);

  if (input_ok) {
    const size_t service_len  = strlen(service);
    const size_t password_len = strlen(password);

    if ((service_len < k_secret_field_size) && (password_len < k_secret_field_size)) {
      *secret = (SecretData_t){};
      memcpy(secret->service, service, service_len);
      memcpy(secret->password, password, password_len);
      ret = true;
    }
  }

  return ret;
}

static inline bool secret_match_service(
  const void *const data, const size_t size, const void *const key)
{
  bool ret = false;

  if ((nullptr != data) && (sizeof(SecretData_t) == size) && (nullptr != key)) {
    const SecretData_t *const secret = data;

    ret = (0 == strcmp(secret->service, (const char *)key));
  }

  return ret;
}

#endif
