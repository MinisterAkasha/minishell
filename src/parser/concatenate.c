/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:19:22 by tilda             #+#    #+#             */
/*   Updated: 2021/04/14 12:41:01 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_concatenate(char **args, int i, t_exe_info *exe_info)
{
	char	*next_arg;
	char	*current_arg;
	int		result;

	result = 1;
	current_arg = ft_strdup(args[i]);
	if (args[i + 1])
	{
		next_arg = ft_strdup(args[i + 1]);
		if (!ft_strcmp(current_arg, " ") && (!ft_strcmp(next_arg, "|")
											|| !ft_strcmp(next_arg, ";")
											|| !ft_strcmp(next_arg, ">")
											|| !ft_strcmp(next_arg, "<")
											|| !ft_strcmp(next_arg, ">>")
											|| !ft_strcmp(exe_info->args, "")))
		{
			result = 0;
		}
	}
	else
		next_arg = ft_strdup("");
	free(current_arg);
	free(next_arg);
	return (result);
}

char	*str_without_escape(char *str)
{
	char	*str_without_escape;

	str_without_escape = ft_substr(str, 1, ft_strlen(str) - 1);
	return (str_without_escape);
}

char *change_str(char *copy_first, char *copy_second, t_exe_args exe_args,
				 t_exe_info *exe_info)
{
	char	*modified_arg;
	char		separator;

	separator = get_separator(copy_second);
	if (copy_second[0] == '\\')
		modified_arg = str_without_escape(copy_second);
	else if (copy_second[0] == '\'')
	{
		modified_arg = ft_strdup(copy_second);
		cut_separator(&modified_arg, separator);
	}
	else
	{
		modified_arg = dollar_sign(copy_second, exe_args, exe_info);
		cut_separator(&modified_arg, separator);
	}
	if (modified_arg[0] == '-' &&  exe_info->exe_function == exe_echo
		&& (!ft_strcmp(copy_first, "") || !ft_strcmp(copy_first, " ")))
	{
		exe_info->is_flag_n = validate_flag_n(modified_arg, exe_info);
		if (exe_info->is_flag_n)
		{
			free(modified_arg);
			modified_arg = ft_strdup("");
		}
	}
	return (modified_arg);
}

void	concat_args(t_exe_args exe_args, char **first, char *second,
					t_exe_info *exe_info)
{
	char		*copy_first;
	char		*modified_arg;
	char		*copy_second;
	char		**copy_arr;

	copy_second = ft_strdup(second);
	copy_first = ft_strdup(*first);
	free(*first);
	modified_arg = change_str(copy_first, copy_second, exe_args, exe_info);
	(*first) = ft_strjoin(copy_first, modified_arg);
	copy_arr = copy_2d_arr(exe_info->double_arr_args);
	if (ft_strcmp(modified_arg, " "))
	{
		free_2d_arr(exe_info->double_arr_args);
		exe_info->double_arr_args = add_param_to_2d_arr(copy_arr, modified_arg);
	}
	free_2d_arr(copy_arr);
	free(copy_second);
	free(copy_first);
	free(modified_arg);
}

void	to_concatenate(char **args, int i, t_store *store,
							t_exe_info *exe_info)
{
	if (is_concatenate(args, i, exe_info))
	{
		concat_args(store->exe_args, &exe_info->args, args[i], exe_info);
//		exe_info->is_flag_n = validate_flag_n(exe_info);
	}
}
