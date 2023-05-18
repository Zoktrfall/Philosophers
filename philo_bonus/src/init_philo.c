#include "philosophers_bonus.h"

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
		(*philo)[i]->time_philo = 0;
		(*philo)[i]->eat_count = 0;
		(*philo)[i]->start_program_time = start;
	}
	return (0);
}
