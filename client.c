#include "libft.h"
#include <signal.h>
#include <fcntl.h>

typedef struct s_client
{
	int		pid_server;
	char	*msg;
	int		bit;
}	t_client;

t_client	client;

void	send_next_bit()
{
	int	next_bit;

	next_bit = (client.msg[0] >> (7 - client.bit)) & (1 << 7);
	client.msg[0] <<= 1;
	client.bit++;
	if (client.bit == 8)
	{
		client.bit = 0;
		client.msg++;
	}
	if (next_bit)
		kill(client.pid_server, SIGUSR2);
	else
		kill(client.pid_server, SIGUSR1);
}

void	s1_handler()
{
	send_next_bit();
}

void	s2_handler()
{
	ft_printf("Server has received your message !\n");
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
		return (1);
	i = 0;
	while (i < (int)ft_strlen(argv[1]))
	{
		if (!ft_isdigit(argv[1][i]))
			return (1);
		i++;
	}
	signal(SIGUSR1, s1_handler);
	signal(SIGUSR2, s2_handler);

	client.pid_server = ft_atoi(argv[1]);
	client.msg = argv[2];
	client.bit = 0;

	send_next_bit();

	while (TRUE)
		pause();
	return (0);
}