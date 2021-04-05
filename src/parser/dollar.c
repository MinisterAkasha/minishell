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
		init_data_dollar_count(&info_arr, head);
	return (1);
}

static char		*find_env(t_exe_args exe_args, char *s_dol)
{
	t_variable	*tmp_variable;
	char		*env;

	env = 0;
	if ((ft_strcmp(s_dol, "")) && (env = get_env_param(s_dol, exe_args.env)))
		env = ft_strdup(ft_strchr(env, '=') + 1);
	else
	{
		tmp_variable = find_variable(exe_args.variables, s_dol);
		if (tmp_variable)
			env = ft_strdup(tmp_variable->value);
	}
	if (!env)
		env = ft_strdup("");
	return (env);
}

static char *get_str_dollar(t_exe_args exe_args, char *arr_str, int *i)
{
	char	*str_dollar;
	char	*env;
	int		start;

	*i += 1;
	start = *i;
	if (arr_str[1] && arr_str[1] == '?')
	{
		str_dollar = ft_strdup("?");
		*i += 1;
	}
	else
	{
		while (arr_str[*i] && arr_str[*i] != ' ' && arr_str[*i] != '$')
			*i += 1;
		str_dollar = ft_substr(arr_str, start, *i - start);
	}
	env = find_env(exe_args, str_dollar);
	free(str_dollar);
	return (env);
}

static char *get_tail(char *arr_str, int *i)
{
	int		start;
	char	*tail_str;

	start = *i;
	while (arr_str[*i] && arr_str[*i] != '$')
		*i += 1;
	tail_str = ft_substr(arr_str, start, *i - start);
	return (tail_str);
}


char	*get_changed_str(t_exe_args exe_args, char *arr_str)
{
	int		i;
	char	*env;
	char	*str_tail;
	char	*changed_str;
	char	*copy_str;
	char	*tmp_str;

	i = 0;
	changed_str = ft_strdup("");
	while (arr_str[i])
	{
		env = get_str_dollar(exe_args, arr_str, &i);
		if (arr_str[i] && arr_str[i] != '$')
			str_tail = get_tail(arr_str, &i);
		else
			str_tail = ft_strdup("");
		copy_str = ft_strdup(changed_str);
		tmp_str = ft_strjoin(env, str_tail);
		changed_str = ft_strjoin(copy_str, tmp_str);
		free(env);
		free(str_tail);
		free(copy_str);
		free(tmp_str);
		if (!arr_str[i])
			break;
		i++;
	}
	return (changed_str);
}

static void		change_dollar_to_env(char ***arr, t_exe_args exe_args)
{
	int			i;
	char		*tmp_str;

	i = 0;
	while ((*arr)[i])
	{
		if ((*arr)[i][0] && (*arr)[i][1] && (*arr)[i][0] == '$'
											&& (*arr)[i][1] != ' ')
		{
			tmp_str = ft_strdup((*arr)[i]);
			free((*arr)[i]);
			(*arr)[i] = get_changed_str(exe_args, tmp_str);
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
		changed_arg = ft_strdup(arg);
	return (changed_arg);
}
