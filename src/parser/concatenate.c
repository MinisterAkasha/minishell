/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:19:22 by tilda             #+#    #+#             */
/*   Updated: 2021/03/16 15:19:23 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_arg(t_exe_info **exe_info, char *arg)
{
	char		separator;
	char		*copy_exe_arg;
	t_exe_info	*tmp_lst;

	tmp_lst = *exe_info;
	separator = get_separator(arg);
	copy_exe_arg = ft_strdup(tmp_lst->arg);
	free(tmp_lst->arg);
	if (separator == 'f')
		tmp_lst->arg = ft_strjoin(copy_exe_arg, arg);
	else
	{
		cut_separator(&arg, separator);
		tmp_lst->arg = ft_strjoin(copy_exe_arg, arg);
	}
	free(arg);
	free(copy_exe_arg);
}

void	concat_exe_arg(char **first, char *second)
{
	char		separator;
	char		*copy_first;

	separator = get_separator(second);
	copy_first = ft_strdup(*first);
	free(*first);
	if (separator == 'f')
		(*first) = ft_strjoin(copy_first, second);
	else
	{
		cut_separator(&second, separator);
		(*first) = ft_strjoin(copy_first, second);
	}
	free(copy_first);
}
