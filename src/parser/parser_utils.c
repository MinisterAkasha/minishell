/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:30:17 by tilda             #+#    #+#             */
/*   Updated: 2021/03/18 15:55:22 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str_to_compare(char **args, t_exe_args exe_args, int *i,
						t_exe_info *exe_info)
{
	char			*str_to_compare;

	str_to_compare = ft_strdup("");
	while (args[*i] && ft_strcmp(args[*i], " ")
			&& ft_strcmp(args[*i], "|")
			&& ft_strcmp(args[*i], ";")
			&& ft_strcmp(args[*i], ">")
			&& ft_strcmp(args[*i], "<")
			&& ft_strcmp(args[*i], ">>"))
	{
		concat_args(exe_args, &str_to_compare, args[*i], exe_info);
		*i += 1;
	}
	return (str_to_compare);
}

void	set_default_new_lst(t_list **lst)
{
	t_exe_info	*exe_info;

	exe_info = ft_calloc(1, sizeof(t_exe_info));
	exe_info->exe_function = NULL;
	exe_info->oper_exe_func = NULL;
	exe_info->args = ft_strdup("");
	exe_info->is_flag_n = 0;
	exe_info->double_arr_args = (char **)ft_calloc(sizeof(char *), 1);
	ft_lstadd_back(lst, ft_lstnew(exe_info));
}

void	init_arg(t_exe_info **exe_info_lst, char *str)
{
	free((*exe_info_lst)->args);
	(*exe_info_lst)->args = ft_strdup(str);
}

int		init_data_dollar_count(int **info_arr, t_list **head)
{
	(*info_arr) = (int *)ft_calloc(2, sizeof(int));
	ft_lstadd_back(head, ft_lstnew((*info_arr)));
	return (1);
}

int		validate_flag_n(char *str, t_exe_info *exe_info)
{
	int		i;

	i = 0;
	if (exe_info->exe_function != exe_echo)
		return (0);
	else if (exe_info->is_flag_n == 1)
		return (1);
	if (str[i] && str[i + 1])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] && str[i] == 'n')
				i++;
			if (!str[i])
				return (1);
		}
	}
	return (0);
}
