/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/04/07 20:56:24 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(char *home)
{
	int		res;
	char	**home_arr;

	if (!home)
	{
		write_error("minishell: ", "cd", "HOME not set");
		res = -2;
	}
	else
	{
		home_arr = ft_split(home, '=');
		res = chdir(home_arr[1]);
		free_2d_arr(home_arr);
	}
	return (res);
}

int	cd_oldpwd(t_exe_args *exe_args)
{
	int			res;
	char		**oldpwd;
	t_variable	*var;

	var = find_variable(exe_args->variables, "OLDPWD");
	oldpwd = ft_split(get_env_param("OLDPWD", exe_args->env), '=');
	res = -1;
	if (!var->value || !get_env_param("OLDPWD", exe_args->env))
	{
		write_error("minishell: ", "cd", "OLDPWD not set");
		res = -2;
	}
	else
	{
		if (var->value)
			res = chdir(var->value);
		else
			res = chdir(oldpwd[1]);
		free_2d_arr(oldpwd);
	}
	return (res);
}

int	exe_cd(t_exe_args *exe_args)
{
	int		res;
	char	old_pwd[2048];
	char	new_pwd[2048];
	char	**env_copy;

	getcwd(old_pwd, 2048);
	if (!exe_args->args[0])
		res = cd_home(get_env_param("HOME", exe_args->env));
	else if (!ft_strcmp(exe_args->args[0], "-"))
		res = cd_oldpwd(exe_args);
	else
		res = chdir(exe_args->args[0]);
	if (res == -1)
	{
		add_variable(&exe_args->variables,
			create_var("?", "1", 0, 0));
		write_error("minishell: cd: ", exe_args->args[0], strerror(errno));
	}
	else if (!res)
	{
		getcwd(new_pwd, 2048);
		change_env_value(new_pwd, "PWD", &exe_args->env);
		change_env_value(new_pwd, "PWD", &exe_args->env_init);
		add_variable(&exe_args->variables, create_var("OLDPWD", old_pwd, 1, 1));
		env_copy = copy_2d_arr(exe_args->env);
		free_2d_arr(exe_args->env);
		exe_args->env = fill_env_with_variables(env_copy, exe_args->variables);
		free_2d_arr(env_copy);
		add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	}
	else if (res < -1)
		add_variable(&exe_args->variables, create_var("?", "1", 0, 0));
	return (1);
}
