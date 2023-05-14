#include "philosophers.h"

void	*thread_philo(void	*philo_arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)philo_arg;
	if (philo->index_philosophers %  2 == 0)
		usleep(1000);
	while (philo->eat_count != philo->optional_argument)
	{
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->print_mutex);
		printf(PHILO_FORK, (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die) || philo->philosophers == 1)
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->print_mutex);
		printf(PHILO_FORK, (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->time_philo_mutex);
		philo->time_philo = return_time() - philo->start_program_time + philo->time_philo;
		pthread_mutex_unlock(philo->time_philo_mutex);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->print_mutex);
		printf(PHILO_EAT, (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->adding_eat);
		if (philo->optional_argument >= 0)
			philo->eat_count++;
		pthread_mutex_unlock(philo->adding_eat);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->print_mutex);
		printf(PHILO_SLEEP, (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
		ft_usleep(philo->time_to_sleep);
		pthread_mutex_lock(philo->check_die);
		if (*(philo->ptr_philo_die))
		{
			pthread_mutex_unlock(philo->check_die);
			return NULL;
		}
		pthread_mutex_unlock(philo->check_die);
		pthread_mutex_lock(philo->print_mutex);
		printf(PHILO_THINK, (return_time() - philo->start_program_time), philo->index_philosophers);
		pthread_mutex_unlock(philo->print_mutex);
	}
	return NULL;
}

int	respected_philosophers(t_philo_data ***philo, pthread_mutex_t ***mutex, int count, int i)
{
	int 			*flag_die;
	pthread_mutex_t	*mas[5];

	flag_die = init_flag_die(philo, count);
	if (flag_die == NULL)
		return (del_philosophers(philo, mutex, count, MALLOC_ERROR));
	if (init_global_mutex(philo, count, mas))
		return (del_philosophers(philo, mutex, count, MALLOC_ERROR));
	while (++i < count)
	{
		if (pthread_create((*philo)[i]->thread_philo, NULL, \
			thread_philo, (*philo)[i]))
			return (del_philosophers(philo, mutex, count, THREAD_ERROR));
	}
	check_end(count, philo, flag_die);
	i = -1;
	while (++i < count)
	{
		if (pthread_join(*(*philo)[i]->thread_philo, NULL))
			return (del_philosophers(philo, mutex, count, THREAD_ERROR));
	}
	free_mutex_mas(mas, 4);
	free(flag_die);
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
	if (respected_philosophers(&philo, &mutex, mas[0], -1))
	{
		// system("leaks philo");
		return (1);
	}
	// system("leaks philo");
	return (0);
}
