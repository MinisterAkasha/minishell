/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/04/09 15:57:05 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unknown_command(t_exe_args *exe_arg)
{
	write_error("minishell: ", exe_arg->args[0], "command not found");
	add_variable(&exe_arg->variables, create_var("?", "127", 0, 0));
	return (1);
}

char	**get_args(t_exe_info *exe_info, t_support_parsing_data support)
{
	char	**args;
	char	*copy_arg;

	copy_arg = ft_strdup(exe_info->args);
	if (exe_info->exe_function == support.exe_func_arr[1])
	{
		if (ft_strlen(copy_arg) == 1)
		{
			args = (char **)malloc(sizeof(char *) + 2);
			args[0] = ft_strdup(copy_arg);
			args[1] = NULL;
		}
		else
			args = ft_split(copy_arg, '\0');
	}
	else
		args = ft_split(copy_arg, ' ');
	free(copy_arg);
	return (args);
}

int		choose_command_and_run(t_exe_info *exe_info, t_store *store,
	t_list **info)
{
	char		*bin_exe_path;
	int			i;

	if (!exe_info->exe_function)
		bin_exe_path = search(store->exe_args.args[0],
			get_env_param("PATH", store->exe_args.env));
	if (exe_info->oper_exe_func &&
		exe_info->oper_exe_func != exe_oper_semicolon)
	{
		i = exe_info->oper_exe_func(&store->exe_args, *info);
		while (i--)
			*info = (*info)->next;
	}
	else if (exe_info->exe_function)
		exe_info->exe_function(&store->exe_args);
	else if (bin_exe_path)
		launch_shell(store->exe_args, bin_exe_path);
	else if (!ft_strlen(exe_info->args))
	{
		free(bin_exe_path);
		return (1);
	}
	else if (get_env_param("PATH", store->exe_args.env))
		unknown_command(&store->exe_args);
	if (!exe_info->exe_function)
		free(bin_exe_path);
	return (0);
}

int		execute(t_store *store)
{
	t_list		*info;
	t_exe_info	*exe_info;

	info = store->exe_info;
	while (info)
	{
		exe_info = info->content;
		store->exe_args.args = get_args(exe_info, store->support);
		if (choose_command_and_run(exe_info, store, &info))
		{
			free_2d_arr(store->exe_args.args);
			return (1);
		}
		free_2d_arr(store->exe_args.args);
		info = info->next;
	}
	return (1);
}
