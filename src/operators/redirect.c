/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/03/24 14:39:07 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exe_oper_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args, int operators_flag)
{
	int		oldstdout;
	int		file;
	char	*bin_exe_path;
	char	**next_arg_arr;

	// printf("%s\n", next_arg);
	next_arg_arr = ft_split(next_arg, ' ');
	file = open(next_arg, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);//TODO обработать ошибку
	if (file)
	{
		// if (fun_args.operator_flag == '0')
		// {
			bin_exe_path = search(fun_args.args[0], get_env_param("PATH", fun_args.env));
			oldstdout = dup(1);
			dup2(file, 1);
			close(file);
			if (exe_function)
				exe_function(&fun_args);
			else if (bin_exe_path)
				launch_shell(fun_args, bin_exe_path);
			// else
			// {
				
			// }
			dup2(oldstdout, 1);
			free(bin_exe_path);
		// }
		
	}
	return (1);
}