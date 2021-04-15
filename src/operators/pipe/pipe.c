/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:46:31 by akasha            #+#    #+#             */
/*   Updated: 2021/04/15 20:40:53 by akasha           ###   ########.fr       */
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

void	get_next_exec_argc(t_list *info, t_exe_args **exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;

	tmp = info;
	exe_info = tmp->next->content;
	free_2d_arr((*exec_args)->args);
	(*exec_args)->args = ft_split(exe_info->args, ' ');
}

int		*create_child_processes(int pipe_num, t_list *info,
	t_exe_args *exec_args, int **fd)
{
	int			*pid;
	t_list		*tmp;
	t_exe_info	*exe_info;
	int			i;

	pid = (int *)malloc(sizeof(int) * (pipe_num + 1));
	if (!pid)
		ft_error_malloc();
	i = -1;
	tmp = info;
	while (++i <= pipe_num)
	{
		exe_info = tmp->content;
		if (check_is_redirect_funtion(exe_info))
			add_args(&exec_args->args, tmp->next->content);
		pid[i] = fork();
		if (pid[i] == 0)
			handle_pipe_command(fd, exe_info, exec_args, i);
		else if (pid[i] == -1)
			kill_all_processes(pid, i);
		if (tmp->next)
			get_next_exec_argc(tmp, &exec_args);
		tmp = tmp->next;
	}
	return (pid);
}

int		handle_parent_process(int *pid, int **fd, t_list *var,
	t_exe_args *exec_args)
{
	int	i;

	i = 0;
	while (i <= get_int_arr_length(fd))
	{
		wait_child_process_end(pid[i], var);
		if (i == 0)
			close(fd[i][1]);
		else if (i == get_int_arr_length(fd))
		{
			close(exec_args->fd[0]);
			close(exec_args->fd[2]);
			close(fd[i - 1][0]);
		}
		else
		{
			close(fd[i - 1][0]);
			close(fd[i][1]);
		}
		i++;
	}
	return (i);
}

int		exe_oper_pipe(t_exe_args *exec_args, t_list *info)
{
	int			**fd;
	int			*pid;
	int			pipe_num;
	int			i;
	int			red;

	pipe_num = get_pipe_number(info);
	fd = create_pipe_fd(pipe_num, exec_args);
	red = check_redirect(pipe_num, info, exec_args);
	if (exec_args->fd[4] == -2 && red)
	{
		reset_fd(exec_args);
		return (pipe_num + red);
	}
	pid = create_child_processes(pipe_num, info, exec_args, fd);
	i = handle_parent_process(pid, fd, exec_args->variables, exec_args);
	reset_fd(exec_args);
	exec_args->fd[1] = -1;
	free(pid);
	free_2d_arr_int(fd);
	return (i + red - 1);
}
