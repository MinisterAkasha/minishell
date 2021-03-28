/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/03/28 22:04:50 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_args(char ***exec_args, char **new_args)
{
	char	**args_copy;
	int		i;

	i = 1;
	while (new_args[i])
	{
		args_copy = copy_2d_arr(*exec_args);
		free_2d_arr(*exec_args);
		*exec_args = add_param_to_2d_arr(args_copy, new_args[i]);
		free_2d_arr(args_copy);
		i++;
	}
}

int		exe_oper_redirect(t_exe_args *exec_args, t_list *info)
{
	int			oldstdout;
	int			file;
	char		*bin_exe_path;
	char		**next_arg_arr;
	t_list		*tmp;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			i = 0;

	tmp = info;
	exe_info = tmp->content;
	while (tmp->next)
	{
		exe_info_next = tmp->next->content;
		next_arg_arr = ft_split(exe_info_next->args, ' ');
		add_args(&exec_args->args, next_arg_arr);
		file = open(next_arg_arr[0], O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);//TODO обработать ошибку
		if (exe_info_next->operator_exe_function != exe_oper_redirect)
		{
			if (file)
			{
				bin_exe_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
				oldstdout = dup(1);
				dup2(file, 1);
				if (exe_info->exe_function)
					exe_info->exe_function(exec_args);
				else if (bin_exe_path)
					launch_shell(*exec_args, bin_exe_path);
				dup2(oldstdout, 1);
				free(bin_exe_path);
			}
			close(file);
		}
		tmp = tmp->next;
		free_2d_arr(next_arg_arr);
		i++;
	}
	return (i);
}