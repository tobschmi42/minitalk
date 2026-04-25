/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:43 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/26 00:30:21 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "helper.h"
#include "libft/libft.h"

static volatile  t_server	siginfo;

static int	message_handler(int sig)
{
	static int		progress = 0;
	static char		string[2097152];
	static size_t	str_runner = 0;

	if (sig == SIGUSR2)
		string[str_runner] = (string[str_runner] << 1);
	else if (sig == 0)
	{
		
		progress = 0;
		str_runner = 0;
	}
	else
		string[str_runner] = (string[str_runner] << 1) ^ 1;
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

static int	signal_processor(const int mode)
{
	siginfo.new_bit = 0;
	if (!siginfo.c_pid)
		siginfo.c_pid = siginfo.new_pid;
	if (siginfo.c_pid != siginfo.new_pid)
	{
		safe_kill(siginfo.c_pid, SIGUSR2, "Failed to dismiss new client.");
		return (mode);
	}
	else if (message_handler(siginfo.sig))
	{
		siginfo.c_pid = 0;
		ft_putstr_fd("\nSuccessfully received Message\n", 1);
		safe_kill(siginfo.new_pid, SIGUSR2, "Failed to close Connection.");
		return (2);
	}
	safe_kill(siginfo.c_pid, SIGUSR1, "Failed to communincate with client.");
	return (1);
}

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	siginfo.new_pid = info->si_pid;
	if (sig == SIGUSR1)
		siginfo.sig = SIGUSR1;
	else if (sig == SIGUSR2)
		siginfo.sig = SIGUSR2;
	else
		siginfo.sig = 0;
	siginfo.new_bit = 1;
}

int	main(void)
{
	struct sigaction	s_act;
	size_t				wait;
	int					mode;

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
	while (1)
	{
		
		if (mode == 2)
		{
			pause();
			mode = 0;
			wait = 0;
		}
		else if (mode == 1)
		{
			wait = 0;
			if (wait >= 9000)
			{
				safe_kill(siginfo.c_pid, SIGUSR2, "Failed to shutdown client after Timeout");
				message_handler(0);
				siginfo.c_pid = 0;
				mode = 2;
			}
			if (siginfo.new_bit == 1)
			{
				mode = signal_processor(mode);
			}
			++wait;
			usleep(100);
		}
		else
		{
			wait = 0;
			mode = signal_processor(mode);
		}
	}
}
