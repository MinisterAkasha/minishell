/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 21:44:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int			exe_export(t_exe_args *exe_args)
{
	write(1, "export\n", 7);
	return (1);
}
int			exe_unset(t_exe_args *exe_args)
{
	write(1, "unset\n", 6);
	return (1);
}
//int			exe_env(t_exe_args *exe_args)
//{
//	write(1, "env\n", 4);
//	return (1);
//}
int			exe_exit(t_exe_args *exe_args)
{
	exit(1);
	write(1, "exit\n", 5);
	return (1);
}

int			unknown_command(t_exe_args *exe_args)
{
	write_error_message("minishell: ", exe_args->args[0], ": command not found");
	return (1);
}
static	char	*get_str_to_compare(char **args, int *i)
{
	char			*str_to_compare;

	str_to_compare = ft_strdup("");
	while (args[*i] && ft_strcmp(args[*i], " "))
	{
		concat_exe_arg(&str_to_compare,  args[*i]);
		*i += 1;
	}
	return (str_to_compare);
}


static	void	init_exec_func(t_exe_info **exe_info,
								t_support_parsing_data support, char **args, int *i)
{
	int				j;
	t_exe_info		*tmp_lst;
	char			*str_to_compare;

	tmp_lst = *exe_info;
	str_to_compare = get_str_to_compare(args, i);
	j = 0;
	while (j < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(str_to_compare, support.exe_str_arr[j]))
			tmp_lst->exe_function = support.exe_func_arr[j];
		j++;
	}
	if (tmp_lst->operator_exe_function != NULL &&
		tmp_lst->operator_exe_function != support.operators_exe_func_arr[0] &&
		tmp_lst->operator_exe_function != support.operators_exe_func_arr[1])
	{
		tmp_lst->exe_function = NULL;
		free(tmp_lst->arg);
		tmp_lst->arg = ft_strdup(str_to_compare);
		*i -= 1;
	}
	free(str_to_compare);
}

static	void	set_default_new_lst(t_exe_info **lst)
{
	(*lst)->next = NULL;
	(*lst)->exe_function = NULL;
	(*lst)->operator_exe_function = NULL;
	(*lst)->arg = ft_strdup("");
}

static	int		init_operator(t_exe_info **tmp_lst, int *increm,
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

int				get_exe_info(char **args, t_store *store)
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
			if (!args[++i] ||
				(init_operator(&tmp_lst, &i, store->support, args[i])) > 0)
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

int main()
{
	t_exe_info *test;
	t_exe_info *fucking_test;
	char *str = "'e'c'h'o pam > tyty ; e'ch'o 111'111' | cd papka ; echo \"222\"222 >> 'echo' \"333333\" ;    echo    '' | echo 44'44'44 ; echo some_word > test.txt test test ; echo next_word > extra_test.txt extra extra";
	char **splited_str;
	t_store *store;
	int i;

	i = 0;
	if (!(store = (t_store *)malloc(sizeof(t_store))))
		return (0);
	init_support_parsing_arr(&store->support);
	splited_str = split(str);
//	while (splited_str[i])
//	{
//		ft_putnbr_fd(i, 1);
//		ft_putchar_fd(')', 1);
//		ft_putendl_fd(splited_str[i], 1);
//		i++;
//	}
	if (!(get_exe_info(splited_str, store)))
		return (0);

//	while (1)
//	{
//
//	}
	while(store->exe_info)
	{
		printf("\n====$$$$====\n");
		printf("store->exe_info->arg: %s\n",store->exe_info->arg);
		printf("store->exe_info->exe_function: %p\n",store->exe_info->exe_function);
		printf("store->exe_info->operator_exe_function: %p\n",store->exe_info->operator_exe_function);
		printf("\n");
		store->exe_info = store->exe_info->next;
	}
	return (0);
}