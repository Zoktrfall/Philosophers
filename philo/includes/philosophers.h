/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:57:47 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:57:48 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

// Error Codes and Their Prints
# define FINISH_PROGRAM 0
# define MALLOC_ERROR 1
# define THREAD_ERROR 2
# define PRINT_MALLOC_ERROR "Malloc error\n"
# define PRINT_THREAD_ERROR "Error when creating or joining a thread\n"

//  Prints
# define PHILO_DIE "%lld %d died\n"
# define PHILO_EAT "%lld %d is eating\n"
# define PHILO_SLEEP "%lld %d is sleeping\n"
# define PHILO_FORK "%lld %d has taken a fork\n"
# define PHILO_THINK "%lld %d is thinking\n"

//  Flags for the Print Function
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4

typedef struct s_philo_data {
	pthread_t		*thread_philo;
	int				philosophers;
	int				index_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				optional_argument;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	long long		time_philo;
	long long		start_program_time;
	int				*ptr_philo_die;
	pthread_mutex_t	*check_die;
	pthread_mutex_t	*adding_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*philo_die_mutex;
	pthread_mutex_t	*time_philo_mutex;
}	t_philo_data;

/*  'Global Mutexes'
	pthread_mutex_t	*check_die;
	pthread_mutex_t	*adding_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*philo_die_mutex;
	pthread_mutex_t	*time_philo_mutex; */

//  Correct Args
int			correct_args(int argc, char **argv, int mas[5]);
int			check_number(char *str);
int			fifth_arg(char *arg);
long long	ft_atoi(const char *str);

//	Init Philosophers
int			*init_flag_die(t_philo_data ***philo, int count);
int			init_threads(t_philo_data ***philo, int count);
int			init_pilo(t_philo_data ***philo, int mas[5], int i);
int			init_global_mutex(t_philo_data ***philo, \
				int count, pthread_mutex_t *mas[5]);
int			init_mutex(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int count);

//  Thread_philo
int			take_fork(t_philo_data *philo);
int			eat_sleep_think(t_philo_data *philo);
void		*thread_philo(void	*philo_arg);
int			respected_philosophers(t_philo_data ***philo, \
			pthread_mutex_t ***mutex, int count, pthread_mutex_t *global[5]);

//  Philo Utils
void		print_philo_action(t_philo_data *philo, int flag);
int			death_check(t_philo_data *philo, int **flag_die);
int			end_program(t_philo_data **philo, int count);
void		check_end(int count, t_philo_data ***philo, int *flag_die);

//  Utils
void		*ft_calloc(size_t num, size_t size);
long long	return_time(void);
void		ft_usleep(long long ms);

//	Free Functions
int			free_mutex_mas(pthread_mutex_t *mas[5], int end);
void		free_philo(t_philo_data ***philo, int count);
int			free_return(int **flag_die, int value);
void		free_mutex(pthread_mutex_t ***mutex, int count);
int			del_philosophers(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int mas_0, int end_program);

#endif