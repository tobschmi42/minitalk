/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobschmi <tobschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:45:37 by tobschmi          #+#    #+#             */
/*   Updated: 2026/04/26 20:52:37 by tobschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "helper.h"

int	safe_kill(int pid, int sig, char *err_message)
{
	if (kill(pid, sig) == -1)
	{
		ft_putendl_fd(err_message, 1);
		return (1);
	}
	return (0);
}
