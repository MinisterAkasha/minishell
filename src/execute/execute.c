/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 17:29:49 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], "command not found");
	add_variable_to_list(&exe_arg->variables, "?", "127", 0, 0);
	return (1);
}

int	execute(t_store *store)
{
	t_list		*info;
	t_exe_info 	*exe_info;
	char		*bin_exe_path;
	int			i;

	info = store->exe_info;
	i = 0;
	while (info)
	{
		exe_info = info->content;
		store->exe_args.args = ft_split(exe_info->args, ' ');//TODO переделать для echo
		bin_exe_path = search(store->exe_args.args[0], get_env_param("PATH", store->exe_args.env));
		if (exe_info->operator_exe_function && exe_info->operator_exe_function != exe_oper_semicolon)
		{
			i = exe_info->operator_exe_function(&store->exe_args, info);
			while (i--)
				info = info->next;
		}
		else if (exe_info->exe_function)
			exe_info->exe_function(&store->exe_args);
		else if (bin_exe_path)
			launch_shell(store->exe_args, bin_exe_path);
		else if (!ft_strlen(exe_info->args))
			return (1);
		else
			unknown_command(&store->exe_args);
		free(bin_exe_path);
		free_2d_arr(store->exe_args.args);
		info = info->next;
	}
	return (1);
}
