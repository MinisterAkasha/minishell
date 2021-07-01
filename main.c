#include "Includes/minishell.h"

void	wait_child_process_end(pid_t id, t_list *var_list)
{
	int			status;
	char		*str_status;
	t_variable	*var;

	waitpid(id, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WEXITSTATUS(status) && !WIFSIGNALED(status))
		waitpid(id, &status, WUNTRACED);
	str_status = ft_itoa(status / 256);
	var = find_variable(g_general->variables, "?");
	if (ft_atoi(var->value) == 130 || ft_atoi(var->value) == 131)
		add_variable(&var_list, create_var("?", var->value, 0, 0));
	else
		add_variable(&var_list, create_var("?", str_status, 0, 0));
	free(str_status);
}

int		launch_process(t_exe_args exe_args, char *bin_path)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (!child_process_id)
	{
		if (execve(bin_path, exe_args.args, exe_args.env) == -1)
			write_error("minishell: ", bin_path, "No such file or directory");
	}
	else if (child_process_id < 0)
		write_error("FORK ERROR: ", strerror(errno), "");
	else
		wait_child_process_end(child_process_id, exe_args.variables);
	return (1);
}

void	init_env(char **env, t_store *store)
{
	store->exe_args.env_init = remove_param_from_2d_arr(env, "OLDPWD");
	store->exe_args.env = remove_param_from_2d_arr(env, "OLDPWD");
	add_variable(&store->exe_args.variables, create_var("OLDPWD", "", 1, 0));
}

int		loop_shell(t_store *store)
{
	char			*line;
	char			**args;
	int				status;
	t_history		*history;

	init_history_data(&history);
	status = 1;
	init_support_parsing_arr(&store->support);
	shlvl(&store->exe_args);
	add_variable(&store->exe_args.variables, create_var("?", "0", 0, 0));
	init_general_signal(store);
	while (status)
	{
		gnl(&line, history);
		args = split(line);
		store->exe_info = get_exe_info(args, store, line);
		status = execute(store);
		ft_lstclear(&store->exe_info, &exe_info_lstclear);
		free_2d_arr(args);
		free(line);
	}
	free_2d_arr(history->arr);
	free(history);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	t_store *store;

	if (!(store = (t_store*)ft_calloc(sizeof(t_store), 1)))
		ft_error_malloc();
	store->exe_args.args = argv;
	store->exe_args.variables = NULL;
	init_env(env, store);
	init_fd(&store->exe_args);
	loop_shell(store);
	free_2d_arr(store->exe_args.env);
	return (argc);
}
