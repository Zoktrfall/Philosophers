#include "philosophers.h"

void	*thread_philo(void	*philo_arg)
{
	t_philo_data *philo;

	philo = (t_philo_data *)philo_arg;
	if (philo->index_philosophers %  2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->time_philo_mutex);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->time_philo_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->time_philo_mutex);
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  has taken a fork\n", (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  has taken a fork\n", (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		philo->time_philo = return_time() - philo->start_program_time;
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d  is eating\n", (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d is sleeping\n", (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		usleep(philo->time_to_sleep * 1000);
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d is thinking\n", (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

int	death_check(t_philo_data *philo, int **flag_die)
{
	pthread_mutex_lock(philo->philo_die_mutex);
	if ((return_time() - philo->start_program_time - philo->time_philo) > philo->time_to_die)
	{
		**flag_die = 1;
		pthread_mutex_unlock(philo->philo_die_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->philo_die_mutex);
	return (0);
}

int	respected_philosophers(t_philo_data ***philo, pthread_mutex_t ***mutex, int count)
{
	int i;
	int *flag_die = malloc(sizeof(int));
	*flag_die = 0;
	for(int j = 0; j < count; j++)
		(*philo)[j]->ptr_philo_die = flag_die;
	if (init_options(philo, count, -1))
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
		while (++i < count)
		{
			if (death_check((*philo)[i], &flag_die))
			{			
				printf("%lld %d died\n", (return_time() - (*philo)[i]->start_program_time), (*philo)[i]->index_philosophers);
				if (pthread_join(*(*philo)[i]->thread_philo, NULL))
					return (del_philosophers(philo, mutex, count, THREAD_ERROR));
			}
		}
	}
	free_global(philo, NULL, NULL);
	// system("leaks philo");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	pthread_mutex_t	**mutex;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_mutex(&philo, &mutex, mas[0]))
		return (del_philosophers(&philo, &mutex, mas[0], MALLOC_ERROR));
	if (respected_philosophers(&philo, &mutex, mas[0]))
		return (1);
	// int *flag_die = malloc(sizeof(int));
	// *flag_die = 0;
	// for(int j = 0; j < mas[0]; j++)
	// {
	// 	philo[j]->ptr_philo_die = *flag_die;
	// 	printf("%d\n", philo[j]->ptr_philo_die);
	// }
	// death_check(0, 0, &flag_die);
	// for(int j = 0; j < mas[0]; j++)
	// {
	// 	philo[j]->ptr_philo_die = *flag_die;
	// 	printf("%d\n", philo[j]->ptr_philo_die);
	// }
	// sleep(4);
	// printf("%lld\n", (return_time() - philo[0]->time_philo - philo[0]->start_program_time));
	// printf("%lld\n", philo[0]->time_to_die);
	// printf("time_to_eat = %lld\n", philo[0]->time_philo);
	// printf("time_to_die = %lld\n", philo[0]->time_to_die);
	// sleep(5);
	// printf("time = %lld\n", return_time());
	// if ((return_time() - philo[0]->time_philo) > philo[0]->time_to_die)
	// 	printf("die\n");
	// struct timeval oper;
	// gettimeofday(&oper, NULL);
	// long long time = oper.tv_sec * 1000 + oper.tv_usec / 1000;
	// printf("time = %lld\n", time / 1000);
	// long long time = return_time();
	// sleep(1);
	// printf("time = %lld\n", (return_time() - time) / 1000);
	// sleep(2);
	// printf("time = %lld\n", (return_time() - time) / 1000);
	// sleep(3);
	// printf("time = %lld\n", (return_time() - time) / 1000);
	del_philosophers(&philo, &mutex, mas[0], FINISH_PROGRAM);
	// system("leaks philo");
	return (0);
}
