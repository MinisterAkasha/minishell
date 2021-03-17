/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 20:47:55 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_variable_list(t_exe_args *exe_arg)
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

char	**fill_export_with_variable(char **export, t_variable *$variable)
{
	char *variable;
	char *key_pattern;
	char **export_copy;

	key_pattern = ft_strjoin($variable->key, "=");
	variable = ft_strjoin(key_pattern, $variable->value);

	export_copy = add_param_to_2d_arr(export, variable);

	free(variable);
	free(key_pattern);

	return (export_copy);
}

void	transform_arr(char **arr, t_list *var)
{
	int			i;
	char		**str;
	char		*tmp;
	char		*support;
	t_variable	*variable;

	i = 0;
	while (arr[i])
	{
		str = ft_split(arr[i], '=');
		variable = find_variable(var, str[0]);
		tmp = ft_strjoin("declare -x ", str[0]);
		if (str[1])
		{
			support = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = ft_strjoin(support, "\"");
			free(support);
			support = ft_strjoin(tmp, str[1]);
			free(tmp);
			tmp = ft_strjoin(support, "\"");
			free(support);
		}
		else if (variable->is_env)
		{
			support = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = ft_strjoin(support, "\"");
			free(support);
			support = ft_strjoin(tmp, "\"");
			free(tmp);
			tmp = ft_strjoin(support, "");
			free(support);
		}
		ft_putendl_fd(tmp, 1);
		free(tmp);
		free_2d_arr(str);
		i++;
	}
}

int		exe_export(t_exe_args *exe_arg)
{
	char		**export;
	char		**export_copy;
	t_list		*tmp;
	t_variable	*$variable;

	export = copy_2d_arr(exe_arg->env);
	fill_variable_list(exe_arg);
	tmp = exe_arg->variables;
	while (tmp)
	{
		$variable = tmp->content;
		if ($variable->is_exported)
		{
			export_copy = copy_2d_arr(export);
			free_2d_arr(export);
			export = fill_export_with_variable(export_copy, $variable);
			free_2d_arr(export_copy);
		}
		tmp = tmp->next;
	}
	if (get_arr_length(exe_arg->args) == 1)
		transform_arr(sort_export(export, 0, get_arr_length(export) - 1), exe_arg->variables);
	free_2d_arr(export);
	return (1);
}
