/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:58:44 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 21:58:16 by akasha           ###   ########.fr       */
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
	int i;
	char	**args;
	int	flag_n;

	i = 0;
	args = ft_split(exe_args->args[0], ' ');
	if (args[0] != NULL && !ft_strcmp(args[0], "-n"))
	{
		flag_n = 1;
		free(exe_args->args[0]);
		exe_args->args[0] = make_new_arg_without_n(exe_args->args[0]);
	}
	else
		flag_n = 0;
	free_2d_arr(args);
	ft_putstr_fd(exe_args->args[0], 1);
	if (!flag_n)
		ft_putendl_fd("", 1);
	add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	return (1);
}
