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
}	t_message;

t_message	message;

void	add_bit_buffer(char bit)
{
	message.buffer[message.char_i] <<= 1;
	if (bit)
		message.buffer[message.char_i]++;
	message.bit_i++;
}

void	alloc_buffer()
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
}

void	check_buffer(int pid)
{
	if (message.bit_i == 8 && message.buffer[message.char_i] == '\0')
	{
		ft_printf("Message recu : %s\n", message.buffer);
		kill(pid, SIGUSR2);
		message.char_i = 0;
		message.bit_i = 0;
		free(message.buffer);
		message.buffer = NULL;
	}
	if (message.bit_i == 8)
	{
		message.bit_i = 0;
		message.char_i++;
		message.buffer[message.char_i] = '\0';
	}
}

void	s1_handler(int signal, siginfo_t *info, void *s)
{
	(void)s;
	(void)signal;

	alloc_buffer();
	add_bit_buffer(0);
	check_buffer(info->si_pid);
	kill(info->si_pid, SIGUSR1);
}

void	s2_handler(int signal, siginfo_t *info, void *s)
{
	(void)s;
	(void)signal;

	alloc_buffer();
	add_bit_buffer(1);
	check_buffer(info->si_pid);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_1;
	struct sigaction	s_2;
	
	s_1.sa_sigaction = s1_handler;
	s_2.sa_sigaction = s2_handler;
	sigemptyset(&s_1.sa_mask);
	sigemptyset(&s_2.sa_mask);
	s_1.sa_flags = SA_SIGINFO;
	s_2.sa_flags = SA_SIGINFO;
	if ((sigaction(SIGUSR1, &s_1, NULL) == -1)
		|| (sigaction(SIGUSR2, &s_2, NULL) == -1))
		exit(EXIT_FAILURE);

	message.buffer = NULL;
	message.buffer_size = BUFFER_SIZE;
	alloc_buffer();
	ft_printf("Server PID : %d\n", getpid());

	while (TRUE)
		pause();

	free(message.buffer);
	return (0);
}