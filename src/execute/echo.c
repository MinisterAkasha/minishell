/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:58:44 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 21:41:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_echo(t_exe_args *exe_args)
{
	int i;
	int	flag_n;

	i = 0;
	if (exe_args->args[i] != NULL)
		flag_n = !ft_strcmp(exe_args->args[i], "-n");
	else
		flag_n = 0;
	if (flag_n)
		i = 1;
	while (exe_args->args[i] != NULL && exe_args->args[i])
	{
		ft_putstr_fd(exe_args->args[i++], 1);
		if (exe_args->args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!flag_n)
		ft_putendl_fd("", 1);
	add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	return (1);
}
