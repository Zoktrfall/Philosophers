#include "philosophers.h"

int	main(int argc, char *argv[])
{
	if (correct_args(argc, argv))
		return (printf("Invalid arguments entered\n"));
	return (0);
}
