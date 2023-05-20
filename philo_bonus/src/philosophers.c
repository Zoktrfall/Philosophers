#include "philosophers_bonus.h"

void	start_philo(t_philo_data *philo)
{
	while (philo->eat_count != philo->optional_argument)
	{
		if (death_check(philo))
		{
			print_philo_action(philo, DIE);
			sem_post(philo->check_end);
			exit(0);
		}
		sem_wait(philo->forks);
		print_philo_action(philo, FORK);
		if (death_check(philo) || philo->philosophers == 1)
		{
			print_philo_action(philo, DIE);
			sem_post(philo->check_end);
			exit(0);
		}
		sem_wait(philo->forks);
		print_philo_action(philo, FORK);
		philo->time_philo = return_time() - \
			philo->start_program_time + philo->time_philo;
		print_philo_action(philo, EAT);
		if (philo->optional_argument >= 0)
			philo->eat_count++;
		if (death_check(philo))
		{
			print_philo_action(philo, DIE);
			sem_post(philo->check_end);
			exit(0);
		}
		ft_usleep(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		print_philo_action(philo, SLEEP);
		ft_usleep(philo->time_to_sleep);
		print_philo_action(philo, THINK);
	}
}

void	finish_program(t_philo_data ***philo, int count, pthread_t	*thread)
{
	int	i;

	i = -1;
	sem_wait((*philo)[0]->check_end);
	if (pthread_create(thread, NULL, check_eat, (*philo)))
		exit(printf(PRINT_THREAD_ERROR));
	sem_wait((*philo)[0]->check_end);
	if (pthread_detach(*thread))
		exit(printf(PRINT_THREAD_ERROR));
	while (++i < (*philo)[0]->philosophers)
		kill((*philo)[i]->process_philo, SIGTERM);
	ft_usleep(100);
}

void	respected_philosophers(t_philo_data ***philo, int count)
{
	int			i;
	pthread_t	*thread;

	i = -1;
	thread = malloc(sizeof(pthread_t));
	if (thread == NULL)
		exit(printf(PRINT_MALLOC_ERROR));
	while (++i < count)
	{
		(*philo)[i]->process_philo = fork();
		if ((*philo)[i]->process_philo < 0)
			exit(printf(PRINT_PROCESS_ERROR));
		if ((*philo)[i]->process_philo == 0)
		{
			if ((*philo)[i]->index_philosophers % 2 == 0)
				usleep(1000);
			start_philo((*philo)[i]);
			exit(0);
		}
	}
	finish_program(philo, count, thread);
	free(thread);
}

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_sem(&philo, mas[0]))
		exit(printf(PRINT_MALLOC_ERROR));
	respected_philosophers(&philo, mas[0]);
	del_philosophers(&philo, mas[0], FINISH_PROGRAM);
	// system("leaks philo_bonus");
	return (0);
}
