#include "libft.h"
#include <signal.h>

void	send_char(int pid, char c)
{
	char	bit;
	char	mask;

	bit = 0;
	mask = 0b10000000;
	while (bit < 8)
	{
		if ((c & mask) != mask)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c <<= 1;
		bit++;
		usleep(100);
	}
}

void	send_message(int pid, char *msg)
{
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	if (argc != 3)
		return (1);
	i = 0;
	while (i < ft_strlen(argv[1]))
	{
		if (!ft_isdigit(argv[1][i]))
			return (1);
		i++;
	}
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}