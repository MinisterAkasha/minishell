/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:46:31 by akasha            #+#    #+#             */
/*   Updated: 2021/03/30 18:02:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exe_function(t_exe_info	*exe_info, t_exe_args *exec_args)
{
	t_variable	*var;

	exe_info->exe_function(exec_args);
	var = find_variable(exec_args->variables, "?");
	exit(ft_atoi(var->value));
}

void	handle_pipe_childe_process(int fd[2], t_exe_args *exec_args, t_exe_info	*exe_info)
{
	int			old_stdout;
	char		*bin_path;

	close(fd[0]);
	bin_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
	old_stdout = dup(1);
	dup2(fd[1], 1);
	if (bin_path)
		execve(bin_path, exec_args->args, exec_args->env);
	else if (exe_info->exe_function)
		run_exe_function(exe_info, exec_args);
	dup2(old_stdout, 1);
	close(fd[1]);
	free(bin_path);
}

void	handle_pipe_parent_process(int fd[2], t_exe_args *exec_args, t_exe_info	*exe_info, int pid)
{
	int		old_stdout;
	int		status;
	char	*bin_path;
	int		pid_2;
	
	close(fd[1]);
	
	pid_2 = fork();
	if (!pid_2)
	{
		old_stdout = dup(0);
		dup2(fd[0], 0);
		bin_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
		if (bin_path)
			execve(bin_path, exec_args->args, exec_args->env);
		else if (exe_info->exe_function)
			run_exe_function(exe_info, exec_args);
		dup2(old_stdout, 0);
	}
	else if (pid_2 > 0)
		wait_child_process_end(pid_2, exec_args->variables);
	close(fd[0]);
}

int		exe_oper_pipe(t_exe_args *exec_args, t_list *info)
{
	t_list		*tmp;
	t_exe_info	*exe_info;
    pid_t		pid;
	int			i;
	char		*bin_path;
	int			old_stdout;
	int			fd_1[2];// C -> P 
	int			fd_2[2];// P -> C
	int			status;
	/* 
	** fd[0] - read
	** fd[1] - write
	*/

	i = 0;
	tmp = info;
	while (tmp->next)
	{
		exe_info = tmp->content;
		if (exe_info->operator_exe_function != exe_oper_pipe)
			break ;

		if (pipe(fd_1) == -1)// || pipe(fd_2) == -1)//TODO
		{
			printf("Can\'t create pipe\n");
			exit(-1);
		}
		pid = fork();
		if (!pid)
			handle_pipe_childe_process(fd_1, exec_args, exe_info);
		else if (pid > 0)
		{
			exe_info = tmp->next->content;
			free_2d_arr(exec_args->args);
			exec_args->args = ft_split(exe_info->args, ' ');
			handle_pipe_parent_process(fd_1, exec_args, exe_info, pid);
		}
		else
			printf("FORK ERROR: CODE: %d\n", errno);//TODO обработать ошибку
		i++;
		tmp = tmp->next;
	}
	return (i);
}