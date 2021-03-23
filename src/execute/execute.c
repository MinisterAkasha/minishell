/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/23 13:19:06 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], ": command not found");
	add_variable_to_list(&exe_arg->variables, "?", "127", 0, 0);
	return (1);
}

int	execute(t_store *store)
{
	t_exe_info	*info;
	char		*bin_exe_path;

	info = store->exe_info;
	store->exe_args.args = ft_split(info->args, ' ');
	if (info->exe_function)
		info->exe_function(&store->exe_args);
	else if ((bin_exe_path = search(store->exe_args.args[0], get_env_param("PATH", store->exe_args.env)))) 
	{
		launch_shell(store, bin_exe_path);
		free(bin_exe_path);
	}
	else
		unknown_command(&store->exe_args);
	free_2d_arr(store->exe_args.args);
	return (1);
}
