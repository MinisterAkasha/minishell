/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:14:07 by tilda             #+#    #+#             */
/*   Updated: 2021/04/04 21:41:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char **buff, char **str_stat)
{
	if (!ft_strcmp(*str_stat, ""))
	{
		free(*str_stat);
		*str_stat = ft_strdup("exit\n");
		free((*buff));
		(*buff) = ft_strdup("");
	}
	else
	{
		free((*buff));
		(*buff) = ft_strdup("");
	}
}

void	ctrl_c(char **buff, char **str_stat)
{
	free(*str_stat);
	*str_stat = ft_strdup("");
	free((*buff));
	(*buff) = ft_strdup("\n");
	add_variable(&general->variables, create_var("?", "1", 0, 0));
}

void	ctrl_slash(char **buff)
{
	free((*buff));
	(*buff) = ft_strdup("");
}
