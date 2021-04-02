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

char	*get_str_to_compare(char **args, t_exe_args exe_args, int *i)
{
	char			*str_to_compare;

	str_to_compare = protect_malloc(ft_strdup(""));
	while (args[*i] && ft_strcmp(args[*i], " ")
			&& ft_strcmp(args[*i], "|")
			&& ft_strcmp(args[*i], ";")
			&& ft_strcmp(args[*i], ">")
			&& ft_strcmp(args[*i], "<")
			&& ft_strcmp(args[*i], ">>"))
	{
		concat_args(exe_args, &str_to_compare, args[*i]);
		*i += 1;
	}
	return (str_to_compare);
}

void	set_default_new_lst(t_list **lst)
{
	t_exe_info	*exe_info;

	exe_info = protect_malloc(ft_calloc(1, sizeof(t_exe_info)));
	exe_info->exe_function = NULL;
	exe_info->oper_exe_func = NULL;
	exe_info->args = protect_malloc(ft_strdup(""));
	ft_lstadd_back(lst, ft_lstnew(exe_info));
}

void	init_arg(t_exe_info **exe_info_lst, char *str)
{
	free((*exe_info_lst)->args);
	(*exe_info_lst)->args = protect_malloc(ft_strdup(str));
}

int		is_word_to_cont(char *str, char sep, int i)
{
	int		cur_operands;
	int		next_operands;
	int		is_separator;
	int		is_space;

	is_separator = (str[i] == '"' || str[i] == '\'');
	next_operands = (str[i + 1] == ';' || str[i + 1] == '|' ||
						str[i + 1] == '>' || str[i + 1] == '<');
	cur_operands = (str[i] == ';' || str[i] == '|' ||
						str[i] == '>' || str[i] == '<');
	is_space = ((str[i] == ' ' && sep == 'f') ||
				(str[i + 1] == ' ' && sep == 'f'));
	if (str[i + 1] == '\0' || is_space
		|| (sep == str[i] && is_separator)
		|| (sep == 'f' && next_operands)
		|| (sep == 'f' && cur_operands))
	{
		return (1);
	}
	return (0);
}

int		init_data_dollar_count(int **info_arr, t_list **head)
{
	if (!((*info_arr) = (int *)ft_calloc(2, sizeof(int))))
		error_malloc();
	ft_lstadd_back(head, protect_malloc(ft_lstnew((*info_arr))));
	return (1);
}
