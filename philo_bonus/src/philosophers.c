#include "philosophers_bonus.h"

void	print_philo_action(t_philo_data *philo, int flag)
{
	sem_wait(philo->print_sem);
	if (flag == FORK)
		printf(PHILO_FORK, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == EAT)
		printf(PHILO_EAT, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == THINK)
		printf(PHILO_THINK, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == SLEEP)
		printf(PHILO_SLEEP, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
	if (flag == DIE)
	{
		printf(PHILO_DIE, (return_time() - \
			philo->start_program_time), philo->index_philosophers);
		return ;
	}
	sem_post(philo->print_sem);
}

int	death_check(t_philo_data *philo)
{
	if ((return_time() - philo->start_program_time \
		- philo->time_philo) > philo->time_to_die)
		return (1);
	return (0);
}

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

void	*check_eat(void *ph)
{
	int				i;
	t_philo_data	*philo;

	philo = ph;
	i = -1;
	while (++i < philo->philosophers)
		waitpid(philo->process_philo, NULL, 0);
	sem_post(philo->check_end);
	return (NULL);
}

void	respected_philosophers(t_philo_data ***philo, int count)
{
	int	i;
	pthread_t	*thread = malloc(sizeof(pthread_t));

	i = -1;
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
	sem_wait((*philo)[0]->check_end);
	pthread_create(thread, NULL, check_eat, philo);
		// write(1, "helav\n", 6);
	
	sem_wait((*philo)[0]->check_end);
	write(1, "helav\n", 6);
	pthread_detach(*thread);
	i = -1;
	while (++i < (*philo)[0]->philosophers)
		kill((*philo)[i]->process_philo, SIGTERM);
	printf("end program\n");
}

int main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_sem(&philo, mas[0]))
		exit(printf(PRINT_MALLOC_ERROR));
	respected_philosophers(&philo, mas[0]);
	del_philosophers(&philo, mas[0], FINISH_PROGRAM);
	return (0);
}