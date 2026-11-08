#include "core/stack.h"

#include "cli/cli.h"

#include <stdio.h>

constexpr char test_message_1[] = "test_message_1";
constexpr char test_message_2[] = "test_message_2";
constexpr char test_message_3[] = "test_message_3";

int main(const int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  Stack_t *const stack = stack_init();

  if (nullptr != stack) {
    printf("Stack has been inited\n");
  } else {
    printf("Stack has not been inited\n");
  }

  printf(
    "push result = %d, value = %s\n",
    (int)stack_push(stack, test_message_1, sizeof(test_message_1)), test_message_1);
  printf(
    "push result = %d, value = %s\n",
    (int)stack_push(stack, test_message_2, sizeof(test_message_2)), test_message_2);
  printf(
    "push result = %d, value = %s\n",
    (int)stack_push(stack, test_message_3, sizeof(test_message_3)), test_message_3);

  for (int i = 0; i < 3; ++i) {
    void *data  = nullptr;
    size_t size = 0U;

    if (stack_pop(stack, &data, &size)) {
      printf("pop report: size = %zu, value = %s\n", size, (char *)data);
      stack_data_free(&data);
    }
  }

  stack_deinit(stack);

  // Cli_t cli = {};
  // if (cli_init(&cli)) {
  //   printf("Командная строка успешно инициализирована\n");
  //   for (;;) { cli_process(&cli); }
  // } else {
  //   printf("Ошибка инициализации командной строки\n");
  // }

  return 0;
}
