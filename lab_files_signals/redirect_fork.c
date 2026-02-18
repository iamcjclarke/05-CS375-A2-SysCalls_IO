#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // CHILD: redirect stdout to file, then exec ls
        int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (fd < 0) {
            perror(argv[1]);
            _exit(1);
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);

        char *cmd[] = {"/bin/ls", "-al", "/", NULL};
        execvp(cmd[0], cmd);

        // only runs if exec fails
        perror("execvp");
        _exit(1);
    }

    // PARENT: wait for child, then print to terminal
    int status = 0;
    waitpid(pid, &status, 0);

    printf("all done\n");
    return 0;
}

