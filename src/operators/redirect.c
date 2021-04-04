/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 19:12:49 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_args(char ***exec_args, t_exe_info	*exe_info_next)
{
	char	**args_copy;
	char	**next_arg_arr;
	int		i;

	i = 1;
	next_arg_arr = ft_split(exe_info_next->args, ' ');
	while (next_arg_arr[i])
	{
		args_copy = copy_2d_arr(*exec_args);
		free_2d_arr(*exec_args);
		*exec_args = add_param_to_2d_arr(args_copy, next_arg_arr[i]);
		free_2d_arr(args_copy);
		i++;
	}
	free_2d_arr(next_arg_arr);
}

void	open_and_write_to_file(t_exe_info *next, t_exe_info *original, t_exe_args *exec_args, t_exe_info *current)
{
	int			oldstdout;
	char		*bin_exe_path;
	char		**next_arg_arr;

	next_arg_arr = ft_split(next->args, ' ');
	exec_args->fd[1] = 1;
	if (current->oper_exe_func == exe_oper_redirect)
		exec_args->fd[0] = open(next_arg_arr[0], O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);//TODO обработать ошибку
	else if (current->oper_exe_func == exe_oper_double_redirect)
		exec_args->fd[0] = open(next_arg_arr[0], O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);//TODO обработать ошибку
	else if (current->oper_exe_func == exe_oper_reverse_redirect)
	{
		exec_args->fd[0] = open(next_arg_arr[0], O_RDWR);
		exec_args->fd[1] = 0;
	}
	else
		return ;
	if (exec_args->fd[0] == -1)
		write_error_message("minishell: ", next_arg_arr[0], strerror(errno));
	if (next->oper_exe_func != exe_oper_redirect &&
			next->oper_exe_func != exe_oper_double_redirect)
	{
		if (exec_args->fd[0] && exec_args->fd[0] != -1)
		{
			bin_exe_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
			oldstdout = dup(exec_args->fd[1]);
			dup2(exec_args->fd[0], exec_args->fd[1]);
			if (original->exe_function)
				original->exe_function(exec_args);
			else if (bin_exe_path)
				launch_shell(*exec_args, bin_exe_path);
			else if (!exec_args->args[0]);
			else
			{
				dup2(oldstdout, exec_args->fd[1]);
				unknown_command(exec_args);
			}
			dup2(oldstdout, exec_args->fd[1]);
			free(bin_exe_path);
		}
	}
	close(exec_args->fd[0]);
	free_2d_arr(next_arg_arr);
}

int		exe_oper_double_redirect(t_exe_args *exec_args, t_list *info)
{
	int i;
	
	i = exe_oper_redirect(exec_args, info);
	return i;
}

int		exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info)
{
	int			i;
	
	i = exe_oper_redirect(exec_args, info);
	return (i);
}

int		exe_oper_redirect(t_exe_args *exec_args, t_list *info)
{
	t_list		*tmp;
	t_exe_info	*current;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			i;

	i = 0;
	tmp = info;
	exe_info = tmp->content;
	current = tmp->content;
	while (tmp->next)
	{
		if (current->oper_exe_func != exe_oper_redirect &&
				current->oper_exe_func != exe_oper_double_redirect
			&& current->oper_exe_func != exe_oper_reverse_redirect)
			break ;
		exe_info_next = tmp->next->content;
		add_args(&exec_args->args, exe_info_next);
		open_and_write_to_file(exe_info_next, exe_info, exec_args, current);
		tmp = tmp->next;
		current = tmp->content;
		i++;
	}
	return (i);
}