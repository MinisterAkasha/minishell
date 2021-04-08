/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:24:49 by tilda             #+#    #+#             */
/*   Updated: 2021/04/08 19:55:29 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(int signum)
{
	add_variable(&g_general->variables, create_var("?", "130", 0, 0));
	ft_putstr_fd("\n", 1);
}

void	signal_ctrl_slash(int signum)
{
	add_variable(&g_general->variables, create_var("?", "131", 0, 0));
	ft_putendl_fd("Quit: 3", 1);
}
