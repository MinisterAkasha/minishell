/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 15:36:41 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_home(char *home)
{
	int		res;
	char	**home_arr;

	home_arr = ft_split(home, '=');
	res = chdir(home_arr[1]);
	free_2d_arr(home_arr);
	return (res);
}

int		exe_cd(t_exe_args *exe_args)
{
	int		res;
	char	old_pwd[2048];
	char	new_pwd[2048];
	char	*error;

	getcwd(old_pwd, 2048);
	if (!exe_args->args[0])
		res = cd_home(get_env_param("HOME", exe_args->env));
	else
		res = chdir(exe_args->args[0]);
	if (res == -1)
	{
		add_variable_to_list(&exe_args->variables, "?", "1", 0, 0);
		write_error_message("minishell: cd: ", exe_args->args[0], strerror(errno)); //TODO доработать ошибки
	}
	else
	{
		getcwd(new_pwd, 2048);
		change_env_value(old_pwd, "OLDPWD", &exe_args->env);
		change_env_value(new_pwd, "PWD", &exe_args->env);
		add_variable_to_list(&exe_args->variables, "?", "0", 0, 0);
	}
	return (1);
}
