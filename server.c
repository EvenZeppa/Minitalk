#include <signal.h>
#include <stdio.h>
#include "libft.h"

#define BUFFER_SIZE 4096

typedef struct s_message
{
	char	*buffer;
	int		buffer_size;
	int		char_i;
	int		bit_i;
	int		pid_client;
	int		is_pending_pid_c;
}	t_message;

t_message	message;

void	add_bit_pid_client(char bit)
{
	message.pid_client <<= 1;
	if (bit)
		message.pid_client++;
}

void	add_bit_buffer(char bit)
{
	message.buffer[message.char_i] <<= 1;
	if (bit)
		message.buffer[message.char_i]++;
	message.bit_i++;
}

void	bit_0()
{
	if (message.is_pending_pid_c)
		add_bit_pid_client(0);
	else
		add_bit_buffer(0);
}

void	bit_1()
{
	if (message.is_pending_pid_c)
		add_bit_pid_client(1);
	else
		add_bit_buffer(1);
}

void	wait_pid_client()
{
	int	int_size;

	int_size = sizeof(int) * 8;
	while (int_size)
	{
		pause();
		int_size--;
	}
	message.is_pending_pid_c = 0;
}

void	wait_signal()
{
	while (TRUE)
	{
		if (!message.buffer || message.char_i >= message.buffer_size - 1)
		{
			message.buffer_size = message.buffer_size + BUFFER_SIZE;
			message.buffer = ft_realloc(message.buffer, sizeof(char) * message.buffer_size);
			if (!message.buffer)
			{
				ft_printf("Erreur d'allocation de la memoire du buffer !\n");
				exit(1);
			}
		}
		pause();
		if (message.bit_i == 8 && message.buffer[message.char_i] == '\0')
		{
			ft_printf("Message recu : %s\n", message.buffer);
			kill(message.pid_client, SIGUSR2);
			break;
		}
		if (message.bit_i == 8)
		{
			message.bit_i = 0;
			message.char_i++;
			message.buffer[message.char_i] = '\0';
		}
		kill(message.pid_client, SIGUSR1);
	}
}

int	main(void)
{
	signal(SIGUSR1, bit_0);
	signal(SIGUSR2, bit_1);
	message.buffer = NULL;
	message.buffer_size = BUFFER_SIZE;
	ft_printf("Server PID : %d\n", getpid());
	while (TRUE)
	{
		message.char_i = 0;
		message.bit_i = 0;
		message.pid_client = 0;
		message.is_pending_pid_c = 1;
		wait_pid_client();
		wait_signal();
	}
	free(message.buffer);
	return (0);
}