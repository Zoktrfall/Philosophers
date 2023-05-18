#include "philosophers.h"

int main(int argc, char *argv[])
{
    t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1))
		return (1);
    for(int i = 0; i < mas[0]; i++)
    {
        printf("mas[%d] forks = %d\n", philo[i].forks)
    }
}