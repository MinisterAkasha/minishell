/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:46:31 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 17:22:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_all_processes(int *pid, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		kill(pid[i], 0);
		i++;
	}
}

int	*create_child_processes(int pipe_num, t_list *info,
	t_exe_args *exec_args, int **fd)
{
	int			*pid;
	t_list		*tmp;
	t_exe_info	*exe_info;
	int			i;

	if (!(pid = (int *)malloc(sizeof(int) * (pipe_num + 1))))
		ft_error_malloc();
	i = -1;
	tmp = info;
	while (++i <= pipe_num && tmp->next)
	{
		exe_info = tmp->content;
		pid[i] = fork();
		if (pid[i] == 0)
			handle_pipe_command(fd, exe_info, exec_args, i);
		else if (pid[i] == -1)
			kill_all_processes(pid, i);
		exe_info = tmp->next->content;
		free_2d_arr(exec_args->args);
		exec_args->args = ft_split(exe_info->args, ' ');
		tmp = tmp->next;
	}
	if (exe_info->oper_exe_func != exe_oper_redirect
		&& exe_info->oper_exe_func != exe_oper_double_redirect
		&& exe_info->oper_exe_func != exe_oper_reverse_redirect
		&& exe_info->oper_exe_func != NULL)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			handle_pipe_command(fd, exe_info, exec_args, i);
		else if (pid[i] == -1)
			kill_all_processes(pid, i);
	}
	return (pid);
}

int	handle_parent_process(int *pid, int **fd)
{
	int	i;
	int	status;

	i = 0;
	while (i <= get_int_arr_length(fd))
	{
		waitpid(pid[i], &status, WUNTRACED);
		if (i == 0)
			close(fd[i][1]);
		else if (i == get_int_arr_length(fd))
			close(fd[i - 1][0]);
		else
		{
			close(fd[i - 1][0]);
			close(fd[i][1]);
		}
		i++;
	}
	return (i);
}

void	open_needed_fd(t_exe_info *exe_info, t_exe_args *exec_args, t_exe_info *exe_info_next)
{
	char **arr;

	arr = ft_split(exe_info_next->args, ' ');
	if (exe_info->oper_exe_func == exe_oper_redirect)
		exec_args->fd[0] = open(arr[0], O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (exe_info->oper_exe_func == exe_oper_double_redirect)
		exec_args->fd[0] = open(arr[0], O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (exe_info->oper_exe_func == exe_oper_reverse_redirect)
	{
		exec_args->fd[0] = open(arr[0], O_RDWR);
		exec_args->fd[1] = 0;
	}
	if (exec_args->fd[0] == -1)
		write_error_message("minishell: ", arr[0], strerror(errno));
	free_2d_arr(arr);
}

int	check_redirect(int **fd, int index, t_list *info, t_exe_args *exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			j;

	tmp = info;
	j = 0;
	while (j++ < index)
		tmp = info->next;
	exe_info = tmp->content;
	exec_args->fd[1] = 1;
	j = 0;
	while (tmp && 
		(exe_info->oper_exe_func == exe_oper_redirect
		|| exe_info->oper_exe_func == exe_oper_double_redirect
		|| exe_info->oper_exe_func == exe_oper_reverse_redirect))
	{
		j++;
		if (exec_args->fd[0] != -1)
			close(exec_args->fd[0]);
		exe_info_next = tmp->next->content;
		if (!(exec_args->fd[0] == -1 && exec_args->fd[1] == 0))
			open_needed_fd(exe_info, exec_args, exe_info_next);
		tmp = tmp->next;
		exe_info = tmp->content;
	}
	return (j);
}

int	exe_oper_pipe(t_exe_args *exec_args, t_list *info)
{
	int			**fd;
	int			*pid;
	int			pipe_num;
	int			i;
	int			red;

	pipe_num = get_pipe_number(info);
	fd = create_pipe_fd(pipe_num);
	red = check_redirect(fd, pipe_num, info, exec_args);
	if (exec_args->fd[0] == -1 && red)
		return (pipe_num + red);
	pid = create_child_processes(pipe_num, info, exec_args, fd);
	i = handle_parent_process(pid, fd);
	free(pid);
	free_2d_arr_int(fd);
	return (i + red - 1);
}
