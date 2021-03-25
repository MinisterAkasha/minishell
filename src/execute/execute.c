/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/24 15:18:32 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			unknown_command(t_exe_args *exe_arg)
{
	write_error_message("minishell: ", exe_arg->args[0], ": command not found");
	add_variable_to_list(&exe_arg->variables, "?", "127", 0, 0);
	return (1);
}

int	*fill_operators_flag_arr(t_exe_info	*info)
{
	int		*arr;
	t_exe_info	*tmp;
	t_exe_info	*tmp_2;
	int			len;
	int			i;

	tmp = info;
	tmp_2 = info;
	len = 0;
	i = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	arr = (int*)malloc(sizeof(int) * len);
	while (tmp_2)
	{
		if (tmp_2->operator_exe_function == exe_oper_semicolon)
			arr[i] = 0;
		else if (tmp_2->operator_exe_function)
			arr[i] = 1;
		else
			arr[i] = 0;
		tmp_2 = tmp_2->next;
		i++;
	}
	return (arr);
}

int	execute(t_store *store)
{
	t_exe_info	*info;
	char		*bin_exe_path;
	int			i = 0;
	int			*operators_flags;

	info = store->exe_info;
	operators_flags = fill_operators_flag_arr(info);
	while (info)
	{
		store->exe_args.operator_flag = operators_flags[i];
		store->exe_args.args = ft_split(info->args, ' ');//TODO переделать для echo
		bin_exe_path = search(store->exe_args.args[0], get_env_param("PATH", store->exe_args.env));
		if (info->operator_exe_function)
			info->operator_exe_function(store->exe_args.args, info->next->args, info->exe_function, store->exe_args);
		else if (info->exe_function)
			info->exe_function(&store->exe_args);
		else if (bin_exe_path)
			launch_shell(store->exe_args, bin_exe_path);
		// else if (!info->operator_exe_function && !info->exe_function);
		else
			unknown_command(&store->exe_args);
		free(bin_exe_path);
		free_2d_arr(store->exe_args.args);
		i++;
		info = info->next;
	}
	free(operators_flags);
	return (1);
}
