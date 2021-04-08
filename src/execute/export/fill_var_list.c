/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:02:34 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 19:19:42 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_valid_var(char **variable, t_exe_args *exe_arg, int i)
{
	if (!get_env_param(variable[0], exe_arg->env_init))
	{
		if (!ft_strchr(exe_arg->args[i], '='))
			add_variable(&exe_arg->variables,
				create_var(variable[0], "", 1, 0));
		else if (variable[1])
			add_variable(&exe_arg->variables,
				create_var(variable[0], variable[1], 1, 1));
		else
			add_variable(&exe_arg->variables,
				create_var(variable[0], "", 1, 1));
	}
	else
	{
		if (ft_strchr(exe_arg->args[i], '='))
			change_env_value(variable[1], variable[0], &exe_arg->env_init);
	}
}

void	fill_variable_list(t_exe_args *exe_arg)
{
	char	**variable;
	int		i;

	i = 0;
	while (exe_arg->args[i])
	{
		variable = splite_var_name(exe_arg->args[i]);
		if (validate_var_name(variable[0]) && ft_strcmp(exe_arg->args[i], "="))
			fill_valid_var(variable, exe_arg, i);
		else
			write_error("minishell: export: '", exe_arg->args[i],
				"': not a valid identifier");
		free_2d_arr(variable);
		i++;
	}
}
