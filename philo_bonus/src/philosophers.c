#include "philosophers_bonus.h"

int init_sem(t_philo_data ***philo, int count)
{
	int		i;
	sem_t	*print_s;
	sem_t	*forks_s;
	sem_t	*end_s;

	i = -1;
	printf("count %d\n", count);
	print_s = sem_open("/my_semaphore", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, 1);
	end_s = sem_open("/my_semaphore2", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, 1);
	forks_s = sem_open("/my_semaphore3", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, count);
	printf("%d\n", print_s);
	printf("%d\n", end_s);
	printf("%d\n", forks_s);
	if (print_s == SEM_FAILED || end_s == SEM_FAILED || forks_s == SEM_FAILED)
	{
		printf("eror\n");
		return (1);
	}
	while (++i < count)
	{
		(*philo)[i]->forks = forks_s;
		(*philo)[i]->print_sem = print_s;
		(*philo)[i]->check_end = end_s;
	}
	printf("hasav\n");
	return (0);
}

int main(int argc, char *argv[])
{
	t_philo_data	**philo;
	int				mas[5];

	if (correct_args(argc, argv, mas))
		return (printf("Invalid arguments entered\n"));
	if (init_pilo(&philo, mas, -1))
		return (1);
	if (init_sem(&philo, mas[0]));
	{
		printf("mutq\n");
		return (1);
	}
	printf("wtf\n");
	for(int i = 0; i < mas[0]; i++)
	{
		printf("philo[%d] : *forks = %d\n", i, philo[i]->forks);
		printf("philoe[%d] : *print_sem = %d\n", i,  philo[i]->print_sem);
		printf("philoe[%d] : check_end = %d\n", i, philo[i]->check_end);
		printf("philoe[%d] : process_philo = %d\n", i, philo[i]->process_philo);
		printf("philoe[%d] : philosophers = %d\n", i, philo[i]->philosophers);
		printf("philoe[%d] : index_philosophers = %d\n", i, philo[i]->index_philosophers);
		printf("philoe[%d] : time_die = %d\n", i, philo[i]->time_to_die);
		printf("philoe[%d] : time_to_eat = %d\n", i, philo[i]->time_to_eat);
		printf("philoe[%d] : time_to_sleep = %d\n", i, philo[i]->time_to_sleep);
	    printf("philoe[%d] : eat_count = %d\n", i, philo[i]->eat_count);
		printf("philoe[%d] : optional_argument = %d\n", i, philo[i]->optional_argument);
		printf("philoe[%d] : start_program_time = %d\n", i, philo[i]->start_program_time);
		printf("\n");
	}
	return (0);
}