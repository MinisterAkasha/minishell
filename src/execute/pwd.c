/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:55:49 by akasha            #+#    #+#             */
/*   Updated: 2021/04/09 15:00:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_pwd(t_exe_args *exe_args)
{
	char	path[2048];
	char	**pwd;

	if (!getcwd(path, 2048))
	{
		pwd = ft_split(get_env_param("PWD", exe_args->env), '=');
		printf("%s\n", pwd[1]);
		free_2d_arr(pwd);
	}
	else
	{
		ft_putendl_fd(getcwd(path, 2048), 1);
		add_variable(&exe_args->variables,
			create_var("?", "0", 0, 0));
	}
	return (1);
}
