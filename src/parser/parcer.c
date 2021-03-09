/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 20:32:35 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_cd(char **args)
{
	write(1, "cd\n", 3);
	return (1);
}
int			exe_pwd(char **args)
{
	char dir[100];

	ft_putendl_fd(getcwd(dir, 100), 1);
	return (1);
}
int			exe_echo(char **args)
{
	write(1, "echo\n", 5);
	return (1);
}
int			exe_export(char **args)
{
	write(1, "export\n", 7);
	return (1);
}
int			exe_unset(char **args)
{
	write(1, "unset\n", 6);
	return (1);
}
int			exe_env(char **args)
{
	write(1, "env\n", 4);
	return (1);
}
int			exe_exit(char **args)
{
	write(1, "exit\n", 5);
	return (1);
}

int			unknown_command(char **args)
{
	write(1, "minishell: ", 12);
	write(1, args[0], ft_strlen(args[0]));
	write(1, ": command not found\n", 21);
	return (1);
}


t_exe_info	parser(char **args, t_support_parsing_data support)
{
	t_exe_info		info;
	int				i;

	i = 0;
	info.exe_function = NULL;
	info.operator_exe_function = NULL;
	info.args = args;
	while (i < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(args[0], support.exe_str_arr[i]))
			info.exe_function = support.exe_func_arr[i];
		i++;
	}
	if (!info.exe_function)
		info.exe_function = unknown_command;
	info.oper = "";
	return (info);
}
