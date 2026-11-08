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

  const Cell_t cell_1 = {.data = (void *)test_message_1, .size = sizeof(test_message_1)};
  const Cell_t cell_2 = {.data = (void *)test_message_2, .size = sizeof(test_message_2)};
  const Cell_t cell_3 = {.data = (void *)test_message_3, .size = sizeof(test_message_3)};

  printf("push result = %d, value = %s\n", (int)stack_push(stack, cell_1), test_message_1);
  printf("push result = %d, value = %s\n", (int)stack_push(stack, cell_2), test_message_2);
  printf("push result = %d, value = %s\n", (int)stack_push(stack, cell_3), test_message_3);

  for (int i = 0; i < 3; ++i) {
    Cell_t cell = stack_pop(stack);
    printf("pop report: size = %d, value = %s\n", (int)cell.size, (char *)cell.data);
    stack_cell_free(&cell);
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
