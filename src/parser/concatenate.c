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

void	concat_args(t_exe_args exe_args, char **first, char *second,
				t_exe_info *exe_info)
{
	char		separator;
	char		*copy_first;
	char		*modified_arg;
	char		*copy_second;

	copy_second = ft_strdup(second);
	separator = get_separator(copy_second);
	copy_first = ft_strdup(*first);
	free(*first);
	cut_separator(exe_args, &copy_second, separator);
	modified_arg = dollar_sign(copy_second, exe_args, separator, exe_info);
	(*first) = ft_strjoin(copy_first, modified_arg);
	free(copy_second);
	free(copy_first);
	free(modified_arg);
}
