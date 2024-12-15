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
		char_i++;
		bit_i = 0;
	}
	buffer[char_i] <<= 1;
	if (bit)
		buffer[char_i]++;
	bit_i++;
}

void	handle()
{
	ft_printf("RECU\n");
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
	ft_printf("Result : %s\n", buffer);
	

	// signal(SIGUSR1, handle);
	// pause();
	return (0);
}