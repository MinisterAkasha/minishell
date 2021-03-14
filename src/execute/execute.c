/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:53:58 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], ": command not found");
	return (1);
}

int	execute(t_store *store, char **args)
{
	t_exe_info	info;
	char		*bin_exe_path;

	if (!args[0])
		return (1);
	info = parser(args, store->support);
	store->exe_args.args = info.args;
	if (info.exe_function)
		info.exe_function(&store->exe_args);
	else if ((bin_exe_path = search(store->exe_args.args[0], get_env_param("PATH", store->exe_args.env)))) 
	{
		launch_shell(store->exe_args.env, args, bin_exe_path);
		free(bin_exe_path);
	}
	else
		unknown_command(&store->exe_args);
	return (1);
}
