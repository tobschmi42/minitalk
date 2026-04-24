#include "libft/libft.h"

static void	safe_kill(int pid, int sig, char *err_message)
{
	if (kill(pid, sig) == -1)
	{
		ft_putendl_fd(err_message, 1);
		exit(-1);
	}
}