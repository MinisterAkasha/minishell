/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 21:34:48 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_needed_fd(t_exe_info *next, t_exe_info *current,
		t_exe_args *exec_args)
{
	char		**next_arg_arr;

	next_arg_arr = ft_split(next->args, ' ');
	exec_args->fd[1] = 1;
	if (current->oper_exe_func == exe_oper_redirect)
		exec_args->fd[0] = open(next_arg_arr[0], O_CREAT | O_TRUNC | O_RDWR
				| O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (current->oper_exe_func == exe_oper_double_redirect)
		exec_args->fd[0] = open(next_arg_arr[0], O_CREAT | O_RDWR | O_APPEND,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (current->oper_exe_func == exe_oper_reverse_redirect)
	{
		exec_args->fd[0] = open(next_arg_arr[0], O_RDWR);
		exec_args->fd[1] = 0;
	}
	else
		return ;
	if (exec_args->fd[0] == -1)
		write_error("minishell: ", next_arg_arr[0], strerror(errno));
	free_2d_arr(next_arg_arr);
}

static void	run_command_to_dup_fd(t_exe_args *exec_args, t_exe_info *original)
{
	char	*bin_exe_path;
	int		oldstdout;

	bin_exe_path = search(exec_args->args[0],
			get_env_param("PATH", exec_args->env));
	oldstdout = dup(exec_args->fd[1]);
	dup2(exec_args->fd[0], exec_args->fd[1]);
	if (original->exe_function)
		original->exe_function(exec_args);
	else if (bin_exe_path)
		launch_shell(*exec_args, bin_exe_path);
	else if (!exec_args->args[0])
		;
	else
	{
		dup2(oldstdout, exec_args->fd[1]);
		unknown_command(exec_args);
	}
	dup2(oldstdout, exec_args->fd[1]);
	free(bin_exe_path);
}

void		open_and_write_to_file(t_exe_info *next, t_exe_info *original,
	t_exe_args *exec_args, t_exe_info *current)
{
	int			oldstdout;
	char		*bin_exe_path;

	open_needed_fd(next, current, exec_args);
	if (next->oper_exe_func != exe_oper_redirect
		&& next->oper_exe_func != exe_oper_double_redirect)
	{
		if (exec_args->fd[0] && exec_args->fd[0] != -1)
			run_command_to_dup_fd(exec_args, original);
	}
	close(exec_args->fd[0]);
}

int			exe_oper_redirect(t_exe_args *exec_args, t_list *info)
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
		if (current->oper_exe_func != exe_oper_redirect
			&& current->oper_exe_func != exe_oper_double_redirect
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
