#include "philosophers.h"

int init_pilo(t_philo_data ***philo, int mas[5])
{
	int	i;

	i = -1;
	*philo = ft_calloc(mas[0], sizeof(t_philo_data *));
	if (*philo == NULL)
		return (1);
	while(++i < mas[0])
	{
		(*philo)[i] = ft_calloc(1, sizeof(t_philo_data));
		if ((*philo)[i] == NULL)
			return (1);
		(*philo)[i]->philosophers = mas[0];
		(*philo)[i]->index_philosophers = i + 1;
		(*philo)[i]->time_to_die = mas[1];
		(*philo)[i]->time_to_eat = mas[2];
		(*philo)[i]->time_to_sleep = mas[3];
		(*philo)[i]->optional_argument = mas[4];
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int			mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	// for(int i = 0; i < 5; i++)
	// 	printf("mas[%d] = %d\n", i, mas[i]);
	if (init_pilo(&philo, mas))
		return (free_pilo(&philo, mas));
	
	// for(int i = 0; i < mas[0]; i++)
	// {
	// 	if (philo[i] == NULL)
	// 		return printf("exav\n");
	// 	printf("pilo[%d]->philosophers = %d\n", i, philo[i]->philosophers);
	// 	printf("pilo[%d]->index_philosophers = %d\n", i, philo[i]->index_philosophers);
	// 	printf("pilo[%d]->time_to_die = %d\n", i, philo[i]->time_to_die);
	// 	printf("pilo[%d]->time_to_eat = %d\n", i, philo[i]->time_to_eat);
	// 	printf("pilo[%d]->time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	// 	printf("pilo[%d]->optional_argument = %d\n", i, philo[i]->optional_argument);
	// }
	return (0);
}
