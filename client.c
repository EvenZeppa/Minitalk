#include "libft.h"
#include <signal.h>
#include <fcntl.h>

int	is_bit_received;

void	send_pid(int pid_server)
{
	int	pid;
	int	bits;
	int	bit;

	pid = getpid();
	bits = sizeof(int) * 8;
	while (--bits >= 0)
	{
		bit = (pid >> bits) & 1;
		if (!bit)
			kill(pid_server, SIGUSR1);
		else
			kill(pid_server, SIGUSR2);
		usleep(1000);
	}
}

void	handle(){
	is_bit_received = 1;
}

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
		if (!is_bit_received)
			pause();
		is_bit_received = 0;
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

void	received()
{
	is_bit_received = 1;
	ft_printf("Server has received your message !\n");
}

int	main(int argc, char *argv[])
{
	int	pid_server;
	int	i;

	is_bit_received = 0;
	signal(SIGUSR1, handle);
	signal(SIGUSR2, received);
	if (argc != 3)
		return (1);
	i = 0;
	while (i < (int)ft_strlen(argv[1]))
	{
		if (!ft_isdigit(argv[1][i]))
			return (1);
		i++;
	}
	pid_server = ft_atoi(argv[1]);
	send_pid(pid_server);
	send_message(pid_server, argv[2]);
	return (0);
}