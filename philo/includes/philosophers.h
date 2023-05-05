#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

//  Correct Args
int			correct_args(int argc, char **argv);
int			check_number(char *str);
long long	ft_atoi(const char *str);

#endif