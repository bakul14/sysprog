#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void signal_callback(const int signal)
{
  printf("Signal %d has been trapped\n\r", signal);
}

int main()
{
  printf("Process ID: %d\n\r", getpid());

  // clang-format off
  const struct sigaction sa = {.sa_handler = signal_callback,
                               .sa_mask = 0,
                               .sa_flags = SA_RESTART};
  // clang-format on

  for (int sig = 1; sig < NSIG; ++sig) {
    sigaction(sig, &sa, NULL);
  }

  for (;;) {
    pause();
  }

  return 0;
}
