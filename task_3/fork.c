#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const pid_t ret = fork();

    switch (ret) {
        case -1: {
            printf("Failure. Process has not been created\n\r");
            exit(-1);
            break;
        }
        case 0: {
            printf("Child  process. PID = %d. PPID = %d\n\r", getpid(), getppid());
            exit(0);
            break;
        }
        default: {
            printf("Parent process. ret = %d. PID = %d. PPID = %d\n\r", ret, getpid(), getppid());
            break;
        }
    }

    return 0;
}
