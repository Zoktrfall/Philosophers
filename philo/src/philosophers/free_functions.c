#include "philosophers.h"

int	free_pilo(t_philo_data ***philo, int mas[5])
{
	int	i;

	i = -1;
	if (*philo == NULL)
		return (printf("Malloc error!\n"));
	while (++i < mas[0])
	{
		if ((*philo)[i] == NULL)
			break ;
		free((*philo)[i]);
	}
	return (printf("Malloc error!\n"));
}
