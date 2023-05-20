/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:58:00 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:01 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_philo_data *philo)
{
	pthread_mutex_lock(philo->check_die);
	if (*(philo->ptr_philo_die))
	{
		pthread_mutex_unlock(philo->check_die);
		return (1);
	}
	pthread_mutex_unlock(philo->check_die);
	pthread_mutex_lock(philo->fork_left);
	print_philo_action(philo, FORK);
	pthread_mutex_lock(philo->check_die);
	if (*(philo->ptr_philo_die) || philo->philosophers == 1)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->check_die);
		return (1);
	}
	pthread_mutex_unlock(philo->check_die);
	pthread_mutex_lock(philo->fork_right);
	print_philo_action(philo, FORK);
	return (0);
}

int	eat_sleep_think(t_philo_data *philo)
{
	pthread_mutex_lock(philo->time_philo_mutex);
	philo->time_philo = return_time() - \
		philo->start_program_time + philo->time_philo;
	pthread_mutex_unlock(philo->time_philo_mutex);
	print_philo_action(philo, EAT);
	pthread_mutex_lock(philo->adding_eat);
	if (philo->optional_argument >= 0)
		philo->eat_count++;
	pthread_mutex_unlock(philo->adding_eat);
	pthread_mutex_lock(philo->check_die);
	if (*(philo->ptr_philo_die))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->check_die);
		return (1);
	}
	pthread_mutex_unlock(philo->check_die);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	print_philo_action(philo, SLEEP);
	ft_usleep(philo->time_to_sleep);
	print_philo_action(philo, THINK);
	return (0);
}

void	*thread_philo(void	*philo_arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)philo_arg;
	if (philo->index_philosophers % 2 == 0)
		usleep(1000);
	while (philo->eat_count != philo->optional_argument)
	{
		if (take_fork(philo))
			return (NULL);
		if (eat_sleep_think(philo))
			return (NULL);
	}
	return (NULL);
}

int	respected_philosophers(t_philo_data ***philo, \
	pthread_mutex_t ***mutex, int count, pthread_mutex_t *global[5])
{
	int	*flag_die;
	int	i;

	i = -1;
	flag_die = init_flag_die(philo, count);
	if (flag_die == NULL)
		return (del_philosophers(philo, mutex, count, MALLOC_ERROR));
	if (init_global_mutex(philo, count, global))
		return (del_philosophers(philo, mutex, count, MALLOC_ERROR));
	while (++i < count)
	{
		if (pthread_create((*philo)[i]->thread_philo, NULL, \
			thread_philo, (*philo)[i]))
			return (free_return(&flag_die, 1));
	}
	check_end(count, philo, flag_die);
	i = -1;
	while (++i < count)
	{
		if (pthread_join(*(*philo)[i]->thread_philo, NULL))
			return (free_return(&flag_die, 1));
	}
	return (free_return(&flag_die, 0));
}
