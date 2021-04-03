/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 17:45:56 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], "command not found");
	add_variable_to_list(&exe_arg->variables, "?", "127", 0, 0);
	return (1);
}

char	**get_args(t_exe_info *exe_info, t_support_parsing_data support)
{
	char	**args;

	if (exe_info->exe_function == support.exe_func_arr[1])
	{
		args = (char **)protect_malloc(ft_calloc(sizeof(char *), 2));
		args[0] = protect_malloc(ft_strdup(exe_info->args));
	}
	else
		args = protect_ft_split(ft_split(exe_info->args, ' '));
	return (args);
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
		store->exe_args.args = get_args(exe_info, store->support);
		bin_exe_path = search(store->exe_args.args[0], get_env_param("PATH", store->exe_args.env));
		if (exe_info->oper_exe_func &&
			exe_info->oper_exe_func != exe_oper_semicolon)
		{
			i = exe_info->oper_exe_func(&store->exe_args, info);
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
