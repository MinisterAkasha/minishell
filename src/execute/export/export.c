/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/18 14:28:57 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fill_variable_list(t_exe_args *exe_arg)
{
	char	**variable;
	int		i = 1;

	while (exe_arg->args[i])
	{
		variable = ft_split(exe_arg->args[i], '=');
		if (!ft_strchr(exe_arg->args[i], '='))
			add_variable_to_list(&exe_arg->variables, variable[0], "", 1, 0);
		else if (variable[1])
			add_variable_to_list(&exe_arg->variables, variable[0], variable[1], 1, 1);
		else
			add_variable_to_list(&exe_arg->variables, variable[0], "", 1, 1);
		free_2d_arr(variable);
		i++;
	}
}

char		**fill_arr_with_variable(char **arr, t_variable *$variable)
{
	char *variable;
	char *key_pattern;
	char **arr_copy;

	key_pattern = ft_strjoin($variable->key, "=");
	variable = ft_strjoin(key_pattern, $variable->value);
	arr_copy = add_param_to_2d_arr(arr, variable);
	free(variable);
	free(key_pattern);
	return (arr_copy);
}

static void	write_transform_arr(char **arr, t_list *var)
{
	int			i;
	char		**str;
	t_variable	*variable;

	i = 0;
	while (arr[i])
	{
		str = ft_split(arr[i], '=');
		variable = find_variable(var, str[0]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(str[0], 1);
		if (variable && variable->is_env)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
		}
		if (str[1])
			ft_putstr_fd(str[1], 1);
		if (variable && variable->is_env)
			ft_putstr_fd("\"", 1);
		ft_putendl_fd("", 1);
		free_2d_arr(str);
		i++;
	}
}

char		**fill_env_with_variables(char **env, t_list *variables)
{
	char		**new_arr;
	char		**sup_arr;
	t_list		*tmp;
	t_variable	*$variable;

	tmp = variables;
	new_arr = copy_2d_arr(env);
	while (tmp)
	{
		$variable = tmp->content;
		if ($variable->is_exported)
		{
			sup_arr = copy_2d_arr(new_arr);
			free_2d_arr(new_arr);
			new_arr = fill_arr_with_variable(sup_arr, $variable);
			free_2d_arr(sup_arr);
		}
		tmp = tmp->next;
	}
	return (new_arr);
}

int			exe_export(t_exe_args *exe_arg)
{
	char		**export;
	char		**export_copy;
	t_list		*tmp;
	t_variable	*$variable;

	fill_variable_list(exe_arg);
	export = fill_env_with_variables(exe_arg->env, exe_arg->variables);
	if (get_arr_length(exe_arg->args) == 1)
		write_transform_arr(sort_export(export, 0, get_arr_length(export) - 1), exe_arg->variables);
	free_2d_arr(export);
	return (1);
}
