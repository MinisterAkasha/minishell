/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:06 by akasha            #+#    #+#             */
/*   Updated: 2021/03/30 18:03:28 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void wait_child_process_end(pid_t id, t_list *var)
{
	int		status;
	char	*str_status;

	waitpid(id, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WEXITSTATUS(status) && !WIFSIGNALED(status))
		waitpid(id, &status, WUNTRACED);
	str_status = ft_itoa(status / 256);
	add_variable_to_list(&var, "?", str_status, 0, 0);
	free(str_status);
}

int launch_shell(t_exe_args exe_args, char *bin_path)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (!child_process_id)
	{
		if (execve(bin_path, exe_args.args, exe_args.env) == -1)
			printf("EXECVE ERROR. CODE: %s\n", strerror(errno));//TODO обработать ошибку
	}
	else if (child_process_id < 0)
		printf("FORK ERROR: CODE: %d\n", errno);//TODO обработать ошибку
	else
		wait_child_process_end(child_process_id, exe_args.variables);
	return (1);
}

int loop_shell(t_store *store)
{
	char			*line;
	char			**args;
	int				status;
	t_history		*history;

	init_history_data(&history);
	status = 1;//TODO начального OLDPWD нет
	init_support_parsing_arr(&store->support);
	shlvl(store->exe_args.env_init);
	add_variable_to_list(&store->exe_args.variables, "?", "0", 0, 0);
	init_general_signal(store);
	while (status)
	{
		gnl(&line, history, store->exe_args.env);
		args = split(line);
		store->exe_info = get_exe_info(args, store);
		status = execute(store);
		ft_lstclear(&store->exe_info, &exe_info_lstclear);
		free_2d_arr(args);
		free(line);
	}
	free_2d_arr(history->arr);
	free(history);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_store *store;

	if (!(store = (t_store*)ft_calloc(sizeof(t_store), 1)))
		return (0); //TODO обработать ошибку
	store->exe_args.args = argv;
	store->exe_args.env = copy_2d_arr(env);
	store->exe_args.env_init = copy_2d_arr(store->exe_args.env);
	store->exe_args.variables = NULL;
	loop_shell(store);
	free_2d_arr(store->exe_args.env);
	return (0);
}