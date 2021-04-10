/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:24:08 by akasha            #+#    #+#             */
/*   Updated: 2021/04/10 17:59:01 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alpha_in_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exe_exit(t_exe_args *exe_args)
{
	int			len;
	t_variable	*var;

	len = get_arr_length(exe_args->args);
	if (len > 1 && check_alpha_in_string(exe_args->args[0]))
	{
		write(1, "exit\nminishell: exit: too many arguments\n", 42);
		return (1);
	}
	else if (len >= 1 && !check_alpha_in_string(exe_args->args[0]))
	{
		write_error("exit\nminishell: exit: ",
			exe_args->args[0], "numeric argument required\n");
		exit(255);
	}
	else
	{
		var = find_variable(exe_args->variables, "?");
		write(1, "exit\n", 5);
		if (exe_args->args[0])
			exit(ft_atoi(exe_args->args[0]) % 256);
		else
			exit(ft_atoi(var->value));
	}
	return (1);
}
