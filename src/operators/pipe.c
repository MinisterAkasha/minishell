/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:46:31 by akasha            #+#    #+#             */
/*   Updated: 2021/04/03 14:59:37 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_pipe_number(t_list *info)
{
	int			num;
	t_list		*tmp;
	t_exe_info	*exe_info;

	num = 0;
	tmp = info;
	exe_info = tmp->content;
	while (exe_info && exe_info->operator_exe_function == exe_oper_pipe)
	{
		tmp = tmp->next;
		exe_info = tmp->content;
		num++;
	}
	return (num);
}

int		**create_pipe_fd(int num)
{
	int		**fd;
	int		i;

	i = 0;
	fd = (int**)malloc(sizeof(int*) * (num + 1));
	while (i < num)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

void	run_exe_function(t_exe_info	*exe_info, t_exe_args *exec_args)
{
	t_variable	*var;

	exe_info->exe_function(exec_args);
	var = find_variable(exec_args->variables, "?");
	exit(ft_atoi(var->value));
}

void	close_unused_fd(int **fd, int index[2])
{
	int	i;
	int	j;

	i = 0;
	while (fd[i])
	{
		j = 0;
		while (fd[i][j])
		{
			if (fd[i][j] != index[0] && fd[i][j] != index[1])
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}

void	handle_pipe_command(int **fd, t_exe_info *exe_info, t_exe_args *exec_args, int i)
{
	int			old_stdout;
	int			old_stdin;
	char		*bin_path;
	int			index[2];

	old_stdout = dup(1);
	old_stdin = dup(0);
	bin_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
	if (i == 0)
	{
		index[0] = fd[i][1];
		index[1] = -1;
		close_unused_fd(fd, index);
		dup2(fd[i][1], 1);
		close(fd[i][1]);
	}
	else if (i == get_int_arr_length(fd))
	{
		i--;
		index[0] = fd[i][0];
		index[1] = -1;
		close_unused_fd(fd, index);
		dup2(fd[i][0], 0);
		close(fd[i][0]);
	}
	else
	{
		index[0] = fd[i - 1][0];
		index[1] = fd[i][1];
		close_unused_fd(fd, index);
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close(fd[i - 1][0]);
		close(fd[i][1]);
	}

	if (exe_info->exe_function)
		run_exe_function(exe_info, exec_args);
	else if (bin_path)
		execve(bin_path, exec_args->args, exec_args->env);
	dup2(old_stdout, 1);
	dup2(old_stdin, 0);
	free(bin_path);
}

int		*create_child_processes(int pipe_num, t_list *info, t_exe_args *exec_args, int **fd)
{
	int	*pid;
	t_list		*tmp;
	t_exe_info	*exe_info;
	int			i;

	pid = (int *)malloc(sizeof(int) * (pipe_num + 1));
	i = 0;
	tmp = info;
	while (tmp->next && i <= pipe_num)
	{
		exe_info = tmp->content;
		pid[i] = fork();
		if (pid[i] == 0)
			handle_pipe_command(fd, exe_info, exec_args, i);
		else if (pid[i] == -1)
		{
			// kill(pid[i], 0);
			//TODO kill pid[i] -> pid[0]
		}
		exe_info = tmp->next->content;
		free_2d_arr(exec_args->args);
		exec_args->args = ft_split(exe_info->args, ' ');
		i++;
		tmp = tmp->next;
	}
	pid[i] = fork();
	if (pid[i] == 0)
		handle_pipe_command(fd, exe_info, exec_args, i);
	return (pid);
}

int		handle_parent_process(int *pid, int **fd)
{
	int i;
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

int		exe_oper_pipe(t_exe_args *exec_args, t_list *info)
{
	int			**fd;
	int			*pid;
	int			pipe_num;
	int			i;

	pipe_num = get_pipe_number(info);
	fd = create_pipe_fd(pipe_num);
	pid = create_child_processes(pipe_num, info, exec_args, fd);
	i = handle_parent_process(pid, fd);
	free(pid);
	free_2d_arr_int(fd);
	return (i - 1);
}