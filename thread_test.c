#include "user.h"

void
thread(void* arg1, void* arg2)
{
  printf(2, "arg1: %d\n", *((int*) arg1));
  printf(2, "arg2: %d\n", *((int*) arg2));
  printf(2, "Starting thread...\n");
  exit();
}

// This test just confirms that our threading
// library works correctly and that the system
// calls are implemented correctly.
int
main(void)
{
  int a = 9900;
  int b = 42;
  printf(2, "Starting threading test\n");
  thread_create(thread, &a, &b);
  printf(2, "Joining thread..\n");
  thread_join();
  exit();
}
