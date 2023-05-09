#include "philosophers.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*str;
	size_t	i;	

	if (num == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	str = (void *)malloc(num * size);
	if (str != NULL)
	{
		i = 0;
		while (i < num * size)
		{
			*(char *)(str + i) = 0;
			i++;
		}
		return (str);
	}
	return (NULL);
}

long long	retrun_time(void)
{
	struct timeval	time;
	long long 		start_program;

	gettimeofday(&time, NULL);
	start_program = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (start_program);
}
