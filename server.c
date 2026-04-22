/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:43 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/21 23:40:50 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdint.h>
#include <unistd.h>

static int	message_handler(int sig)
{
	static int		progress = 0;
	static char		character = 0;
	static char		string[2097152];
	static size_t	str_runner = 0;

	if (sig == SIGUSR2)
		character = (character << 1);
	else
		character = (character << 1) ^ 1;
	++progress;
	if (progress == 8)
	{
		progress = 0;
		string[str_runner] = character;
		str_runner++;
		if (character == '\0')
		{
			str_runner = 0;
			ft_putstr_fd(string, 1);
			return (1);
		}
	}
	return (0);
}

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	pid = 0;
	
	(void) ucontext;
	if (!pid)
		pid = info->si_pid;
	if (pid != info->si_pid)
		kill(info->si_pid, SIGUSR2);
	else
	{
		if (message_handler(sig))
		{
			pid = 0;
			kill(info->si_pid, SIGUSR2);
		}
		else
			kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	s_act;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_SIGINFO;
	s_act.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	while (1)
		;
}
