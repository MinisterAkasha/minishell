/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:19:22 by tilda             #+#    #+#             */
/*   Updated: 2021/03/28 21:04:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_arg(t_list **tmp_lst, t_exe_args exe_args, char *arg)
{
	char		separator;
	char		*copy_exe_arg;
	char		*modified_arg;
	t_exe_info	*exe_info;

	exe_info = (*tmp_lst)->content;
	separator = get_separator(arg);
	copy_exe_arg = protect_malloc(ft_strdup(exe_info->args));
	free(exe_info->args);
	cut_separator(exe_args, &arg, separator);
	modified_arg = dollar_sign(arg, exe_args, separator);
	exe_info->args = protect_malloc(ft_strjoin(copy_exe_arg, modified_arg));
	free(modified_arg);
	free(copy_exe_arg);
}

void	concat_exe_arg(t_exe_args exe_args, char **first, char *second)
{
	char		separator;
	char		*copy_first;
	char		*modified_arg;

	separator = get_separator(second);
	copy_first = protect_malloc(ft_strdup(*first));
	free(*first);
	cut_separator(exe_args, &second, separator);
	modified_arg = dollar_sign(second, exe_args, separator);
	(*first) = protect_malloc(ft_strjoin(copy_first, second));//TODO where i should put modified_arg
	free(copy_first);
	free(modified_arg);
}


