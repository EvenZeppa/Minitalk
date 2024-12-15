#include <signal.h>
#include "libft.h"

#define BUFFER_SIZE 128

typedef struct s_message
{
	char	*buffer;
	int		char_i;
	int		bit_i;
}	t_message;

t_message	message;

void	add_bit_buffer(char bit)
{
	message.buffer[message.char_i] <<= 1;
	if (bit)
		message.buffer[message.char_i]++;
	message.bit_i++;
}

void	bit_0()
{
	add_bit_buffer(0);
}

void	bit_1()
{
	add_bit_buffer(1);
}

void	wait_signal()
{
	signal(SIGUSR1, bit_0);
	signal(SIGUSR2, bit_1);
	while (TRUE)
	{
		pause();
		if (message.char_i > BUFFER_SIZE)
		{
			ft_printf("Message corrompu !\n");
			message.char_i = 0;
			message.bit_i = 0;
		}
		if (message.bit_i == 8 && message.buffer[message.char_i] == '\0')
		{
			ft_printf("Message recu : %s\n", message.buffer);
			// free(message.buffer);
			// message.buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
			message.char_i = 0;
			message.bit_i = 0;
		}
		if (message.bit_i == 8)
		{
			message.bit_i = 0;
			message.char_i++;
			message.buffer[message.char_i] = '\0';
		}
	}
}

int	main(int argc, char *argv[])
{
	message.buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	message.char_i = 0;
	message.bit_i = 0;
	ft_printf("Server PID : %d\n", getpid());
	wait_signal();
	free(message.buffer);
	return (0);
}