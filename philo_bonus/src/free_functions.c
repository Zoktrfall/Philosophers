/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:58:17 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:18 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

int	del_philosophers(t_philo_data ***philo,
	int mas_0, int end_program)
{
	unlink_sem((*philo)[0]->print_sem, (*philo)[0]->check_end, \
		(*philo)[0]->forks);
	free_philo(philo, mas_0);
	return (0);
}

int	unlink_sem(sem_t *print_s, sem_t *end_s, sem_t *forks_s)
{
	if (forks_s != SEM_FAILED)
	{
		sem_close(forks_s);
		sem_unlink("/my_semaphore");
	}
	if (end_s != SEM_FAILED)
	{
		sem_close(end_s);
		sem_unlink("/my_semaphore2");
	}
	if (print_s != SEM_FAILED)
	{
		sem_close(print_s);
		sem_unlink("/my_semaphore3");
	}
	return (1);
}
