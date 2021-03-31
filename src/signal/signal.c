/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:24:49 by tilda             #+#    #+#             */
/*   Updated: 2021/03/30 15:24:51 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(int signum)
{
	ft_putendl_fd("Ctrl-D", 1);
}

void	ctrl_c(int signum)
{
	ft_putendl_fd("Ctrl-C", 1);
	add_variable_to_list(&general->variables, "?", "130", 0, 0);
	ft_putstr_fd("\n", 1);
}

void	ctrl_slash(int signum)
{
	ft_putendl_fd("Quit: 3", 1);
	add_variable_to_list(&general->variables, "?", "131", 0, 0);
}