/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:35 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/22 22:42:51 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"

static volatile sig_atomic_t	g_pause;

static void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_pause = 1;
	else
		exit(0);
}

static void	send_bit(char character, size_t position, int pid)
{
	if ((character >> position) & 1)
		kill(pid, SIGUSR1);
	else
		kill (pid, SIGUSR2);
}

static void	communication_handler( char *string, int pid)
{
	size_t	str_runner;
	size_t	bit_runner;
	int		wait;

	str_runner = 0;
	bit_runner = 0;
	while (str_runner <= ft_strlen(string))
	{
		bit_runner = 8;
		while (bit_runner != 0)
		{
			g_pause = 0;
			send_bit(string[str_runner], bit_runner - 1, pid);
			wait = 0;
			while (g_pause == 0)
			{
				usleep(10);
				++wait;
				if (wait >= 90)
					exit(1);
			}
			--bit_runner;
		}
		++str_runner;
	}
}

int	main(int num, char **args)
{
	struct sigaction	s_act;

	if (num != 3)
		return (0);
	s_act.sa_handler = signal_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = 0;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	communication_handler(args[2], ft_atoi(args[1]));
}
