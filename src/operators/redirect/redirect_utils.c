#include "minishell.h"

void	add_args(char ***exec_args, t_exe_info *exe_info_next)
{
	char	**args_copy;
	char	**next_arg_arr;
	int		i;

	i = 1;
	next_arg_arr = ft_split(exe_info_next->args, ' ');
	while (next_arg_arr[i])
	{
		args_copy = copy_2d_arr(*exec_args);
		free_2d_arr(*exec_args);
		*exec_args = add_param_to_2d_arr(args_copy, next_arg_arr[i]);
		free_2d_arr(args_copy);
		i++;
	}
	free_2d_arr(next_arg_arr);
}

int		check_is_redirect_funtion(t_exe_info *current)
{
	if (current->oper_exe_func != exe_oper_redirect
			&& current->oper_exe_func != exe_oper_double_redirect
			&& current->oper_exe_func != exe_oper_reverse_redirect)
		return (0);
	return (1);
}

void	write_to_file(t_exe_info *original, t_exe_args *exec_args)
{
	if (exec_args->fd[4] != -2)
		run_command_to_dup_fd(exec_args, original);
	close(exec_args->fd[0]);
	close(exec_args->fd[2]);
	reset_fd(exec_args);
}

void	error_redirect_command(t_exe_args *exec_args, int oldstd_out)
{
	t_variable	*var;

	var = find_variable(exec_args->variables, "?");
	if (ft_atoi(var->value) != 127)
	{
		dup2(oldstd_out, exec_args->fd[1]);
		add_variable(&exec_args->variables, create_var("?", "1", 0, 0));
		invalid_input(exec_args);
	}
}
