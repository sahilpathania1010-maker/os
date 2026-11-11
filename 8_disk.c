// gcc 8_disk.c -o disk   then   ./disk
// Head moves away from the spindle = towards HIGHER cylinder numbers.
#include <stdio.h>
#include <stdlib.h>

int req[20], n, head, size;

void sstf()
{
    int done[20] = {0}, pos = head, total = 0, i, j, min, idx = 0;

    printf("\nSSTF: %d", pos);
    for (i = 0; i < n; i++)
    {
        min = 9999;
        for (j = 0; j < n; j++)    // find nearest unserved request
            if (done[j] == 0 && abs(req[j] - pos) < min)
            {
                min = abs(req[j] - pos);
                idx = j;
            }
        total += min;
        pos = req[idx];
        done[idx] = 1;
        printf(" -> %d", pos);
    }
    printf("\nTotal head movement = %d\n", total);
}

void scan(int start)
{
    int i, pos = head, total = 0;

    printf("\nSCAN: %d", pos);
    for (i = start; i < n; i++)    // go up
    {
        total += req[i] - pos;
        pos = req[i];
        printf(" -> %d", pos);
    }
    total += (size - 1) - pos;     // go to last cylinder
    pos = size - 1;
    printf(" -> %d", pos);
    for (i = start - 1; i >= 0; i--)   // come back down
    {
        total += pos - req[i];
        pos = req[i];
        printf(" -> %d", pos);
    }
    printf("\nTotal head movement = %d\n", total);
}

void clook(int start)
{
    int i, pos = head, total = 0;

    printf("\nC-LOOK: %d", pos);
    for (i = start; i < n; i++)    // go up
    {
        total += req[i] - pos;
        pos = req[i];
        printf(" -> %d", pos);
    }
    for (i = 0; i < start; i++)    // jump to lowest, go up again
    {
        total += abs(req[i] - pos);
        pos = req[i];
        printf(" -> %d", pos);
    }
    printf("\nTotal head movement = %d\n", total);
}

int main()
{
    int i, j, t, start;

    printf("Enter disk size: ");
    scanf("%d", &size);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    for (i = 0; i < n - 1; i++)    // sort requests (bubble sort)
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1])
            {
                t = req[j];
                req[j] = req[j + 1];
                req[j + 1] = t;
            }

    start = 0;                     // first request >= head
    while (start < n && req[start] < head)
        start++;

    sstf();
    scan(start);
    clook(start);
    return 0;
}
