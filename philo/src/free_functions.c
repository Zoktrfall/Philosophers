#include "philosophers.h"

void	free_philo(t_philo_data ***philo, int count)
{
	int	i;

	i = -1;
	if (*philo == NULL)
		return ;
	while (++i < count)
	{
		if ((*philo)[i] == NULL)
			break ;
		free((*philo)[i]);
	}
	free(*philo);
}

void	free_mutex(pthread_mutex_t ***mutex, int count)
{
	int	i;

	i = -1;
	if (*mutex == NULL)
		return ;
	while (++i < count)
	{
		if ((*mutex)[i] == NULL)
			break ;
		pthread_mutex_destroy((*mutex)[i]);
		free((*mutex)[i]);
	}
	free(*mutex);
}

int	del_philosophers(t_philo_data ***philo, \
	pthread_mutex_t ***mutex, int mas[5], int end_program)
{
	free_philo(philo, mas[0]);
	free_mutex(mutex, mas[0]);
	if (end_program == 0)
	{
		printf("Malloc error\n");
		return (1);
	}
	return (0);
}
