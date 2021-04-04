/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:57:01 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 20:01:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_needed_fd(t_exe_info *exe_info, t_exe_args *exec_args,
	t_exe_info *exe_info_next)
{
	char	**arr;

	exec_args->fd[1] = 1;
	arr = ft_split(exe_info_next->args, ' ');
	if (exe_info->oper_exe_func == exe_oper_redirect)
		exec_args->fd[0] = open(arr[0], O_CREAT | O_TRUNC | O_RDWR | O_APPEND,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (exe_info->oper_exe_func == exe_oper_double_redirect)
		exec_args->fd[0] = open(arr[0], O_CREAT | O_RDWR | O_APPEND,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else if (exe_info->oper_exe_func == exe_oper_reverse_redirect)
	{
		exec_args->fd[0] = open(arr[0], O_RDWR);
		exec_args->fd[1] = 0;
	}
	if (exec_args->fd[0] == -1)
		write_error_message("minishell: ", arr[0], strerror(errno));
	free_2d_arr(arr);
}

int			check_redirect(int **fd, int index, t_list *info,
	t_exe_args *exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			j;

	tmp = info;
	while (index-- > 0)
		tmp = info->next;
	exe_info = tmp->content;
	j = 0;
	while (tmp
		&& (exe_info->oper_exe_func == exe_oper_redirect
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
