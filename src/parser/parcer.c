/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/18 15:37:46 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int			exe_pwd(t_exe_args *exe_args)
// {
// 	char path[100];

// 	//TODO обработать ошибки
// 	ft_putendl_fd(getcwd(path, 100), 1);
// 	return (1);
// }
// int			exe_echo(t_exe_args *exe_args)
// {
// 	write(1, "echo\n", 5);
// 	return (1);
// }
// // int			exe_export(t_exe_args *exe_args)
// // {
// // 	write(1, "export\n", 7);
// // 	return (1);
// // }
// int			exe_unset(t_exe_args *exe_args)
// {
// 	write(1, "unset\n", 6);
// 	return (1);
// }
// int			exe_exit(t_exe_args *exe_args)
// {
// 	exit(1);
// 	write(1, "exit\n", 5);
// 	return (1);
// }

// t_exe_info	parser(char **args, t_support_parsing_data support)
// {
// 	t_exe_info		info;
// 	int				i;

// 	i = 0;
// 	info.exe_function = NULL;
// 	info.operator_exe_function = NULL;
// 	info.args = args;
// 	while (i < sizeof(support.exe_str_arr) / sizeof(char *))
// 	{
// 		if (!ft_strcmp(args[0], support.exe_str_arr[i]))
// 			info.exe_function = support.exe_func_arr[i];
// 		i++;
// 	}
// 	if (!info.exe_function)
// 		info.exe_function = NULL;
// 	info.oper = "";
// 	return (info);
// }
