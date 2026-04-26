/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:43 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/26 19:28:08 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "helper.h"
#include "libft/libft.h"

static volatile t_server	g_siginfo;

static int	message_handler(int sig)
{
	static int		progress = 0;
	static char		string[2097152];
	static size_t	str_runner = 0;

	if (sig == 0)
	{
		progress = 0;
		str_runner = 0;
	}
	else
		string[str_runner] = (string[str_runner] << 1) ^ (sig == SIGUSR1);
	++progress;
	if (progress == 8)
	{
		progress = 0;
		if (string[str_runner] != '\0')
			str_runner++;
		else
		{
			str_runner = 0;
			ft_putstr_fd(string, 1);
			return (1);
		}
	}
	return (0);
}

static int	signal_processor(const int mode, int *current_pid)
{
	g_siginfo.new_bit = 0;
	if (*current_pid == 0)
		*current_pid = g_siginfo.new_pid;
	if (*current_pid != g_siginfo.new_pid)
	{
		safe_kill(g_siginfo.new_pid, SIGUSR2, "Failed to dismiss new client.");
		return (mode);
	}
	else if (message_handler(g_siginfo.sig))
	{
		*current_pid = 0;
		ft_putstr_fd("\nSuccessfully received Message\n", 1);
		safe_kill(g_siginfo.new_pid, SIGUSR2, "Failed to close Connection.");
		return (1);
	}
	safe_kill(*current_pid, SIGUSR1, "Failed to communincate with client.");
	return (0);
}

static int	server_mode(int mode, int *wait, int *current_pid)
{
	if (mode == 1)
	{
		pause();
		mode = 0;
		*wait = 0;
	}
	if (g_siginfo.new_bit == 1)
	{
		mode = signal_processor(mode, current_pid);
		*wait = 0;
	}
	else
	{
		usleep(10);
		(*wait)++;
	}
	if (*wait >= 90000)
	{
		ft_putstr_fd("\nTimeout: Client dropped.\n", 1);
		message_handler(0);
		*current_pid = 0;
		mode = 1;
		*wait = 0;
	}
	return (mode);
}

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	g_siginfo.new_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_siginfo.sig = SIGUSR1;
	else if (sig == SIGUSR2)
		g_siginfo.sig = SIGUSR2;
	else
		g_siginfo.sig = 0;
	g_siginfo.new_bit = 1;
}

int	main(void)
{
	struct sigaction	s_act;
	int					mode;
	int					current_pid;
	int					wait;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&s_act.sa_mask);
	sigaddset(&s_act.sa_mask, SIGUSR1);
	sigaddset(&s_act.sa_mask, SIGUSR2);
	s_act.sa_flags = SA_SIGINFO;
	s_act.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	mode = 2;
	current_pid = 0;
	wait = 0;
	while (1)
		mode = server_mode(mode, &wait, &current_pid);
}
