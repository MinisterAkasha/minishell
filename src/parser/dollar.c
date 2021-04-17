/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:48:01 by tilda             #+#    #+#             */
/*   Updated: 2021/04/14 14:37:33 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create a linked list 'head'
** Which has data to cut the 'str' by $ and spaces
** info_arr[0] - is index of start
** info_arr[1] - is len to cut the str
*/

static int		dollar_count(char *str, t_list **head, t_exe_info *exe_info)
{
	int		i;
	int		*info_arr;

	i = 0;
	init_data_dollar_count(&info_arr, head);
	while (str[i])
	{
		if (str[i] && ((str[i] == '\\' || (str[i] == '$' && str[i - 1] != '\\'))
			|| (str[i] == '=' && exe_info->exe_function == exe_export)))
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

char			*get_changed_str(t_exe_args exe_args, char *arr_str)
{
	int		i;
	char	*env;
	char	*str_tail;
	char	*changed_str;
	char	*copy_str;

	i = 0;
	changed_str = ft_strdup("");
	while (arr_str[i])
	{
		env = get_str_dollar(exe_args, arr_str, &i);
		str_tail = get_tail(arr_str, &i);
		copy_str = ft_strdup(changed_str);
		free(changed_str);
		changed_str = triple_str_join(copy_str, env, str_tail);
		free(env);
		free(str_tail);
		free(copy_str);
		if (!arr_str[i])
			break ;
		i++;
	}
	return (changed_str);
}

int				ft_costil(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (str[0] == '$')
	{
		if (str[1] == '\'')
		{
			if (str[len - 1] == '"')
			{
				return (0);
			}
		}
	}
	return (1);
}

static void		change_dollar_to_env(char ***arr, t_exe_args exe_args)
{
	int			i;
	char		*tmp_str;

	i = 0;
	while ((*arr)[i])
	{
		tmp_str = ft_strdup((*arr)[i]);
		free((*arr)[i]);
		if ((*arr)[i][0] && (*arr)[i][0] == '$' && ft_isdigit((*arr)[i][1]))
			(*arr)[i] = ft_substr(tmp_str, 2, ft_strlen(tmp_str) - 2);
		else if ((*arr)[i][0] && (*arr)[i][1] && (*arr)[i][0] == '$'
			&& (*arr)[i][1] != ' ' && ft_costil((*arr)[i]))
		{
			(*arr)[i] = get_changed_str(exe_args, tmp_str);
		}
		else if ((*arr)[i][0] && (*arr)[i][0] == '\\' && (*arr)[i][1] == '$')
			(*arr)[i] = ft_substr(tmp_str, 1, ft_strlen(tmp_str) - 1);
		else
			(*arr)[i] = ft_strdup(tmp_str);
		free(tmp_str);
		i++;
	}
}

/*
** Change $str to str from the env variable
*/

char			*dollar_sign(char *arg, t_exe_args exe_args,
					t_exe_info *exe_info)
{
	t_list	*head;
	t_list	*copy_head;
	char	*changed_arg;
	char	**double_arr;

	head = NULL;
	dollar_count(arg, &head, exe_info);
	copy_head = head;
	double_arr = init_arr_2d(arg, copy_head);
	change_dollar_to_env(&double_arr, exe_args);
	changed_arg = multiply_strjoin(double_arr);
	free_2d_arr(double_arr);
	ft_lstclear(&head, &del_item_libft_lst);
	return (changed_arg);
}
