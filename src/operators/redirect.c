/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/03/23 19:03:59 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exe_oper_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args)
{
	int		oldstdout;
	int		file;
	char	*bin_exe_path;

	file = open(next_arg, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);//TODO обработать ошибку
	if (file)
	{
		oldstdout = dup(1);
		dup2(file, 1);
		close(file);
		if (exe_function)
			exe_function(&fun_args);
		else
		{
			bin_exe_path = search(fun_args.args[0], get_env_param("PATH", fun_args.env));
			launch_shell(fun_args, bin_exe_path);
			free(bin_exe_path);
		}
		dup2(oldstdout, 1);
	}
	return (1);
}