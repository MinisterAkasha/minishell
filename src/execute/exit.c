/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:24:08 by akasha            #+#    #+#             */
/*   Updated: 2021/03/21 20:26:10 by akasha           ###   ########.fr       */
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
	int len;

	len = get_arr_length(exe_args->args);
	if (len > 1 && check_alpha_in_string(exe_args->args[0]))
	{
		write(1, "exit\nminishell: exit: too many arguments\n", 42);
		return (1);
	}
	else if (len >= 1 && !check_alpha_in_string(exe_args->args[0]))
	{
		write(1, "exit\nminishell: exit: asd: numeric argument required\n", 54);
		exit(255);
	}
	else
	{
		write(1, "exit\n", 5);
		if (exe_args->args[0])
			exit(ft_atoi(exe_args->args[0]) % 256);
		else
			exit(0);
	}
	return (1);
}