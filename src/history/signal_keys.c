/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:14:07 by tilda             #+#    #+#             */
/*   Updated: 2021/03/31 13:14:09 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char **buff, char **str_stat)
{
	if (!ft_strcmp(*str_stat, ""))
	{
		free(*str_stat);
		*str_stat = protect_malloc(ft_strdup("exit\n"));//TODO сделать чтобы не было с новой строки
		free((*buff));
		(*buff) = protect_malloc(ft_strdup(""));
	}
	else
	{
		free((*buff));
		(*buff) = protect_malloc(ft_strdup(""));
	}
}

void	ctrl_c(char **buff, char **str_stat)
{
	free(*str_stat);
	*str_stat = protect_malloc(ft_strdup(""));
	free((*buff));
	(*buff) = protect_malloc(ft_strdup("\n"));
	add_variable_to_list(&general->variables, "?", "1", 0, 0);
}

void	ctrl_slash(char **buff)
{
	free((*buff));
	(*buff) = protect_malloc(ft_strdup(""));
}
