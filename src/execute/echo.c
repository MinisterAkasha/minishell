/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:58:44 by akasha            #+#    #+#             */
/*   Updated: 2021/04/12 12:37:39 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_new_arg_without_n(char *str)
{
	char	*new_arg;

	new_arg = ft_strdup(str + 3);
	return (new_arg);
}

int		exe_echo(t_exe_args *exe_args)
{
	char *str;

	if (exe_args->is_flag_n)
	{
		str = ft_strchr(exe_args->args[0], '-') + 1;
		while (*str == 'n')
			str++;
		str++;
		ft_putstr_fd(str, 1);
	}
	else
		ft_putstr_fd(exe_args->args[0], 1);
	if (!exe_args->is_flag_n)
		write(1, "\n", 1);
	add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	return (1);
}
