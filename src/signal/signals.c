/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:24:49 by tilda             #+#    #+#             */
/*   Updated: 2021/04/12 14:07:54 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		signal_ctrl_c(void)
{
	add_variable(&g_general->variables, create_var("?", "130", 0, 0));
	ft_putstr_fd("\n", 1);
}

static void		signal_ctrl_slash(void)
{
	add_variable(&g_general->variables, create_var("?", "131", 0, 0));
	ft_putendl_fd("Quit: 3", 1);
}

void			signal_listener(int signum)
{
	int		chaild_status;

	wait(&chaild_status);
	if (chaild_status == 2 || chaild_status == 3)
	{
		if (signum == 2)
			signal_ctrl_c();
		else if (signum == 3)
			signal_ctrl_slash();
	}
}
