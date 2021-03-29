/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:46:31 by akasha            #+#    #+#             */
/*   Updated: 2021/03/28 22:04:25 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exe_oper_pipe(t_exe_args *exec_args, t_list *info)
{
    pid_t	pid;
	char	*bin_path;
	int		old_stdout;
	char	*buf;
	int 	res;
	int		fd_1[2];// C -> P 
	int		fd_2[2];// P -> C
	/* 
	** fd[0] - read
	** fd[1] - write
	*/

	if (pipe(fd_1) == -1)// || pipe(fd_2) == -1)
	{
		printf("Can\'t create pipe\n");
        exit(-1); 
	}
	bin_path = search(exec_args->args[0], get_env_param("PATH", exec_args->env));
	pid = fork();
	if (!pid)
	{
		close(fd_1[0]);
		old_stdout = dup(1);
		dup2(fd_1[1], 1);
		if (bin_path)
			execve(bin_path, exec_args->args, exec_args->env);
		dup2(old_stdout, 1);
		close(fd_1[1]);
	}
	else if (pid > 0)
	{
		// int status;
		// waitpid(pid, &status, WUNTRACED);
		buf = (char *)malloc(sizeof(char) * 1000);
		close(fd_1[1]);
		if ((res = read(fd_1[0], buf, 1000)) == -1)
			printf("ERROR\n");
		printf("%s\n", buf);
		close(fd_1[0]);
		// free(bin_path);
	}
	else
		printf("FORK ERROR: CODE: %d\n", errno); //TODO обработать ошибку
	return (1);
}