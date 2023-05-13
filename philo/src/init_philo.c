#include "philosophers.h"

int	init_pilo(t_philo_data ***philo, int mas[5], int i)
{
	long long	start;

	start = return_time();
	*philo = ft_calloc(mas[0], sizeof(t_philo_data *));
	if (*philo == NULL)
		return (1);
	while (++i < mas[0])
	{
		(*philo)[i] = ft_calloc(1, sizeof(t_philo_data));
		if ((*philo)[i] == NULL)
			return (1);
		(*philo)[i]->philosophers = mas[0];
		(*philo)[i]->index_philosophers = i + 1;
		(*philo)[i]->time_to_die = mas[1];
		(*philo)[i]->time_to_eat = mas[2];
		(*philo)[i]->time_to_sleep = mas[3];
		(*philo)[i]->optional_argument = mas[4];
		(*philo)[i]->fork_left = NULL;
		(*philo)[i]->fork_right = NULL;
		(*philo)[i]->time_philo = 0;
		(*philo)[i]->eat_count = 0;
		(*philo)[i]->start_program_time = start;
		(*philo)[i]->ptr_philo_die = NULL;
	}
	return (0);
}

int	init_threads(t_philo_data ***philo, int count)
{
	int			i;
	pthread_t	**threads;

	i = -1;
	threads = (pthread_t **)ft_calloc(count, sizeof(pthread_t *));
	if (threads == NULL)
		return (1);
	while (++i < count)
	{
		threads[i] = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
		if (threads[i] == NULL)
		{
			free(threads);
			return (1);
		}
		(*philo)[i]->thread_philo = threads[i];
	}
	free(threads);
	return (0);
}

int	init_mutex(t_philo_data ***philo, pthread_mutex_t ***mutex, int count)
{
	int				i;
	int				max;

	i = -1;
	*mutex = ft_calloc(count, sizeof(pthread_mutex_t *));
	if (mutex == NULL)
		return (1);
	while (++i < count)
	{
		(*mutex)[i] = ft_calloc(1, sizeof(pthread_mutex_t));
		if ((*mutex)[i] == NULL || pthread_mutex_init((*mutex)[i], NULL))
			return (1);
	}
	max = i;
	i = -1;
	while (++i < count)
	{
		if (i == 0)
			(*philo)[i]->fork_left = (*mutex)[max - 1];
		else
			(*philo)[i]->fork_left = (*mutex)[i - 1];
		(*philo)[i]->fork_right = (*mutex)[i];
	}
	return (init_threads(philo, count));
}

int	init_options(t_philo_data ***philo, int count, int i)
{
	int				philo_die;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	*die_m;
	pthread_mutex_t	*time_philo_mutex;

	philo_die = 0;
	print_m = NULL;
	die_m = NULL;
	print_m = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	die_m = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	time_philo_mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (print_m == NULL || die_m == NULL || time_philo_mutex == NULL
		|| pthread_mutex_init(print_m, NULL) || pthread_mutex_init(die_m, NULL)
		|| pthread_mutex_init(time_philo_mutex, NULL))
		return (free_global(NULL, print_m, die_m));
	while (++i < count)
	{
		(*philo)[i]->print_mutex = print_m;
		(*philo)[i]->philo_die_mutex = die_m;
		(*philo)[i]->time_philo_mutex = time_philo_mutex;
	}
	return (0);
}
