#include "list.h"

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  List *list = create_list();

  delete_list(list);

  return 0;
}
