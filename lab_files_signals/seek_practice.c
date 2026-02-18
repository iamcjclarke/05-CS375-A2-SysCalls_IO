#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void) {
    char buffer[200];
    memset(buffer, 'a', 200);

    int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
    write(fd, buffer, 200);

    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, 100);

    lseek(fd, 500, SEEK_CUR);     // from offset 100 -> offset 600
    write(fd, buffer, 100);       // writes 100 'a' bytes at 600..699

    close(fd);
    return 0;
}
