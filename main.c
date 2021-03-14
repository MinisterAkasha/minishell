/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:06 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:53:34 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void wait_child_process_end(pid_t id)
{
	int status;

	waitpid(id, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(id, &status, WUNTRACED);
}

int launch_shell(char **env, char **args, char *bin_path)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (!child_process_id)
	{
		if (execve(bin_path, args, env) == -1)
			printf("EXECVE ERROR. CODE: %s\n", strerror(errno)); //TODO обработать ошибку
	}
	else if (child_process_id < 0)
		printf("FORK ERROR: CODE: %d\n", errno); //TODO обработать ошибку
	else
		wait_child_process_end(child_process_id);
	return (1);
}

int loop_shell(t_store *store)
{
	char			*line;
	char			**args;
	int				status;

	status = 1;
	init_support_parsing_arr(&store->support);
	shlvl(store->exe_args.env);
	while (status)
	{
		ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
		get_next_line(0, &line);
		args = ft_split(line, ' ');
		status = execute(store, args);
		free(line);
		free_2d_arr(args);
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_store *store;

	if (!(store = (t_store*)malloc(sizeof(t_store))))
		return (0); //TODO обработать ошибку
	store->exe_args.args = argv;
	store->exe_args.env = create_env(env);
	store->exe_args.variables = NULL;
	// add_variable_to_list(&store->exe_args.variables, "name", "Ilya", 0);
	// add_variable_to_list(&store->variables, "id", "1", 0);
	// add_variable_to_list(&store->variables, "status", "ok", 0);
	// t_variable *variable = find_variable(store->variables, "name");
	loop_shell(store);
	free_2d_arr(store->exe_args.env);
	return (0);
}