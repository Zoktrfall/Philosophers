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
