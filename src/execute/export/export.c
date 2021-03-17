/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 14:55:04 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_variable_list(t_exe_args *exe_arg)
{
	char **variable;
	int i = 1;
	
	while (exe_arg->args[i])
	{
		variable = ft_split(exe_arg->args[i], '=');
		if (!ft_strchr(exe_arg->args[i], '='))
			add_variable_to_list(&exe_arg->variables, variable[0], "", 1);
		else if (variable[1])
			add_variable_to_list(&exe_arg->variables, variable[0], variable[1], 1);
		else
			add_variable_to_list(&exe_arg->variables, variable[0], "\"\"", 1);
		free_2d_arr(variable);
		i++;
	}
}

int exe_export(t_exe_args *exe_arg)
{
	char **export;
	

	// export = copy_2d_arr(exe_arg->env);
	fill_variable_list(exe_arg);
	

	t_list *tmp;
	t_variable *$variable;
	tmp = exe_arg->variables;
	while (tmp)
	{
		$variable = tmp->content;
		printf("%s:%s\n", $variable->key, $variable->value);
		tmp = tmp->next;
	}

	// while ()
	// if (get_arr_length(exe_arg->args) == 1)
	// {
	// 	sort_export(export, 0, get_arr_length(export) - 1);
	// 	int i = 0;
	// 	while (export[i])
	// 	{
	// 		printf("%s\n", export[i]);
	// 		i++;
	// 	}
	// }

	return (1);
}
