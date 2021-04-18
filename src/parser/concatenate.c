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

int		is_concatenate(char **args, int i, t_exe_info *exe_info)
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

void	cut_escape(char **str)
{
	char	*copy_str;
	char	*str_without_escape;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy_str = ft_strdup(*str);
	str_without_escape = ft_calloc(ft_strlen(copy_str) + 1, sizeof(char));
	while (copy_str[i])
	{
		if (copy_str[i] == '\\' &&
		(copy_str[i + 1] == '"' || copy_str[i + 1] == '\\'))
			i++;
		str_without_escape[j] = copy_str[i];
		j++;
		i++;
	}
	free(*str);
	free(copy_str);
	(*str) = ft_strdup(str_without_escape);
	free(str_without_escape);
}

char	*change_str(char *copy_second, t_exe_args exe_args,
				t_exe_info *exe_info)
{
	char		*modified_arg;
	char		separator;

	separator = get_separator(copy_second);
	if (copy_second[0] == '\\')
		modified_arg = ft_substr(copy_second, 1, ft_strlen(copy_second) - 1);
	else
	{
		if (copy_second[0] == '\'')
			modified_arg = ft_strdup(copy_second);
		else
			modified_arg = dollar_sign(copy_second, exe_args, exe_info);
		cut_separator(&modified_arg, separator);
		if (separator == '"')
			cut_escape(&modified_arg);
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
	modified_arg = change_str(copy_second, exe_args, exe_info);
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
	int		is_flag_n;

	if (is_concatenate(args, i, exe_info))
	{
		concat_args(store->exe_args, &exe_info->args, args[i], exe_info);
		is_flag_n = validate_flag_n(exe_info->args, exe_info);
		if (is_flag_n && (!args[i + 1]
			|| (args[i] && args[i + 1] && !ft_strcmp(args[i + 1], " "))))
		{
			if (exe_info->is_flag_n == 0)
				exe_info->is_flag_n = 1;
			free(exe_info->args);
			exe_info->args = ft_strdup("");
		}
	}
}
