#include "client.h"

t_client	g_client;

void	send_next_bit(void)
{
	int	next_bit;

	next_bit = (g_client.msg[0] >> (7 - g_client.bit)) & (1 << 7);
	g_client.msg[0] <<= 1;
	g_client.bit++;
	if (g_client.bit == 8)
	{
		g_client.bit = 0;
		g_client.msg++;
	}
	if (next_bit)
		kill(g_client.pid_server, SIGUSR2);
	else
		kill(g_client.pid_server, SIGUSR1);
}

void	s1_handler(int signal)
{
	(void)signal;
	send_next_bit();
}

void	s2_handler(int signal)
{
	(void)signal;
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
	g_client.pid_server = ft_atoi(argv[1]);
	g_client.msg = argv[2];
	g_client.bit = 0;
	send_next_bit();
	while (TRUE)
		pause();
	return (0);
}
