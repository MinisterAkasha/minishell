/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:24:49 by tilda             #+#    #+#             */
/*   Updated: 2021/04/04 21:13:09 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(int signum)
{
	add_variable_to_list(&general->variables, create_variable("?", "130", 0, 0));
	ft_putstr_fd("\n", 1);
}

void	signal_ctrl_slash(int signum)
{
	add_variable_to_list(&general->variables, create_variable("?", "131", 0, 0));
	ft_putendl_fd("Quit: 3", 1);
}
