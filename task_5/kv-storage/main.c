#include "core/stack.h"

#include <stdio.h>

constexpr char test_message_1[] = "test_message_1";
constexpr char test_message_2[] = "test_message_2";
constexpr char test_message_3[] = "test_message_3";

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  Stack_t stack = {};
  if (init(&stack)) {
    printf("Stack has been inited\n");
  } else {
    printf("Stack has not been inited\n");
  }

  const Cell_t cell_1 = {.data = (void *)test_message_1};
  const Cell_t cell_2 = {.data = (void *)test_message_2};
  const Cell_t cell_3 = {.data = (void *)test_message_3};

  printf("push result = %d, value = %s\n", (int)push(&stack, cell_1), test_message_1);
  printf("push result = %d, value = %s\n", (int)push(&stack, cell_2), test_message_2);
  printf("push result = %d, value = %s\n", (int)push(&stack, cell_3), test_message_3);

  for (int i = 0; i < 3; ++i) {
    Cell_t cell_tmp;
    printf("pop result = %d,  value = %s\n", (int)pop(&stack, &cell_tmp), (char *)cell_tmp.data);
  }

  deinit(&stack);

  return 0;
}
