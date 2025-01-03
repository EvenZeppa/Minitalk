#include "server.h"

t_message	g_message;

void	alloc_buffer(void)
{
	if (!g_message.buffer || g_message.char_i >= g_message.buffer_size - 1)
	{
		g_message.buffer_size = g_message.buffer_size + BUFFER_SIZE;
		g_message.buffer = ft_realloc(
				g_message.buffer, sizeof(char) * g_message.buffer_size);
		if (!g_message.buffer)
		{
			ft_printf("Erreur d'allocation de la memoire du buffer !\n");
			exit(1);
		}
	}
}

void	check_buffer(int pid)
{
	if (g_message.bit_i == 8 && g_message.buffer[g_message.char_i] == '\0')
	{
		ft_printf("g_message recu : %s\n", g_message.buffer);
		kill(pid, SIGUSR2);
		g_message.char_i = 0;
		g_message.bit_i = 0;
		free(g_message.buffer);
		g_message.buffer = NULL;
	}
	if (g_message.bit_i == 8)
	{
		g_message.bit_i = 0;
		g_message.char_i++;
		g_message.buffer[g_message.char_i] = '\0';
	}
}

void	s1_handler(int signal, siginfo_t *info, void *s)
{
	(void)s;
	(void)signal;
	alloc_buffer();
	g_message.buffer[g_message.char_i] <<= 1;
	g_message.bit_i++;
	check_buffer(info->si_pid);
	kill(info->si_pid, SIGUSR1);
}

void	s2_handler(int signal, siginfo_t *info, void *s)
{
	(void)s;
	(void)signal;
	alloc_buffer();
	g_message.buffer[g_message.char_i] <<= 1;
	g_message.buffer[g_message.char_i]++;
	g_message.bit_i++;
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
	g_message.buffer = NULL;
	g_message.buffer_size = BUFFER_SIZE;
	alloc_buffer();
	ft_printf("Server PID : %d\n", getpid());
	while (TRUE)
		pause();
	free(g_message.buffer);
	return (0);
}
