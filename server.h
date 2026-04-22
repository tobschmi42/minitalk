

#include <signal.h>


typedef struct s_siginfo
{
	volatile sig_atomic_t	sig;
	volatile sig_atomic_t	pid;
} t_server;