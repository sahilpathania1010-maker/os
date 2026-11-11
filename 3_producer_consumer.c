// gcc 3_producer_consumer.c -o pc -pthread   then   ./pc
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE], in = 0, out = 0;
sem_t empty, full;                 // counting semaphores
pthread_mutex_t mutex;             // mutual exclusion

void *producer(void *arg)
{
    int i;
    for (i = 1; i <= 10; i++)
    {
        sem_wait(&empty);          // wait for an empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        printf("Produced %d\n", i);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);           // one more full slot
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int i, item;
    for (i = 1; i <= 10; i++)
    {
        sem_wait(&full);           // wait for a full slot
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);          // one more empty slot
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);     // all slots empty at start
    sem_init(&full, 0, 0);         // no slot full at start
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
