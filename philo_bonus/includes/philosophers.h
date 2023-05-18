#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>

typedef struct s_philo_data {
	sem_t			*forks;
	pid_t			process_philo;
	int				philosophers;
	int				index_philosophers;
	int     		time_to_die;
	int		        time_to_eat;
	int     		time_to_sleep;
	int				eat_count;
	int				optional_argument;
	long long		time_philo;
	long long		start_program_time;
}	t_philo_data;

//  Correct Args
int			correct_args(int argc, char **argv, int mas[5]);
int			check_number(char *str);
int			fifth_arg(char *arg);
long long	ft_atoi(const char *str);

//  Utils
void		*ft_calloc(size_t num, size_t size);
long long	return_time(void);
void		ft_usleep(long long ms);

#endif