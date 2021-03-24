/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:48:01 by tilda             #+#    #+#             */
/*   Updated: 2021/03/23 19:48:02 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		init_data_dollar_count(int **info_arr, t_list **head)
{
	if (!(*info_arr = (int *)ft_calloc(2, sizeof(int))))
		error_malloc();
	ft_lstadd_back(head, protect_malloc(ft_lstnew(*info_arr)));
	return (1);
}

/*
** Create a linked list 'head'
** Which has data to cut the 'str' by $ and spaces
** Structure of the linked:
** start_index -> len -> start_index -> len -> ...
*/

static	int		dollar_count(char *str, t_list **head)
{
	int			i;
	int			*info_arr;

	i = 0;
	init_data_dollar_count(&info_arr, head);
	while (str[i])
	{
		info_arr[1]++;
		if (str[i] && str[i] != '"' && str[i] != ' ' && str[i] != '$')
			init_data_dollar_count(&info_arr, head);
		if (info_arr[1] == 0)
			info_arr[0] = i;
	}
	return (1);
}

void		change_dollar_to_env(char ***arr, t_exe_args exe_args)
{
	int			i;
	t_variable	*tmp_variable;
	char		*tmp_str;
	char		*str_dollar;
	char		*env;

	i = 0;
	tmp_str = 0;
	while((*arr)[i])
	{
		if ((*arr)[i][0] && (*arr)[i][0] == '$')
		{
			if ((*arr)[i][1] && (*arr)[i][1] == '?')
			{
				str_dollar = "$?";
				tmp_str = protect_malloc(ft_strdup((*arr)[i] + 2));
//				if (!(str_dollar = get_env_param("$?", exe_args.env)))
//				{
//					tmp_variable = find_variable(exe_args.variables, "$?");
//					if (tmp_variable)
//						str_dollar = tmp_variable->value;
//				}
//				if (str_dollar)
//					str_dollar = protect_malloc(ft_strdup(str_dollar));//TODO May be leak
//				free((*arr)[i]);
//				(*arr)[i] = protect_malloc(ft_strjoin(str_dollar, tmp_str));
			}
			else
			{
				str_dollar = (*arr)[i] + 1;
				tmp_str = protect_malloc(ft_strdup(""));
//				if (!(str_dollar = get_env_param((*arr)[i] + 1, exe_args.env)))
//				{
//					tmp_variable = find_variable(exe_args.variables, (*arr)[i] + 1);
//					if (tmp_variable)
//						str_dollar = tmp_variable->value;
//				}
//				if (str_dollar)
//				{
//					free((*arr)[i]);
//					(*arr)[i] = protect_malloc(ft_strdup(str_dollar));
//				}
			}

			if (!(env = get_env_param(str_dollar, exe_args.env)))
			{
				tmp_variable = find_variable(exe_args.variables, str_dollar);
				if (tmp_variable)
					env = tmp_variable->value;
			}
			if (env)
				env = protect_malloc(ft_strdup(env));//TODO May be leak
			free((*arr)[i]);
			(*arr)[i] = protect_malloc(ft_strjoin(env, tmp_str));
		}
		i++;
	}
}

char		*multiply_strjoin(char **args)
{
	int		i;
	char	*cur_str;
	char	*next_str;
	char	*str;

	i = 0;
	str = NULL;
	while (args[i])
	{
		i++;
	}
	return (str);
}

void			dollar_sign(char **arg, t_exe_args exe_args)
{
	t_list	*head;
	t_list	*copy_head;
	char	*copy_arg;
	char	**double_arr;

	dollar_count(*arg, &head);
	copy_head = head;
	copy_arg = ft_strdup(*arg);
	double_arr = init_arr_2d(*arg, copy_head);
	change_dollar_to_env(&double_arr, exe_args);
	//TODO склеить двумерный массив



	free_2d_arr(double_arr);
	ft_lstclear(&head, &del_item_libft_lst);
}
