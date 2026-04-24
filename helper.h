#ifndef HELPER_H
# define HELPER_H

# include <signal.h>


typedef struct s_siginfo
{
	volatile sig_atomic_t	sig;
	volatile sig_atomic_t	pid;
} t_server;

static void	safe_kill(int pid, int sig, char *err_message);

#endif