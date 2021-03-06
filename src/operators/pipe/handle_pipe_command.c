#include "minishell.h"

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

void	handle_start_pipe_command(int **fd, int i)
{
	int	index[2];

	index[0] = fd[i][1];
	index[1] = -1;
	close_unused_fd(fd, index);
	dup2(fd[i][1], 1);
	close(fd[i][1]);
}

void	handle_center_pipe_command(int **fd, int i)
{
	int	index[2];

	index[0] = fd[i - 1][0];
	index[1] = fd[i][1];
	close_unused_fd(fd, index);
	dup2(fd[i - 1][0], 0);
	dup2(fd[i][1], 1);
	close(fd[i - 1][0]);
	close(fd[i][1]);
}

void	handle_end_pipe_command(int **fd, int i, t_exe_args *exec_args)
{
	int	index[2];

	i--;
	if (exec_args->fd[2] == -1)
		index[0] = fd[i][0];
	else
		index[0] = -1;
	if (exec_args->fd[0] == -1)
		index[1] = fd[i][1];
	else
		index[1] = -1;
	close_unused_fd(fd, index);
	if (exec_args->fd[2] != -1)
		dup2(exec_args->fd[2], 0);
	else
		dup2(fd[i][0], 0);
	if (exec_args->fd[0] != -1)
		dup2(exec_args->fd[0], 1);
	close(exec_args->fd[0]);
	close(exec_args->fd[2]);
	close(fd[i][1]);
	close(fd[i][0]);
}

void	handle_pipe_command(int **fd, t_exe_info *exe_info,
	t_exe_args *exec_args, int i)
{
	int			old_stdout;
	int			old_stdin;
	char		*bin_path;

	old_stdout = dup(1);
	old_stdin = dup(0);
	bin_path = search(exec_args,
			get_env_param("PATH", exec_args->env));
	check_command(bin_path, exe_info, exec_args, i);
	if (i == 0)
		handle_start_pipe_command(fd, i);
	else if (i == get_int_arr_length(fd))
		handle_end_pipe_command(fd, i, exec_args);
	else
		handle_center_pipe_command(fd, i);
	run_command(bin_path, exe_info, exec_args);
	dup2(old_stdout, 1);
	dup2(old_stdin, 0);
	free(bin_path);
}
