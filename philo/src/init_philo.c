#include "philosophers.h"

int	init_pilo(t_philo_data ***philo, int mas[5])
{
	int	i;

	i = -1;
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
	}
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
	return (0);
}
