/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:58:23 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:24 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eat_sleep_think(t_philo_data *philo)
{
	philo->time_philo = return_time() - \
	philo->start_program_time + philo->time_philo;
	print_philo_action(philo, EAT);
	if (philo->optional_argument >= 0)
		philo->eat_count++;
	if (death_check(philo, 0))
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

void	start_philo(t_philo_data *philo)
{
	while (philo->eat_count != philo->optional_argument)
	{
		if (death_check(philo, 0))
		{
			print_philo_action(philo, DIE);
			sem_post(philo->check_end);
			exit(0);
		}
		sem_wait(philo->forks);
		print_philo_action(philo, FORK);
		if (death_check(philo, 1))
		{
			print_philo_action(philo, DIE);
			sem_post(philo->check_end);
			exit(0);
		}
		sem_wait(philo->forks);
		print_philo_action(philo, FORK);
		eat_sleep_think(philo);
	}
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
