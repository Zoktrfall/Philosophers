#include "philosophers.h"

pthread_mutex_t print;

void	*thread_philo(void	*philo_arg)
{
	t_philo_data *philo;

	philo = (t_philo_data *)philo_arg;
	if (philo->index_philosophers %  2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  has taken a fork\n", (retrun_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  has taken a fork\n", (retrun_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  is eating\n", (retrun_time() - philo->start_program_time), philo->index_philosophers);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d is sleeping\n", (retrun_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		usleep(philo->time_to_sleep);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d is thinking\n", (retrun_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

int	respected_philosophers(t_philo_data ***philo, pthread_mutex_t ***mutex, int count)
{
	int i;
	int *flag_die = malloc(sizeof(int));
	*flag_die = 0;
	for(int j = 0; j < count; j++)
		(*philo)[j]->ptr_philo_die = flag_die;
	if (init_options(philo, count))
		return (del_philosophers(philo, mutex, count, MALLOC_ERROR));
	i = -1;
	while (++i < count)
	{
		if (pthread_create((*philo)[i]->thread_philo, NULL, \
			thread_philo, (*philo)[i]))
			return (del_philosophers(philo, mutex, count, THREAD_ERROR));
	}
	while (1)
	{
		i = -1;
		while (i < count)
		{
			if (*flag_die == 1)
			{			
				if (pthread_join(*(*philo)[i]->thread_philo, NULL))
					return (del_philosophers(philo, mutex, count, THREAD_ERROR));
			}
			i++;
		}
	}
	free_global(philo, NULL, NULL);
	system("leaks philo");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	pthread_mutex_t	**mutex;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas) || init_mutex(&philo, &mutex, mas[0]))
		return (del_philosophers(&philo, &mutex, mas[0], MALLOC_ERROR));
	if (respected_philosophers(&philo, &mutex, mas[0]))
		return (1);
	// struct timeval oper;
	// gettimeofday(&oper, NULL);
	// long long time = oper.tv_sec * 1000 + oper.tv_usec / 1000;
	// printf("time = %lld\n", time / 1000);
	// long long time = retrun_time();
	// sleep(1);
	// printf("time = %lld\n", (retrun_time() - time) / 1000);
	// sleep(2);
	// printf("time = %lld\n", (retrun_time() - time) / 1000);
	// sleep(3);
	// printf("time = %lld\n", (retrun_time() - time) / 1000);
	// for(int i = 0; i < mas[0]; i++)
	// {
	// 	sleep(1);
	// 	if (philo[i] == NULL)
	// 		return printf("exav\n");
	// 	printf("philo[%d]->philo_die_mutex= %d\n", i, philo[i]->philo_die_mutex);
	// 	printf("philo[%d]->ptr_philo_die= %d\n", i, philo[i]->ptr_philo_die);
	// 	printf("philo[%d]->print_mutexo= %d\n", i, philo[i]->print_mutex);
	// 	printf("philo[%d]->thread_philo= %d\n", i, philo[i]->thread_philo);
	// 	printf("philo[%d]->philosophers = %d\n", i, philo[i]->philosophers);
	// 	printf("philo[%d]->index_philosophers = %d\n", i, philo[i]->index_philosophers);
	// 	printf("philo[%d]->time_to_die = %d\n", i, philo[i]->time_to_die);
	// 	printf("philo[%d]->time_to_eat = %d\n", i, philo[i]->time_to_eat);
	// 	printf("philo[%d]->time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	// 	printf("philo[%d]->optional_argument = %d\n", i, philo[i]->optional_argument);
	// 	printf("philo[%d]->fork_left = %d\n", i, philo[i]->fork_left);
	// 	printf("philo[%d]->fork_right = %d\n", i, philo[i]->fork_right);
	// 	printf("philo[%d]->start_program_time = %lld\n", i, (retrun_time() - philo[i]->start_program_time) / 1000);
	// 	printf("\n");
	// }
	del_philosophers(&philo, &mutex, mas[0], FINISH_PROGRAM);
	// system("leaks philo");
	return (0);
}
