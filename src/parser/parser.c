/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/18 22:24:15 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_create_env(t_exe_args *exe_args)
{
	return (1);
}

int			exe_pwd(t_exe_args *exe_args)
{
	char path[100];

	//TODO обработать ошибки
	ft_putendl_fd(getcwd(path, 100), 1);
	return (1);
}
int			exe_echo(t_exe_args *exe_args)
{
	write(1, "echo\n", 5);
	return (1);
}
int			exe_exit(t_exe_args *exe_args)
{
	exit(1);
	write(1, "exit\n", 5);
	return (1);
}

// int			unknown_command(t_exe_args *exe_args)
// {
// 	write_error_message("minishell: ", exe_args->args[0], ": command not found");
// 	return (1);
// }

static	void	init_redirection(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	if ((*tmp_lst)->operator_exe_function != NULL
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[0]
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[1])
	{
		(*tmp_lst)->exe_function = NULL;
		free((*tmp_lst)->args);
		(*tmp_lst)->args = ft_strdup(str);
		*decrement -= 1;
	}
	return ;
}

static	void	init_exe_env(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	char	**splited_str;
	int		result;
	int		i;

	result = 1;
	i = 0;
	splited_str = ft_split(str, '=');
	if (get_arr_length(splited_str) < 2)
		result = 0;
	while (splited_str[0][i])
	{
		if (!ft_isalnum(splited_str[0][i]))
			result = 0;
		i++;
	}
	if (result == 1)
	{
		free((*tmp_lst)->args);
		(*tmp_lst)->args = ft_strdup(str);
		(*tmp_lst)->exe_function = support.exe_func_arr[7];
		*decrement -= 1;
	}
	free_2d_arr(splited_str);
}

static	void	init_exec_func(t_exe_info **exe_info,
								t_support_parsing_data support, char **args, int *i)
{
	int				j;
	t_exe_info		*tmp_lst;
	char			*str_to_compare;
	int				state_env;

	state_env = 0;
	tmp_lst = *exe_info;
	str_to_compare = get_str_to_compare(args, i, &state_env);
	j = 0;
	while (j < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(str_to_compare, support.exe_str_arr[j]))
			tmp_lst->exe_function = support.exe_func_arr[j];
		j++;
	}
	init_redirection(&tmp_lst, support, i, str_to_compare);
	if (!tmp_lst->exe_function && state_env == 4)
		init_exe_env(&tmp_lst, support, i, str_to_compare);
	free(str_to_compare);
}

static	int	init_operator(t_exe_info **tmp_lst, int *increm,
								t_support_parsing_data support, char *arg)
{
	int		i;

	i = 0;
	while (i < sizeof(support.operators_arr) / sizeof(char *))
	{
		if (!ft_strcmp(arg, support.operators_arr[i]))
		{
			if (!((*tmp_lst)->next = (t_exe_info *)malloc(sizeof(t_exe_info))))
				return (0);
			(*tmp_lst) = (*tmp_lst)->next;
			set_default_new_lst(tmp_lst);
			(*tmp_lst)->operator_exe_function = support.operators_exe_func_arr[i];
			*increm += 1;
			return (1);
		}
		i++;
	}
	return (-1);
}

int	get_exe_info(char **args, t_store *store)
{
	t_exe_info	*tmp_lst;
	int			i;

	i = 0;
	if (!(store->exe_info = (t_exe_info *)malloc(sizeof(t_exe_info))))
		return (0);
	set_default_new_lst(&store->exe_info);
	tmp_lst = store->exe_info;
	while (args[i])
	{
		init_exec_func(&tmp_lst, store->support, args, &i);
		while (args[i])
		{
			if (!args[++i]
				 || (init_operator(&tmp_lst, &i, store->support, args[i])) > 0)
				break ;
			else
				concat_arg(&tmp_lst, args[i]);
		}
		if (!args[i])
			break ;
		i++;
	}
	return (1);
}
