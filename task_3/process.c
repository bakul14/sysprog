#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    printf("PPID: %d\n\r", getppid());
    printf("PID: %d\n\r", getpid());
    while(true);
    return 0;
}
