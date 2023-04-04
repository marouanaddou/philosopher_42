#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
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
    // thread->die = 0;
    while(1)
        mutex_data(thread);
    return (0);
}

void creat_thread(thread_t *thread, char *av[], int ac, mutex_t *mt)
{
    int i;

    i = 0;
    // mt = malloc(sizeof(pthread_mutex_t) * 1);
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
        thread[i].lmutex = &thread[(i + 1) % ft_atoi(av[1])].mutex;
        thread[i].mt = mt;
        thread[i].die = 0;
        thread[i].cont_to_eat = 0;        
        pthread_create(&thread[i].th, NULL, &creat, &thread[i]);
        usleep(60);
        i++;
    }
    i = 0;
    while(1)
    {
        pthread_mutex_lock(&thread[i].mt->mut);
        if (calcultime() - thread[i].start_programe > ft_atoi(av[2]))
        {
            pthread_mutex_unlock(&thread[i].mt->mut);
            printf("%lld %d die\n",calcultime() - thread[i].start_programe, i + 1);
            i = 0;
            while(i < ft_atoi(av[1]))
            {
                pthread_mutex_lock(&thread[i].mt->mut);
                thread[i].die = 1;
                pthread_mutex_unlock(&thread[i].mt->mut);
                i++;
            }
            break;
        }
        pthread_mutex_unlock(&thread[i].mt->mut);
        pthread_mutex_lock(&thread[i].mt->mut);
        if (ac == 6)
        {
            if (thread[i].cont_to_eat == thread[i].number_of_times_each_philosopher_must_eat)
            {
                pthread_mutex_unlock(&thread[i].mt->mut);
                break;
            }
        }
        pthread_mutex_unlock(&thread[i].mt->mut);    
        if (i == ft_atoi(av[1]) - 1)
            i = 0;
        i++;
    }
    i = 0;
    while(i < ft_atoi(av[1]))
        pthread_detach(thread[i++].th);
}
       
int main (int ac, char *av[])
{
    thread_t thread[250];
    static mutex_t mt;
    int i;

    i = 0;
    if (ac == 5 || ac == 6)
    {
        if (check_arg(av, ac) == 0)
            return (0);
        while(i < ft_atoi(av[1]))
            pthread_mutex_init(&thread[i++].mutex, NULL);
        pthread_mutex_init(&mt.mut, NULL);
        creat_thread(thread, av, ac, &mt);
        i = 0;
        // while(i < ft_atoi(av[1]))
        //     pthread_join(thread[i++].th, NULL);
        // while(i < ft_atoi(av[1]))
        //     pthread_mutex_destroy(&thread[i++].mutex);
        // pthread_mutex_destroy(&mt.mut);
    }
}