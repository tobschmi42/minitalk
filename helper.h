#ifndef HELPER_H
# define HELPER_H

# include <signal.h>
# include <stdlib.h>

typedef struct s_siginfo
{
	volatile sig_atomic_t	sig;
	volatile sig_atomic_t	new_pid;
	volatile sig_atomic_t	new_bit;
	volatile sig_atomic_t	c_pid;
} t_server;

int	safe_kill(int pid, int sig, char *err_message);

#endif