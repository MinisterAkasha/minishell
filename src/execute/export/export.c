/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/20 19:46:37 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_var_name_chars(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int			validate_var_name(char *name, char *var)
{
	printf("%s\n", name);
	if (ft_isdigit(name[0]) || ft_strchr(name, '.') || !check_var_name_chars(name))
	{
		write(1, "minishell: export: '", 20);
		write(1, var, ft_strlen(var));
		write(1, "': not a valid identifier\n", 27);
		return (0);
	}
	return (1);
}

char	**splite_var_name(char *str)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * 3);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	arr[0] = ft_substr(str, 0, i);
	arr[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	arr[2] = NULL;
	return (arr);
}

void		fill_variable_list(t_exe_args *exe_arg)
{
	char	**variable;
	int		i;

	i = 0;
	while (exe_arg->args[i])
	{
		variable = splite_var_name(exe_arg->args[i]);
		if (validate_var_name(variable[0], exe_arg->args[i]))
		{
			if (!get_env_param(variable[0], exe_arg->env_init))
			{
				if (!ft_strchr(exe_arg->args[i], '='))
					add_variable_to_list(&exe_arg->variables, variable[0], "", 1, 0);
				else if (variable[1])
					add_variable_to_list(&exe_arg->variables, variable[0], variable[1], 1, 1);
				else
					add_variable_to_list(&exe_arg->variables, variable[0], "", 1, 1);
			}
			else
			{
				if (ft_strchr(exe_arg->args[i], '='))
					change_env_value(variable[1], variable[0], &exe_arg->env_init);
			}
		}
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

char		**fill_export_with_variables(char **env, t_list *variables)
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
		if ($variable->is_env)
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
	char		**env_copy;

	fill_variable_list(exe_arg);
	env_copy = copy_2d_arr(exe_arg->env_init);
	export = fill_export_with_variables(env_copy, exe_arg->variables);
	free_2d_arr(exe_arg->env);
	exe_arg->env = fill_env_with_variables(env_copy, exe_arg->variables);
	free_2d_arr(env_copy);
	if (get_arr_length(exe_arg->args) == 0)
		write_transform_arr(sort_export(export, 0, get_arr_length(export) - 1), exe_arg->variables);
	free_2d_arr(export);
	return (1);
}
