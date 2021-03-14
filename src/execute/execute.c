/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:39:53 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], ": command not found");
	return (1);
}

int	execute(t_data *data, char **args, t_support_parsing_data support, t_exe_args *exe_arg)
{
	t_exe_info	info;
	char		*bin_exe_path;

	if (!args[0])
		return (1);
	info = parser(args, support);
	exe_arg->args = info.args;
	if (info.exe_function)
		info.exe_function(exe_arg);
	else if ((bin_exe_path = search(exe_arg->args[0], get_env_param("PATH", exe_arg->env)))) 
	{
		launch_shell(exe_arg->env, args, bin_exe_path);
		free(bin_exe_path);
	}
	else
		unknown_command(exe_arg);
	return (1);
}
