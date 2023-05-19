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

int	init_sem(t_philo_data ***philo, int count)
{
	int		i;
	sem_t	*print_s;
	sem_t	*forks_s;
	sem_t	*end_s;

	i = -1;
	unlink_sem(print_s, end_s, forks_s);
	print_s = sem_open("/my_semaphore", \
		O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, 1);
	end_s = sem_open("/my_semaphore2", \
		O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, 1);
	forks_s = sem_open("/my_semaphore3", \
		O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, count);
	if (print_s == SEM_FAILED || end_s == SEM_FAILED || forks_s == SEM_FAILED)
		return (unlink_sem(print_s, end_s, forks_s));
	while (++i < count)
	{
		(*philo)[i]->forks = forks_s;
		(*philo)[i]->print_sem = print_s;
		(*philo)[i]->check_end = end_s;
	}
	return (0);
}
