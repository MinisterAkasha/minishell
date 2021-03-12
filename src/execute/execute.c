/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/12 17:05:55 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(char **args, char **env)
{
	write_error_message("minishell: ", args[0], ": command not found");
	return (1);
}

int	execute(t_data *data, char **args, t_support_parsing_data support)
{
	t_exe_info	info;
	char		*bin_exe_path;

	if (!args[0])
		return (1);
	info = parser(args, support);
	if (info.exe_function)
		info.exe_function(info.args, data->env);
	else if (bin_exe_path)
	{
		bin_exe_path = search(info.args[0], get_env_param("PATH", data->env));
		launch_shell(data, args, bin_exe_path);
		free(bin_exe_path);
	}
	else
		unknown_command(info.args, data->env);
	return (1);
}
