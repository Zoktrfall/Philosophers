#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	pthread_mutex_t	**mutex;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	// for(int i = 0; i < 5; i++)
	// 	printf("mas[%d] = %d\n", i, mas[i]);
	if (init_pilo(&philo, mas) || init_mutex(&philo, &mutex, mas[0]))
		return (del_philosophers(&philo, &mutex, mas, 0));

	
	// for(int i = 0; i < mas[0]; i++)
	// {
	// 	if (philo[i] == NULL)
	// 		return printf("exav\n");
	// 	printf("philo[%d]->philosophers = %d\n", i, philo[i]->philosophers);
	// 	printf("philo[%d]->index_philosophers = %d\n", i, philo[i]->index_philosophers);
	// 	printf("philo[%d]->time_to_die = %d\n", i, philo[i]->time_to_die);
	// 	printf("philo[%d]->time_to_eat = %d\n", i, philo[i]->time_to_eat);
	// 	printf("philo[%d]->time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	// 	printf("philo[%d]->optional_argument = %d\n", i, philo[i]->optional_argument);
	// 	printf("philo[%d]->fork_left = %d\n", i, philo[i]->fork_left);
	// 	printf("philo[%d]->fork_right = %d\n", i, philo[i]->fork_right);
	// }
	// system("leaks philo");
	return (0);
}
