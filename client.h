#ifndef CLIENT_H
# define CLIENT_H

#include "libft.h"
#include <signal.h>
#include <fcntl.h>

typedef struct s_client
{
	int		pid_server;
	char	*msg;
	int		bit;
}	t_client;

#endif