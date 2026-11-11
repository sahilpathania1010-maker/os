// FIRST PROCESS: accepts sentences, sends them on fifo1,
// reads the result back from fifo2 and displays it.
// gcc 6_fifo1.c -o fifo1   then   ./fifo1   (run in terminal 2)
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char str[500], res[500];
    int fd1, fd2;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    printf("Enter sentences (type # at the end):\n");
    scanf("%[^#]", str);           // read everything until #

    fd1 = open("fifo1", O_WRONLY);
    write(fd1, str, strlen(str) + 1);
    close(fd1);

    fd2 = open("fifo2", O_RDONLY);
    read(fd2, res, sizeof(res));
    close(fd2);

    printf("\nResult received from second process:\n%s", res);
    return 0;
}
