/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:57:50 by aafrikya          #+#    #+#             */
/*   Updated: 2023/05/20 20:57:51 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	negative;
	long long	result;

	i = 0;
	negative = 1;
	result = 0;
	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
		result = 10 * result + (str[i++] - '0');
	return (result * negative);
}

int	check_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '+' && i == 0)))
			return (1);
		i++;
	}
	return (0);
}

int	fifth_arg(char *arg)
{
	if (arg == NULL)
		return (-42);
	return (ft_atoi(arg));
}

int	correct_args(int argc, char **argv, int mas[5])
{
	size_t		i;
	long long	checker;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		if (check_number(argv[i]))
			return (1);
		checker = ft_atoi(argv[i]);
		if (checker < 0 || checker > 4294967295)
			return (1);
		i++;
	}
	i = -1;
	while (++i < 4)
		mas[i] = ft_atoi(argv[i + 1]);
	mas[i] = fifth_arg(argv[5]);
	return (0);
}
