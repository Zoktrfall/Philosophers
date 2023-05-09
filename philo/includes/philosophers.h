#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define FINISH_PROGRAM 0
# define MALLOC_ERROR 1
# define THREAD_ERROR 2
# define JOIN_ERROR 3
# define PRINT_MALLOC_ERROR "Malloc error\n"
# define PRINT_THREAD_ERROR "Error creating thread\n"
# define PRINT_JOIN_ERROR "Error in join\n"

typedef struct s_philo_data {
	pthread_t		*thread_philo;
	int				philosophers;
	int				index_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional_argument;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	long long		time_philo;
	long long		start_program_time;
	int				*ptr_philo_die;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*philo_die_mutex;
}	t_philo_data;

//  Correct Args
int			correct_args(int argc, char **argv, int mas[5]);
int			check_number(char *str);
int			fifth_arg(char *arg);
long long	ft_atoi(const char *str);

//	Init Philosophers
int			init_threads(t_philo_data ***philo, int count);
int			init_pilo(t_philo_data ***philo, int mas[5]);
int			init_options(t_philo_data ***philo, int count);
int			init_mutex(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int count);

//  Utils
void		*ft_calloc(size_t num, size_t size);
long long	retrun_time(void);

//	Free Functions
void		free_philo(t_philo_data ***philo, int count);
void		free_mutex(pthread_mutex_t ***mutex, int count);
int			free_global(t_philo_data ***philo, \
				pthread_mutex_t *str, pthread_mutex_t *ptr);
int			del_philosophers(t_philo_data ***philo, \
				pthread_mutex_t ***mutex, int mas_0, int end_program);

#endif