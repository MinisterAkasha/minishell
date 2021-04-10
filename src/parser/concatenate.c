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

char	*str_without_escape(char *str)
{
	char	*str_without_escape;

	str_without_escape = ft_substr(str, 1, ft_strlen(str) - 1);
	return (str_without_escape);
}

void	concat_args(t_exe_args exe_args, char **first, char *second)
{
	char		separator;
	char		*copy_first;
	char		*modified_arg;
	char		*copy_second;

	copy_second = ft_strdup(second);
	copy_first = ft_strdup(*first);
	free(*first);
	if (copy_second[0] == '\\')
		modified_arg = str_without_escape(copy_second);
	else if (copy_second[0] == '\'')
	{
		modified_arg = ft_strdup(copy_second);
		separator = get_separator(copy_second);
		cut_separator(exe_args, &modified_arg, separator);
	}
	else
	{
		separator = get_separator(copy_second);
		modified_arg = dollar_sign(copy_second, exe_args, separator);
		cut_separator(exe_args, &modified_arg, separator);
	}
	(*first) = ft_strjoin(copy_first, modified_arg);
	free(copy_second);
	free(copy_first);
	free(modified_arg);
}
