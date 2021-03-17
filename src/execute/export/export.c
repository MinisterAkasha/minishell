/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 12:39:44 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exe_export(t_exe_args *exe_arg)
{
	char	**export;

	export = create_env(exe_arg->env);
	//t_variable *variable; // = find_variable(variables, "name");
	// printf("%s: %s\n", variable->key, variable->value);
	//TODO цикл по agrs и создать переменные
	if (get_arr_length(exe_arg->args) == 1)
	{
		sort_export(export, 0, get_arr_length(export) - 1);
		int i = 0;
		while (export[i])
		{
			printf("%s\n", export[i]);
			i++;
		}
	}

	return (1);
}