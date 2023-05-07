#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo_data {
	int				philosophers;
	int				index_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional_argument;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	int				time_pilo;
}	t_philo_data;

//  Correct Args
int			correct_args(int argc, char **argv, int mas[5]);
int			check_number(char *str);
int			fifth_arg(char *arg);
long long	ft_atoi(const char *str);

//	Init Philosophers
int			init_pilo(t_philo_data ***philo, int mas[5]);
int			init_mutex(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int count);

//  Utils
void		*ft_calloc(size_t num, size_t size);

//	Free Functions
void		free_philo(t_philo_data ***philo, int count);
void		free_mutex(pthread_mutex_t ***mutex, int count);
int			del_philosophers(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int mas[5], int end_program);

#endif