#include "libft/libft.h"
#include <signal.h>
#include <stdint.h>
#include <unistd.h>

static void    signal_handler (int sig, siginfo_t *info, void *ucontext)
{
    static int      progress = 0;
    static char g_character;

    (void) ucontext;
    if (sig == SIGUSR2)
        g_character = (g_character << 1);
    else
        g_character = (g_character << 1) ^ 1;
    ++progress;
    if (progress == 8)
    {
        write(1, &g_character, 1);
        progress = 0;
    }
    kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction    s_act;

    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    sigemptyset(&s_act.sa_mask);
    s_act.sa_flags = SA_SIGINFO;
    s_act.sa_sigaction = signal_handler;
    sigaction(SIGUSR1, &s_act, NULL);
    sigaction(SIGUSR2, &s_act, NULL);
    while(1)
        ;
}