#include "philosophers_bonus.h"

int main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_sem(&philo, mas[0]))
		return (del_philosophers(&philo, mas[0], MALLOC_ERROR));
	// for(int i = 0; i < mas[0]; i++)
	// {
	// 	printf("philo[%d] : *forks = %d\n", i, philo[i]->forks);
	// 	printf("philoe[%d] : *print_sem = %d\n", i,  philo[i]->print_sem);
	// 	printf("philoe[%d] : check_end = %d\n", i, philo[i]->check_end);
	// 	printf("philoe[%d] : process_philo = %d\n", i, philo[i]->process_philo);
	// 	printf("philoe[%d] : philosophers = %d\n", i, philo[i]->philosophers);
	// 	printf("philoe[%d] : index_philosophers = %d\n", i, philo[i]->index_philosophers);
	// 	printf("philoe[%d] : time_die = %d\n", i, philo[i]->time_to_die);
	// 	printf("philoe[%d] : time_to_eat = %d\n", i, philo[i]->time_to_eat);
	// 	printf("philoe[%d] : time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	//     printf("philoe[%d] : eat_count = %d\n", i, philo[i]->eat_count);
	// 	printf("philoe[%d] : optional_argument = %d\n", i, philo[i]->optional_argument);
	// 	printf("philoe[%d] : start_program_time = %d\n", i, philo[i]->start_program_time);
	// 	printf("\n");
	// }
	return (0);
}