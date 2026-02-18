#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void handler(int signum) {
    (void)signum;

    const char msg[] = "Do you really want to quit [y/n]? ";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);

    char c = 0;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        if (c == 'y' || c == 'Y') {
            const char bye[] = "\n";
            write(STDOUT_FILENO, bye, sizeof(bye) - 1);
            _exit(0);  // immediate exit from signal handler
        }
    }

    const char cont[] = "\n";
    write(STDOUT_FILENO, cont, sizeof(cont) - 1);
}

int main(void) {
    signal(SIGINT, handler);

    while (1) { }
}
