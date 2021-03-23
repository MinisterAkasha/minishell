/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:19:22 by tilda             #+#    #+#             */
/*   Updated: 2021/03/18 15:55:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_arg(t_exe_info **exe_info, t_support_parsing_data support, char *arg)
{
	char		separator;
	char		*copy_exe_arg;
	t_exe_info	*tmp_lst;

	tmp_lst = *exe_info;
	separator = get_separator(arg);
	copy_exe_arg = protect_malloc(ft_strdup(tmp_lst->args));
	free(tmp_lst->args);
	if (separator == 'f')
		tmp_lst->args = protect_malloc(ft_strjoin(copy_exe_arg, arg));
	else
	{
		cut_separator(&arg, separator);
		tmp_lst->args = protect_malloc(ft_strjoin(copy_exe_arg, arg));
	}
	free(copy_exe_arg);
}

void	concat_exe_arg(char **first, char *second)
{
	char		separator;
	char		*copy_first;

	separator = get_separator(second);
	copy_first = protect_malloc(ft_strdup(*first));
	free(*first);
	if (separator == 'f')
		(*first) = protect_malloc(ft_strjoin(copy_first, second));
	else
	{
		cut_separator(&second, separator);
		(*first) = protect_malloc(ft_strjoin(copy_first, second));
	}
	free(copy_first);
}
