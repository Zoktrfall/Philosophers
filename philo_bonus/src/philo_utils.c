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

void	*check_eat(void *ph)
{
	int				i;
	t_philo_data	**philo;

	philo = ph;
	i = -1;
	while (++i < (philo)[0]->philosophers)
		waitpid((philo)[i]->process_philo, NULL, 0);
	sem_post(philo[0]->check_end);
	return (NULL);
}
