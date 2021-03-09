/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 17:09:39 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_cd(char **args){
	write(1, "cd\n", 3);
	return (1);
}
int			exe_pwd(char **args){
	write(1, "pwd\n", 4);
	return (1);
}
int			exe_echo(char **args){
	write(1, "echo\n", 5);
	return (1);
}
int			exe_export(char **args){
	write(1, "export\n", 7);
	return (1);
}
int			exe_unset(char **args){
	write(1, "unset\n", 6);
	return (1);
}
int			exe_env(char **args){
	write(1, "env\n", 4);
	return (1);
}
int			exe_exit(char **args){
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

void init_support(t_parser_data *data)
{
	data->exe_str[0] = "cd";
	data->exe_str[1] = "echo";
	data->exe_str[2] = "pwd";
	data->exe_str[3] = "export";
	data->exe_str[4] = "unset";
	data->exe_str[5] = "env";
	data->exe_str[6] = "exit";
	data->exe_func_arr[0] = &exe_cd;
	data->exe_func_arr[1] = &exe_echo;
	data->exe_func_arr[2] = &exe_pwd;
	data->exe_func_arr[3] = &exe_export;
	data->exe_func_arr[4] = &exe_unset;
	data->exe_func_arr[5] = &exe_env;
	data->exe_func_arr[6] = &exe_exit;
}

t_exe_info	parser(char **args)
{
	t_exe_info		info;
	t_parser_data	support;
	int				i;

	init_support(&support);
	i = 0;
	info.exe_function = NULL;
	info.operator_exe_function = NULL;
	info.args = args;
	while (i < sizeof(support.exe_str) / sizeof(char *))
	{
		if (!ft_strcmp(args[0], support.exe_str[i]))
			info.exe_function = support.exe_func_arr[i];
		i++;
	}
	if (!info.exe_function)
		info.exe_function = unknown_command;
	info.oper = "";
	return (info);
}
