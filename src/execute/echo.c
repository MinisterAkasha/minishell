/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:58:44 by akasha            #+#    #+#             */
/*   Updated: 2021/03/25 18:27:35 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_echo(t_exe_args *exe_args)
{
	int i;
	int	flag_n;
	
	i = 0;
	flag_n = !ft_strcmp(exe_args->args[i], "-n");
	if (flag_n)
		i = 1;
	while (exe_args->args[i])
	{
		ft_putstr_fd(exe_args->args[i++], 1);
		if (exe_args->args[i + 1])
			ft_putstr_fd(" ", 1); 
	}
	if (!flag_n)
		ft_putendl_fd("", 1);
	else
		ft_putendl_fd("%", 1);
	add_variable_to_list(&exe_args->variables, "?", "0", 0, 0);
	return (1);
}