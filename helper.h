/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:45:45 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/26 21:54:41 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include <signal.h>
# include <stdlib.h>

typedef struct s_siginfo
{
	volatile sig_atomic_t	sig;
	volatile sig_atomic_t	current_pid;
	volatile sig_atomic_t	new_pid;
	volatile sig_atomic_t	new_bit;
}	t_server;

int	safe_kill(int pid, int sig, char *err_message);

#endif
