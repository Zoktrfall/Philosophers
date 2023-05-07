#include "philosophers.h"

// void	*thread_philo(void	*philo_arg)
// {
// 	printf("Hello\n");
// }


// int	respected_philosophers(t_philo_data ***philo, pthread_mutex_t ***mutex, int count)
// {
// 	int i;

// 	i = -1;
// 	while (++i < count)
// 	{
// 		if (pthread_create((*philo)[i]->thread_philo, NULL, \
// 			thread_philo, (*philo)[i]))
// 			return (del_philosophers(philo, mutex, count, THREAD_ERROR));
// 	}
// 	return 0;
// }

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	pthread_mutex_t	**mutex;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas) || init_mutex(&philo, &mutex, mas[0]))
		return (del_philosophers(&philo, &mutex, mas[0], MALLOC_ERROR));
	// if (respected_philosophers(&philo, &mutex, mas[0]))
	// 	return (1);
	// for(int i = 0; i < mas[0]; i++)
	// {
	// 	if (philo[i] == NULL)
	// 		return printf("exav\n");
	// 	printf("phile[%d]->thread_philo= %d\n", i, philo[i]->thread_philo);
	// 	printf("philo[%d]->philosophers = %d\n", i, philo[i]->philosophers);
	// 	printf("philo[%d]->index_philosophers = %d\n", i, philo[i]->index_philosophers);
	// 	printf("philo[%d]->time_to_die = %d\n", i, philo[i]->time_to_die);
	// 	printf("philo[%d]->time_to_eat = %d\n", i, philo[i]->time_to_eat);
	// 	printf("philo[%d]->time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	// 	printf("philo[%d]->optional_argument = %d\n", i, philo[i]->optional_argument);
	// 	printf("philo[%d]->fork_left = %d\n", i, philo[i]->fork_left);
	// 	printf("philo[%d]->fork_right = %d\n", i, philo[i]->fork_right);
	// 	printf("\n");
	// }
	del_philosophers(&philo, &mutex, mas[0], FINISH_PROGRAM);
	// system("leaks philo");
	return (0);
}
