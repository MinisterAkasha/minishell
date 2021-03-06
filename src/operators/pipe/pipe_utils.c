#include "minishell.h"

int		get_pipe_number(t_list *info)
{
	int			num;
	t_list		*tmp;
	t_exe_info	*exe_info;

	num = 0;
	tmp = info;
	exe_info = tmp->content;
	while (exe_info && exe_info->oper_exe_func == exe_oper_pipe)
	{
		tmp = tmp->next;
		exe_info = tmp->content;
		num++;
	}
	return (num);
}

int		**create_pipe_fd(int num, t_exe_args *exec_args)
{
	int		**fd;
	int		i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (num + 1));
	if (!fd)
		ft_error_malloc();
	while (i < num)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			ft_error_malloc();
		if (i == 0 && exec_args->pipe_fd[1] != -1)
		{
			fd[i][0] = exec_args->pipe_fd[0];
			fd[i][1] = exec_args->pipe_fd[1];
		}
		else
			pipe(fd[i]);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

void	run_exe_function(t_exe_info *exe_info, t_exe_args *exec_args)
{
	t_variable	*var;

	exe_info->exe_function(exec_args);
	var = find_variable(exec_args->variables, "?");
	exit(ft_atoi(var->value));
}

void	run_command(char *bin_path, t_exe_info *exe_info, t_exe_args *exec_args)
{
	int			res;
	t_variable	*var;

	res = open(exec_args->args[0], O_RDWR);
	if (exe_info->exe_function)
		run_exe_function(exe_info, exec_args);
	else if (bin_path)
		execve(bin_path, exec_args->args, exec_args->env);
	else if (res != -1)
	{
		close(res);
		exit(0);
	}
	else
	{
		var = find_variable(exec_args->variables, "?");
		if (ft_atoi(var->value) != 127)
			invalid_input(exec_args);
		exit(127);
	}
}

void	check_command(char *path, t_exe_info *exe_info,
	t_exe_args *exec_args, int i)
{
	int			res;
	t_variable	*var;

	res = open(exec_args->args[0], O_RDWR);
	if (res != -1 && i == 0)
		close(res);
	else if (!exe_info->exe_function && !path)
	{
		if (res != -1)
			close(res);
		var = find_variable(exec_args->variables, "?");
		if (ft_atoi(var->value) != 127)
			invalid_input(exec_args);
		exit(127);
	}
}
