#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int newfd = open("output_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (newfd < 0) exit(1);

    printf("Luke, I am your...\n");  // goes to terminal
    dup2(newfd, 1);                  // stdout -> file
    printf("father\n");              // goes to file

    close(newfd);
    return 0;
}
