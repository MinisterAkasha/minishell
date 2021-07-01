#include "minishell.h"

static void	pipe_redirect_error(t_exe_args *exec_args, char *error_body)
{
	add_variable(&exec_args->variables, create_var("?", "1", 0, 0));
	write_error("minishell: ", error_body, strerror(errno));
	exec_args->fd[4] = -2;
}

static void	open_needed_fd(t_exe_info *exe_info, t_exe_args *exec_args,
	t_exe_info *exe_info_next)
{
	char	**arr;

	arr = ft_split(exe_info_next->args, ' ');
	if (exe_info->oper_exe_func == exe_oper_redirect)
	{
		close(exec_args->fd[0]);
		exec_args->fd[0] = open(arr[0], O_CREAT | O_TRUNC | O_RDWR | O_APPEND,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	}
	else if (exe_info->oper_exe_func == exe_oper_double_redirect)
	{
		close(exec_args->fd[0]);
		exec_args->fd[0] = open(arr[0], O_CREAT | O_RDWR | O_APPEND,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	}
	else if (exe_info->oper_exe_func == exe_oper_reverse_redirect)
	{
		close(exec_args->fd[2]);
		exec_args->fd[2] = open(arr[0], O_RDWR);
		exec_args->fd[4] = -3;
	}
	if (exec_args->fd[2] == -1 && exec_args->fd[4] == -3)
		pipe_redirect_error(exec_args, arr[0]);
	free_2d_arr(arr);
}

int			check_redirect(int index, t_list *info,
	t_exe_args *exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			j;

	tmp = info;
	while (index-- > 0)
		tmp = tmp->next;
	exe_info = tmp->content;
	j = 0;
	exec_args->fd[1] = 1;
	exec_args->fd[3] = 0;
	while (tmp && (check_is_redirect_funtion(exe_info)))
	{
		j++;
		exe_info_next = tmp->next->content;
		if (exec_args->fd[4] != -2)
			open_needed_fd(exe_info, exec_args, exe_info_next);
		tmp = tmp->next;
		exe_info = tmp->content;
	}
	return (j);
}
