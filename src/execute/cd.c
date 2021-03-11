/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/11 18:21:10 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exe_cd(char **args, char **env)
{
	int		res;
	char	old_pwd[2048]; //TODO
	char	new_pwd[2048];

	getcwd(old_pwd, 2048);
	res = chdir(args[1]);
	if (res == -1)
		write_error_message("minishell: cd: ", args[1], ": Not a directory");
	else
	{
		getcwd(new_pwd, 2048);
		change_env(old_pwd, "OLDPWD", &env);
		change_env(new_pwd, "PWD", &env);
	}
	return (res);
}
