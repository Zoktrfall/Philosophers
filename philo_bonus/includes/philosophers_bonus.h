#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <string.h>
# include <semaphore.h>

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
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*check_end;
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

//	Init Philosophers
int	init_pilo(t_philo_data ***philo, int mas[5], int i);

//  Utils
void		*ft_calloc(size_t num, size_t size);
long long	return_time(void);
void		ft_usleep(long long ms);

#endif