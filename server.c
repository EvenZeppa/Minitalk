#include <signal.h>
#include "libft.h"

#define BUFFER_SIZE 64

char	*buffer;

void	add_bit_buffer(char bit)
{
	static int	char_i = 0;
	static int	bit_i = 0;

	if (bit_i == 7)
	{
		char_i++;
		bit_i = 0;
	}
	buffer[char_i] <<= 1;
	if (bit)
		buffer[char_i]++;
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
		char	bit = *str;
		str++;
	}
	

	// signal(SIGUSR1, handle);
	// pause();
	return (0);
}