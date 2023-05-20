/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:58:21 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:22 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	death_check(t_philo_data *philo, int flag)
{
	if (flag && philo->philosophers == 1)
	{
		ft_usleep(philo->time_to_die + 1);
		return (1);
	}
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
