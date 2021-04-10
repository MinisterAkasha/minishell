/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:10:16 by akasha            #+#    #+#             */
/*   Updated: 2021/04/10 18:24:38 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	use_correct_open(t_exe_args *exec_args,
	char *next_fd, t_exe_info *exe_info)
{
	if (exe_info->oper_exe_func == exe_oper_redirect)
	{
		close(exec_args->fd[0]);
		exec_args->fd[0] = open(next_fd,
			O_CREAT | O_TRUNC | O_RDWR | O_APPEND,
			S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	}
	else if (exe_info->oper_exe_func == exe_oper_double_redirect)
	{
		close(exec_args->fd[0]);
		exec_args->fd[0] = open(next_fd,
			O_CREAT | O_RDWR | O_APPEND,
			S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	}
	else if (exe_info->oper_exe_func == exe_oper_reverse_redirect)
	{
		close(exec_args->fd[2]);
		exec_args->fd[2] = open(next_fd, O_RDWR);
		if (exec_args->fd[2] == -1)
		{
			write_error("minishell: ", next_fd, strerror(errno));
			add_variable(&exec_args->variables, create_var("?", "1", 0, 0));
			exec_args->fd[4] = -2;
		}
	}
}

static void	open_needed_fd(t_list *info, t_exe_args *exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;
	t_exe_info	*next_exe_info;
	t_list		*next_info;
	char		**next_fd;

	tmp = info;
	exe_info = tmp->content;
	exec_args->fd[1] = 1;
	exec_args->fd[3] = 0;
	while (tmp
		&& (exe_info->oper_exe_func == exe_oper_redirect
		|| exe_info->oper_exe_func == exe_oper_double_redirect
		|| exe_info->oper_exe_func == exe_oper_reverse_redirect))
	{
		next_info = tmp->next;
		next_exe_info = next_info->content;
		next_fd = ft_split(next_exe_info->args, ' ');
		if (exec_args->fd[4] != -2)
			use_correct_open(exec_args, next_fd[0], exe_info);
		free_2d_arr(next_fd);
		tmp = tmp->next;
		exe_info = tmp->content;
	}
}

static void	run_command_to_dup_fd(t_exe_args *exec_args, t_exe_info *original)
{
	char	*path;
	int		oldstd_out;
	int		oldstd_in;

	path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
	oldstd_out = dup(1);
	oldstd_in = dup(0);
	if (exec_args->fd[0] != -1)
		dup2(exec_args->fd[0], 1);
	if (exec_args->fd[2] != -1)
		dup2(exec_args->fd[2], 0);
	if (original->exe_function)
		original->exe_function(exec_args);
	else if (path)
		launch_process(*exec_args, path);
	else if (!exec_args->args[0])
		;
	else
	{
		dup2(oldstd_out, exec_args->fd[1]);
		add_variable(&exec_args->variables, create_var("?", "1", 0, 0));
		unknown_command(exec_args);
	}
	dup2(oldstd_out, 1);
	dup2(oldstd_in, 0);
	free(path);
}

void		write_to_file(t_exe_info *next, t_exe_info *original,
	t_exe_args *exec_args, t_exe_info *current)
{
	if (exec_args->fd[4] != -2)
		run_command_to_dup_fd(exec_args, original);
	close(exec_args->fd[0]);
	close(exec_args->fd[2]);
	reset_fd(exec_args);	
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
	open_needed_fd(tmp, exec_args);
	while (tmp->next)
	{
		if (current->oper_exe_func == exe_oper_pipe)
			i--;
		if (!check_is_redirect_funtion(current))
			break ;
		exe_info_next = tmp->next->content;
		add_args(&exec_args->args, exe_info_next);
		tmp = tmp->next;
		current = tmp->content;
		i++;
	}
	write_to_file(exe_info_next, exe_info, exec_args, current);
	return (i);
}
