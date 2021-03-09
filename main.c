/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:06 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 19:29:00 by akasha           ###   ########.fr       */
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

int launch_shell(t_data *data, char **args)
{
	pid_t child_process_id;

	if (!ft_strcmp(args[0], "./minishell")) {
		child_process_id = fork();
		if (!child_process_id)
		{
			if (execve(data->procces_name, args, data->env) == -1)
				printf("%d", errno); //TODO обработать ошибку
		}
		else if (child_process_id < 0)
			printf("%d", errno); //TODO обработать ошибку
		else
			wait_child_process_end(child_process_id);
	}
	return (1);
}

int loop_shell(t_data *data)
{
	char			*line;
	char			**args;
	int				status;
	t_support_parsing_data	support;

	status = 1;
	init_support_parsing_arr(&support);
	while (status)
	{
		ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
		get_next_line(0, &line);
		args = ft_split(line, ' ');
		status = execute(data, args, support);
		free(line);
		free_2d_arr(args);
		free(args);
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_data *data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (0); //TODO обработать ошибку
	data->argv = argv;
	data->env = env;
	data->procces_name = argv[0];
	loop_shell(data);
	return (0);
}