// gcc 7_pipes.c -o pipes   then   ./pipes
// Pipe p1: parent -> child (file name)
// Pipe p2: child -> parent (file contents)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2], n;
    char fname[100], buf[1000];
    FILE *fp;

    pipe(p1);
    pipe(p2);

    if (fork() > 0)                // parent
    {
        close(p1[0]);              // parent only writes on p1
        close(p2[1]);              // parent only reads on p2

        printf("Enter file name: ");
        scanf("%s", fname);
        write(p1[1], fname, strlen(fname) + 1);

        read(p2[0], buf, sizeof(buf));
        printf("\nContents of file:\n%s\n", buf);
        wait(NULL);
    }
    else                           // child
    {
        close(p1[1]);              // child only reads on p1
        close(p2[0]);              // child only writes on p2

        read(p1[0], fname, sizeof(fname));

        fp = fopen(fname, "r");
        if (fp == NULL)
            strcpy(buf, "File not found");
        else
        {
            n = fread(buf, 1, sizeof(buf) - 1, fp);
            buf[n] = '\0';
            fclose(fp);
        }
        write(p2[1], buf, strlen(buf) + 1);
    }
    return 0;
}
