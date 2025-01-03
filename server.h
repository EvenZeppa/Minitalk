#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <stdio.h>
# include "libft.h"

# define BUFFER_SIZE 4096

typedef struct s_message
{
	char	*buffer;
	int		buffer_size;
	int		char_i;
	int		bit_i;
}	t_message;

#endif