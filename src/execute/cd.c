/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/20 20:59:51 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exe_cd(t_exe_args *exe_arg)
{
	int		res;
	char	old_pwd[2048];
	char	new_pwd[2048];

	getcwd(old_pwd, 2048);
	res = chdir(exe_arg->args[0]);
	if (res == -1)
		write_error_message("minishell: cd: ", exe_arg->args[0], ": Not a directory"); //TODO доработать ошибки
	else
	{
		getcwd(new_pwd, 2048);
		change_env_value(old_pwd, "OLDPWD", &exe_arg->env);
		change_env_value(new_pwd, "PWD", &exe_arg->env);
	}
	return (1);
}
