/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:58:18 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:19 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

long long	return_time(void)
{
	struct timeval	time;
	long long		start_program;

	gettimeofday(&time, NULL);
	start_program = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (start_program);
}

void	ft_usleep(long long ms)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&now, NULL);
	gettimeofday(&start, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000 + \
		(now.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(10);
		gettimeofday(&now, NULL);
	}
}
