/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 19:27:01 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**splite_var_name(char *str)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		ft_error_malloc();
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	arr[0] = ft_substr(str, 0, i);
	arr[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	arr[2] = NULL;
	return (arr);
}

void	write_transform_arr(char **arr, t_list *var)
{
	int			i;
	char		**str;
	t_variable	*variable;

	i = 0;
	while (arr[i])
	{
		str = splite_var_name(arr[i]);
		variable = find_variable(var, str[0]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(str[0], 1);
		if (!variable || (variable && variable->is_env))
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
		}
		if (str[1])
			ft_putstr_fd(str[1], 1);
		if (!variable || (variable && variable->is_env))
			ft_putstr_fd("\"", 1);
		ft_putendl_fd("", 1);
		free_2d_arr(str);
		i++;
	}
}

void	set_export_status_var(t_exe_args *exe_arg)
{
	char	**variable;
	int		i;

	i = 0;
	while (exe_arg->args[i])
	{
		variable = splite_var_name(exe_arg->args[i]);
		if (!validate_var_name(variable[0]))
		{
			add_variable(&exe_arg->variables, create_var("?", "1", 0, 0));
			free_2d_arr(variable);
			return ;
		}
		free_2d_arr(variable);
		i++;
	}
	add_variable(&exe_arg->variables, create_var("?", "0", 0, 0));
}

int		exe_export(t_exe_args *exe_arg)
{
	char		**export;
	char		**env_copy;

	fill_variable_list(exe_arg);
	set_export_status_var(exe_arg);
	env_copy = copy_2d_arr(exe_arg->env_init);
	export = fill_export_with_variables(env_copy, exe_arg->variables);
	free_2d_arr(exe_arg->env);
	exe_arg->env = fill_env_with_variables(env_copy, exe_arg->variables);
	free_2d_arr(env_copy);
	if (get_arr_length(exe_arg->args) == 0)
	{
		add_variable(&exe_arg->variables, create_var("?", "0", 0, 0));
		write_transform_arr(sort_export(export, 0, get_arr_length(export) - 1),
			exe_arg->variables);
	}
	free_2d_arr(export);
	return (1);
}
