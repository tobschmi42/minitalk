/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:35 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/21 23:38:21 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"

volatile int	g_pause;

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

int	main(int num, char **args)
{
	size_t				str_runner;
	size_t				bit_runner;
	struct sigaction	s_act;

	if (num != 3)
		return (0);
	str_runner = 0;
	s_act.sa_handler = signal_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = 0;
	sigaction(SIGUSR1, &s_act, NULL);
	while (str_runner < ft_strlen(args[2]))
	{
		bit_runner = 8;
		while (bit_runner != 0)
		{
			g_pause = 0;
			send_bit(args[2][str_runner], bit_runner - 1, ft_atoi(args[1]));
			while (g_pause == 0)
				pause();
			--bit_runner;
		}
		++str_runner;
	}
}
