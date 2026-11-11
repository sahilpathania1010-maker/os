// SECOND PROCESS: reads sentences from fifo1, counts characters,
// words and lines, writes them to result.txt, then sends the
// file contents back on fifo2.
// gcc 6_fifo2.c -o fifo2   then   ./fifo2   (run in terminal 1)
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char str[500], res[500];
    int fd1, fd2, i, n;
    int c = 0, w = 0, l = 0;
    FILE *fp;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    fd1 = open("fifo1", O_RDONLY);
    read(fd1, str, sizeof(str));
    close(fd1);

    for (i = 0; str[i] != '\0'; i++)
    {
        c++;                                   // character
        if (str[i] == '\n')
            l++;                               // line
        if (str[i] != ' ' && str[i] != '\n' &&
            (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\n'))
            w++;                               // start of a word
    }

    fp = fopen("result.txt", "w");             // write output to file
    fprintf(fp, "Characters = %d\nWords = %d\nLines = %d\n", c, w, l);
    fclose(fp);

    fp = fopen("result.txt", "r");             // read file contents
    n = fread(res, 1, sizeof(res) - 1, fp);
    res[n] = '\0';
    fclose(fp);

    fd2 = open("fifo2", O_WRONLY);             // send them back
    write(fd2, res, strlen(res) + 1);
    close(fd2);

    printf("Result written to result.txt and sent back\n");
    return 0;
}
