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
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
	int				time_pilo;
}	t_philo_data;

//  Correct Args
int			correct_args(int argc, char **argv, int mas[5]);
int			check_number(char *str);
int			fifth_arg(char *arg);
long long	ft_atoi(const char *str);

//  Utils
void		*ft_calloc(size_t num, size_t size);

//	Free Functions
int 		free_pilo(t_philo_data ***philo, int mas[5]);

#endif