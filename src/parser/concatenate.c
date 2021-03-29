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

void	concat_args(t_exe_args exe_args, char **first, char *second)
{
	char		separator;
	char		*copy_first;
	char		*modified_arg;

	separator = get_separator(second);
	copy_first = protect_malloc(ft_strdup(*first));
	free(*first);
	cut_separator(exe_args, &second, separator);
	modified_arg = dollar_sign(second, exe_args, separator);
	(*first) = protect_malloc(ft_strjoin(copy_first, modified_arg));
	free(copy_first);
	free(modified_arg);
}


