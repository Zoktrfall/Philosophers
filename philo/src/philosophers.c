#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	pthread_mutex_t	**mutex;
	int				mas[5];
	pthread_mutex_t	*global[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_mutex(&philo, &mutex, mas[0]))
		return (del_philosophers(&philo, &mutex, mas[0], MALLOC_ERROR));
	if (respected_philosophers(&philo, &mutex, mas[0], global))
	{
		free_mutex_mas(global, 4);
		del_philosophers(&philo, &mutex, mas[0], THREAD_ERROR);
		return (1);
	}
	free_mutex_mas(global, 4);
	del_philosophers(&philo, &mutex, mas[0], FINISH_PROGRAM);
	return (0);
}
