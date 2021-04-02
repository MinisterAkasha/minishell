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
	info_arr[0] = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '$'))
		{
			init_data_dollar_count(&info_arr, head);
			info_arr[0] = i;
		}
		info_arr[1]++;
		i++;
	}
	if (!str[i])
	{
		info_arr[1]++;
		init_data_dollar_count(&info_arr, head);
	}
	return (1);
}

static char		*find_env(t_exe_args exe_args, char *s_dol)
{
	t_variable	*tmp_variable;
	char		*env;

	env = 0;
	if ((ft_strcmp(s_dol, "")) && (env = get_env_param(s_dol, exe_args.env)))
		env = protect_malloc(ft_strdup(ft_strchr(env, '=') + 1));
	else
	{
		tmp_variable = find_variable(exe_args.variables, s_dol);
		if (tmp_variable)
			env = protect_malloc(ft_strdup(tmp_variable->value));
	}
	if (!env)
		env = protect_malloc(ft_strdup(""));
	return (env);
}

static char		*get_str_dollar(char ***arr, char **tmp_str, int i)
{
	char	*str_dollar;

	if ((*arr)[i][1] && (*arr)[i][1] == '?')
	{
		str_dollar = "?";
		*tmp_str = protect_malloc(ft_strdup((*arr)[i] + 2));
	}
	else
	{
		str_dollar = (*arr)[i] + 1;
		*tmp_str = protect_malloc(ft_strdup(""));
	}
	return (str_dollar);
}

static void		change_dollar_to_env(char ***arr, t_exe_args exe_args)
{
	int			i;
	char		*tmp_str;
	char		*str_dollar;
	char		*env;

	i = 0;
	while ((*arr)[i])
	{
		if ((*arr)[i][0] && (*arr)[i][1] && (*arr)[i][0] == '$'
											&& (*arr)[i][1] != ' ')
		{
			str_dollar = get_str_dollar(arr, &tmp_str, i);
			env = find_env(exe_args, str_dollar);
			free((*arr)[i]);
			(*arr)[i] = protect_malloc(ft_strjoin(env, tmp_str));
			free(env);
			free(tmp_str);
		}
		i++;
	}
}

/*
** Change $str to str from the env variable
*/

char			*dollar_sign(char *arg, t_exe_args exe_args, char sep)
{
	t_list	*head;
	t_list	*copy_head;
	char	*changed_arg;
	char	**double_arr;

	head = NULL;
	if (sep != '\'')
	{
		dollar_count(arg, &head);
		copy_head = head;
		double_arr = init_arr_2d(arg, copy_head);
		change_dollar_to_env(&double_arr, exe_args);
		changed_arg = multiply_strjoin(double_arr);
		free_2d_arr(double_arr);
		ft_lstclear(&head, &del_item_libft_lst);
	}
	else
		changed_arg = protect_malloc(ft_strdup(arg));
	return (changed_arg);
}
