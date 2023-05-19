#include "philosophers_bonus.h"

int	end_process(t_philo_data ***philo, int end)
{
	int	i;

	i = -1;
	while (++i <= end)
		kill((*philo)[i]->process_philo, SIGTERM);
	return (1);
}

void	respected_philosophers(t_philo_data ***philo, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		(*philo)[i]->process_philo = fork();
		if ((*philo)[i]->process_philo < 0)
			exit(printf(PRINT_PROCESS_ERROR));
		if ((*philo)[i]->process_philo == 0)
		{
			if ((*philo)[i]->index_philosophers % 2 == 0)
				usleep(1000);
		}
	}
}

int main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1) || init_sem(&philo, mas[0]))
		exit(printf(PRINT_MALLOC_ERROR));
	respected_philosophers(&philo, mas[0]);
	del_philosophers(&philo, mas[0], FINISH_PROGRAM);
	return (0);
}