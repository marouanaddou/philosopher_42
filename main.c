#include "philosopher.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <unistd.h>

long long calcultime()
{
    long long time;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}
void *creat(void *philo)
{
    thread_t *thread;

    thread = (thread_t *)philo;
    thread->die = 0;
    thread->cont_to_eat = 0;
    // if (thread->i / 2 == 0)
    //     usleep(200);
    while(1)
    {
        mutex_data(thread);
        if (thread->cont_to_eat == thread->number_of_times_each_philosopher_must_eat)
            break;
    }
    return (0);
}

void creat_thread(thread_t *thread, char *av[], int ac)
{
    int i;

    i = 0;
    while(i < ft_atoi(av[1]))
    {
        thread[i].number_of_philo = atoi(av[1]);
        thread[i].time_to_die = atoi(av[2]);
        thread[i].time_to_eat = atoi(av[3]);
        thread[i].time_to_sleep = atoi(av[4]);
        if (ac == 6)
            thread[i].number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
        thread[i].start = calcultime();
        thread[i].start_programe = calcultime();
        thread[i].i = i + 1;
        thread[i].lmutex = &thread[(i + 1)% ft_atoi(av[1])].mutex;
        pthread_create(&thread[i].th, NULL, &creat, &thread[i]);
        usleep(60);
        i++;
    }
    i = 0;
    while(i < ft_atoi(av[1]))
        pthread_join(thread[i++].th, NULL);
}
int main (int ac, char *av[])
{
    thread_t thread[250];
    int i;

    i = 0;
    if (ac == 5 || ac == 6)
    {
        if (check_arg(av, ac) == 0)
            return (0);
        while(i < ft_atoi(av[1]))
        {
            pthread_mutex_init(&thread[i].mutex, NULL);
            i++;
        }
        creat_thread(thread, av, ac);
        i = 0;
        while(i < ft_atoi(av[1]))
        {
            pthread_mutex_destroy(&thread[i].mutex);
            i++;
        }
    }
}