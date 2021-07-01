#include "minishell.h"

void	init_support_parsing_arr(t_support_parsing_data *data)
{
	data->exe_str_arr[0] = "cd";
	data->exe_str_arr[1] = "echo";
	data->exe_str_arr[2] = "pwd";
	data->exe_str_arr[3] = "export";
	data->exe_str_arr[4] = "unset";
	data->exe_str_arr[5] = "env";
	data->exe_str_arr[6] = "exit";
	data->exe_func_arr[0] = &exe_cd;
	data->exe_func_arr[1] = &exe_echo;
	data->exe_func_arr[2] = &exe_pwd;
	data->exe_func_arr[3] = &exe_export;
	data->exe_func_arr[4] = &exe_unset;
	data->exe_func_arr[5] = &exe_env;
	data->exe_func_arr[6] = &exe_exit;
	data->operators_arr[0] = ";";
	data->operators_arr[1] = "|";
	data->operators_arr[2] = ">";
	data->operators_arr[3] = ">>";
	data->operators_arr[4] = "<";
	data->operators_exe_func_arr[0] = &exe_oper_semicolon;
	data->operators_exe_func_arr[1] = &exe_oper_pipe;
	data->operators_exe_func_arr[2] = &exe_oper_redirect;
	data->operators_exe_func_arr[3] = &exe_oper_double_redirect;
	data->operators_exe_func_arr[4] = &exe_oper_reverse_redirect;
}

void	init_history_data(t_history **history)
{
	(*history) = (t_history *)ft_calloc(sizeof(t_history), 1);
	(*history)->arr = (char **)ft_calloc(sizeof(char *), 2);
	(*history)->total = 0;
	(*history)->cur = (*history)->total;
}

void	init_general_signal(t_store *store)
{
	g_general = ft_calloc(1, sizeof(t_general));
	g_general->variables = store->exe_args.variables;
	signal(2, signal_listener);
	signal(3, signal_listener);
}

void	init_fd(t_exe_args *exe_args)
{
	exe_args->fd[0] = -1;
	exe_args->fd[1] = -1;
	exe_args->fd[2] = -1;
	exe_args->fd[3] = -1;
	exe_args->fd[4] = 0;
	exe_args->pipe_fd[0] = -1;
	exe_args->pipe_fd[1] = -1;
}
