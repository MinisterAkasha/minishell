/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/04/12 13:55:54 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tcl.h>
#include <tclDecls.h>
#include "minishell.h"

static int		init_redirection(t_exe_info **exe_info_lst,
				t_support_parsing_data support)
{
	if ((*exe_info_lst)->oper_exe_func != NULL
		&& (*exe_info_lst)->oper_exe_func != support.operators_exe_func_arr[0]
		&& (*exe_info_lst)->oper_exe_func != support.operators_exe_func_arr[1])
	{
		(*exe_info_lst)->exe_function = NULL;
		return (1);
	}
	else if (!(*exe_info_lst)->exe_function)
		return (1);
	return (0);
}

static void		search_exe_func(char *str_lower,
						t_support_parsing_data support, t_exe_info *exe_info)
{
	int		j;
	char	*del_elem;
	char	**copy_arr;

	j = 0;
	while (j < (int)(sizeof(support.exe_str_arr) / sizeof(char *)))
	{
		if (!ft_strcmp(str_lower, support.exe_str_arr[j]))
		{
			del_elem = ft_strdup(exe_info->double_arr_args[0]);
			copy_arr = copy_2d_arr(exe_info->double_arr_args);
			free_2d_arr(exe_info->double_arr_args);
			exe_info->double_arr_args = remove_elem_2d_arr(copy_arr, del_elem);
			free_2d_arr(copy_arr);
			free(del_elem);
			exe_info->exe_function = support.exe_func_arr[j];
			break ;
		}
		j++;
	}
}

static void		init_exec_func(t_list **lst,
								t_store *store, char **args, int *i)
{
	t_list			*tmp_lst;
	t_exe_info		*exe_info;
	char			*str_to_compare;
	char			*str_lower;

	tmp_lst = *lst;
	exe_info = tmp_lst->content;
	if (args[*i] && !ft_strcmp(args[*i], " "))
		*i += 1;
	str_to_compare = get_str_to_compare(args, store->exe_args, i, exe_info);
	str_lower = str_to_lower(str_to_compare);
	search_exe_func(str_lower, store->support, exe_info);
	if (init_redirection(&exe_info, store->support))
		init_arg(&exe_info, str_lower);
	else if (args[*i] && !ft_strcmp(args[*i], " "))
		*i += 1;
	free(str_lower);
	free(str_to_compare);
}

static int		init_operator(t_list **tmp_lst, int i,
								t_support_parsing_data support, char **args)
{
	t_exe_info	*exe_info;
	int			j;

	exe_info = (*tmp_lst)->content;
	j = 0;
	while (j < (int)(sizeof(support.operators_arr) / sizeof(char *)))
	{
		if (!ft_strcmp(args[i], support.operators_arr[j]))
		{
			exe_info->oper_exe_func = support.operators_exe_func_arr[j];
			if (!args[i + 1])
				return (0);
			set_default_new_lst(tmp_lst);
			(*tmp_lst) = (*tmp_lst)->next;
			return (0);
		}
		j++;
	}
	return (1);
}

t_list			*get_exe_info(char **args, t_store *store)
{
	t_list		*head;
	t_list		*tmp_lst;
	t_exe_info	*exe_info;
	int			i;

	i = 0;
	head = NULL;
	set_default_new_lst(&head);
	tmp_lst = head;
	while (args[i])
	{
		init_exec_func(&tmp_lst, store, args, &i);
		while (args[i] && init_operator(&tmp_lst, i, store->support, args))
		{
			exe_info = tmp_lst->content;
			to_concatenate(args, i, store, exe_info);
			i++;
		}
		if (!args[i])
			break ;
		i++;
	}
	return (head);
}
