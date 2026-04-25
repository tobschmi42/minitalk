/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:09:35 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/26 00:15:51 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "helper.h"
#include "libft/libft.h"

static volatile sig_atomic_t	g_pause;

static void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_pause = 1;
	else if (signal == SIGUSR2)
		g_pause = 2;
}

static void	send_bit(char character, size_t position, int pid)
{
	int error;

	if ((character >> position) & 1)
		error = safe_kill(pid, SIGUSR1, "Error when commincating with server\n");
	else
		error = safe_kill(pid, SIGUSR2, "Error when commincating with server\n");
	if (error)
		exit (1);
}

static int	communication_handler(char *string, int pid)
{
	size_t	str_runner;
	size_t	bit_runner;
	int		wait;

	str_runner = 0;
	while (str_runner <= ft_strlen(string))
	{
		bit_runner = 8;
		while (bit_runner != 0)
		{
			g_pause = 0;
			send_bit(string[str_runner], bit_runner - 1, pid);
			wait = 0;
			while (g_pause == 0 && wait <= 9000)
			{
				usleep(100);
				++wait;
			}
			if (wait >= 9000 || g_pause == 2)
				return (1);
			--bit_runner;
		}
		++str_runner;
	}
	return (0);
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
	 if (communication_handler(args[2], ft_atoi(args[1])))
	 {
		if (g_pause == 2)
			ft_putendl_fd("Server closed Connection.", 1);
		else
		{
			ft_putendl_fd("Error when attempting to communicate with Server", 1);
			return (1);
		}
	 }
	 //ft_putendl_fd("Message sent successfully", 1);
	 return (0);
}
