/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:06 by akasha            #+#    #+#             */
/*   Updated: 2021/03/21 20:43:42 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void wait_child_process_end(pid_t id, t_list *var)
{
	int status;

	waitpid(id, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WEXITSTATUS(status) && !WIFSIGNALED(status))
		waitpid(id, &status, WUNTRACED);
	add_variable_to_list(&var, "?", ft_itoa(status / 256), 0, 0);
}

int launch_shell(t_store *store, char *bin_path)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (!child_process_id)
	{
		if (execve(bin_path, store->exe_args.args, store->exe_args.env) == -1)
			printf("EXECVE ERROR. CODE: %s\n", strerror(errno)); //TODO обработать ошибку
	}
	else if (child_process_id < 0)
		printf("FORK ERROR: CODE: %d\n", errno); //TODO обработать ошибку
	else
		wait_child_process_end(child_process_id, store->exe_args.variables);
	return (1);
}

int loop_shell(t_store *store)
{
	char			*line;
	char			**args;
	int				status;
	char			**history;

	history = protect_malloc((char **)ft_calloc(sizeof(char *), 2));
	*history = protect_malloc(ft_strdup(""));
	status = 1;//TODO начального OLDPWD нет
	init_support_parsing_arr(&store->support);
	shlvl(store->exe_args.env_init);
	add_variable_to_list(&store->exe_args.variables, "?", "0", 0, 0);
	while (status) //TODO пофиксить пустой инпут
	{
//		ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
//		get_next_line(0, &line);
		if (!gnl(&line, NULL))
		{
			printf("\nCtrl-D\n");
			return (1);
		}
		args = split(line);
		store->exe_info = get_exe_info(args, store);
		status = execute(store);//TODO Убрать лик (лик аргумента)
		ft_lstclear(&store->exe_info, &exe_info_lstclear);
		free_2d_arr(args);
		free(line);
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_store *store;

	if (!(store = (t_store*)malloc(sizeof(t_store))))
		return (0); //TODO обработать ошибку
	store->exe_args.args = argv;
	store->exe_args.env = copy_2d_arr(env);
	store->exe_args.env_init = copy_2d_arr(store->exe_args.env);
	store->exe_args.variables = NULL;
	loop_shell(store);
	free_2d_arr(store->exe_args.env);
	return (0);
}