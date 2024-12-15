#include <signal.h>
#include "libft.h"

#define BUFFER_SIZE 64

char	*buffer;

void	add_bit_buffer(char bit)
{
	static int	char_i = 0;
	static int	bit_i = 0;

	if (bit_i == 8)
	{
		if (buffer[char_i] == '\0')
			char_i = 0;
		else
			char_i++;
		bit_i = 0;
	}
	buffer[char_i] <<= 1;
	if (bit)
		buffer[char_i]++;
	bit_i++;
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
	while (TRUE)
	{
		signal(SIGUSR1, bit_0);
		signal(SIGUSR2, bit_1);
		pause();
		if (ft_strnchr(buffer, '\0', BUFFER_SIZE))
		{
			ft_printf("Message recu : %s\n", buffer);
			ft_memset((void *)&buffer[0], '\0', BUFFER_SIZE);
		}
	}
}

int	main(int argc, char *argv[])
{
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	ft_printf("Server PID : %d\n", getpid());
	


	char	*str = "test";
	while (*str)
	{
		char	byte = *str;
		char	bit = 0;
		while (bit < 8)
		{
			add_bit_buffer((byte & 0b10000000) == 0b10000000 ? (char)0b00000001 : 0);
			byte <<= 1;
			bit++;
		}
		str++;
	}


	return (0);
}