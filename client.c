#include "libft.h"
#include <signal.h>

int	main(int argc, char *argv[])
{
	int	pid = ft_atoi(argv[1]);
	kill(pid, SIGUSR1);
	return (0);
}