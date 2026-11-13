#ifndef SECRET_H
#define SECRET_H

#include <stddef.h>
#include <string.h>

static constexpr size_t k_secret_field_size = 64U;

typedef struct SecretData {
  char service[k_secret_field_size];
  char secret[k_secret_field_size];
} SecretData_t;

static inline bool secret_fill(
  SecretData_t *const secret_data, const char *const service, const char *const secret)
{
  bool ret = false;

  const bool input_ok = (nullptr != secret_data) && (nullptr != service) && (nullptr != secret);

  if (input_ok) {
    const size_t service_len = strlen(service);
    const size_t secret_len  = strlen(secret);

    if ((service_len < k_secret_field_size) && (secret_len < k_secret_field_size)) {
      *secret_data = (SecretData_t){};
      memcpy(secret_data->service, service, service_len);
      memcpy(secret_data->secret, secret, secret_len);
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
    const SecretData_t *const secret_data = data;

    ret = (0 == strcmp(secret_data->service, (const char *)key));
  }

  return ret;
}

#endif
