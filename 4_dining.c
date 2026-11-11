// gcc 4_dining.c -o dining -pthread   then   ./dining
// Deadlock-free: "room" semaphore lets only 4 of the 5 philosophers
// pick up forks at a time, so a circular wait can never form.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t fork_s[5];                   // one semaphore per fork
sem_t room;                        // allows max 4 philosophers

void *philosopher(void *arg)
{
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i);
    sem_wait(&room);               // enter room

    sem_wait(&fork_s[i]);          // left fork
    sem_wait(&fork_s[(i + 1) % 5]);// right fork

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&fork_s[(i + 1) % 5]);
    sem_post(&fork_s[i]);

    sem_post(&room);               // leave room
    printf("Philosopher %d finished eating\n", i);
    return NULL;
}

int main()
{
    pthread_t t[5];
    int id[5], i;

    sem_init(&room, 0, 4);
    for (i = 0; i < 5; i++)
        sem_init(&fork_s[i], 0, 1);

    for (i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }
    for (i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    return 0;
}
