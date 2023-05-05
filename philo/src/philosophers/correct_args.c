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

int	correct_args(int argc, char **argv)
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
	return (0);
}
