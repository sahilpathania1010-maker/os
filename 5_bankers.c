// gcc 5_bankers.c -o bankers   then   ./bankers
#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10];
    int count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Need = Max - Allocation
    printf("\nNeed matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Safety algorithm
    while (count < n)
    {
        found = 0;
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                        break;

                if (j == m)        // all needs can be met
                {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];   // release resources
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0)            // no process could run
            break;
    }

    if (count == n)
    {
        printf("\nSystem is in SAFE state\nSafe sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safe[i]);
        printf("\n");
    }
    else
        printf("\nSystem is in UNSAFE state\n");

    return 0;
}
