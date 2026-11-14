#ifndef SECRET_H
#define SECRET_H

#include <stddef.h>
#include <string.h>

constexpr size_t k_secret_field_size = 64U;

typedef struct SecretData {
  char key[k_secret_field_size];
  char val[k_secret_field_size];
} SecretData_t;

// clang-format off
static inline bool secret_fill(
  SecretData_t *const secret,
  const char *const key,
  const char *const val)
// clang-format on
{
  bool ret = false;

  const bool input_ok = (nullptr != secret) && (nullptr != key) && (nullptr != val);

  if (input_ok) {
    const size_t key_len    = strlen(key);
    const size_t secret_len = strlen(val);

    if ((key_len < k_secret_field_size) && (secret_len < k_secret_field_size)) {
      *secret = (SecretData_t){};
      memcpy(secret->key, key, key_len);
      memcpy(secret->val, val, secret_len);
      ret = true;
    }
  }

  return ret;
}

// clang-format off
static inline bool secret_match_key(
  const void *const data,
  const size_t size,
  const void *const key)
// clang-format on
{
  bool ret = false;

  if ((nullptr != data) && (sizeof(SecretData_t) == size) && (nullptr != key)) {
    const SecretData_t *const secret = data;

    ret = (0 == strcmp(secret->key, (const char *)key));
  }

  return ret;
}

#endif
