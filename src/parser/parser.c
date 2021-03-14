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

int			exe_pwd(char **args, char **env)
{
	char path[100];

	//TODO обработать ошибки
	ft_putendl_fd(getcwd(path, 100), 1);
	return (1);
}
int			exe_echo(char **args, char **env)
{
	write(1, "echo\n", 5);
	return (1);
}
int			exe_export(char **args, char **env)
{
	write(1, "export\n", 7);
	return (1);
}
int			exe_unset(char **args, char **env)
{
	write(1, "unset\n", 6);
	return (1);
}
int			exe_env(char **args, char **env)
{
	write(1, "env\n", 4);
	return (1);
}
int			exe_exit(char **args, char **env)
{
	exit(1);
	write(1, "exit\n", 5);
	return (1);
}

int			unknown_command(char **args, char **env)
{
	write_error_message("minishell: ", args[0], ": command not found");
	return (1);
}

static	char get_separator(char *arg)
{
	int		i;
	char	separator;

	i = 0;
	separator = 'f';
	while(arg[i] && separator == 'f')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			separator = arg[i];
		i++;
	}
	return (separator);
}

static	void cut_separator(char **arg, char separator)
{
	int		i;
	int		len;
	char	*first;
	char	*second;
	int		start_index;

	i = 0;
	first = 0;
	if (separator == (*arg)[0])
		i++;
	while (1)
	{
		len = 0;
		start_index = i;
		while ((*arg)[i] != separator && (*arg)[i++])
			len++;
		if (first != 0)
			break;
		first = ft_substr((*arg), start_index, len);
		i++;
	}
	second = ft_substr((*arg), start_index, len);
	free((*arg));
	(*arg) = ft_strjoin(first, second);
	free(first);
	free(second);
}

static	void concat_arg(t_exe_info	**exe_info, char *arg)
{
	char	separator;
	char	*copy_exe_arg;
	t_exe_info	*copy_exe_info;

	copy_exe_info = *exe_info;
	separator = get_separator(arg);
	copy_exe_arg = ft_strdup(copy_exe_info->arg);
	free(copy_exe_info->arg);
	if (separator == 'f')
		copy_exe_info->arg = ft_strjoin(copy_exe_arg, arg); // check if first arg is "" or NULL
	else
	{
		cut_separator(&arg, separator);
		copy_exe_info->arg = ft_strjoin(copy_exe_arg, arg);
	}
	free(arg);
	free(copy_exe_arg);
}

static	int init_exec_func(t_exe_info	**exe_info, t_support_parsing_data support, char *arg)
{
	int				i;
	char	*str;
	t_exe_info	*copy_exe_info;

	copy_exe_info = *exe_info;
	cut_separator(&arg, get_separator(arg));
	i = 0;
	while (i < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(arg, support.exe_str_arr[i]))
			copy_exe_info->exe_function = support.exe_func_arr[i];
		i++;
	}
	free(arg);
	if (!copy_exe_info->exe_function)
		return (0);
	return (1);
}

static	void	create_new_list(t_exe_info **lst)
{
	(*lst)->next = NULL;
	(*lst)->exe_function = NULL;
	(*lst)->operator_exe_function = NULL;
	(*lst)->arg = ft_strdup("");
}

static	int init_oper_exec_func(t_exe_info **copy_exe_info, t_support_parsing_data support, char *arg)
{
	int		i;

	i = 0;
	while (i < sizeof(support.operators_arr) / sizeof(char *))
	{
		if (!ft_strcmp(arg, support.operators_arr[i]))
		{
			if (!((*copy_exe_info)->next = (t_exe_info *)malloc(sizeof(t_exe_info))))
				return (0);
			(*copy_exe_info) = (*copy_exe_info)->next;
			create_new_list(copy_exe_info);
			(*copy_exe_info)->operator_exe_function = support.operators_exe_func_arr[i];
			return (i);
		}
		i++;
	}
	return (-1);
}

int		get_exe_info(char **args, t_store *store)
{
	t_exe_info	*copy_exe_info;
	size_t		i;
	int			index_oper;

	i = 0;
	if (!(store->exe_info = (t_exe_info *)malloc(sizeof (t_exe_info))))
		return (0);
	create_new_list(&store->exe_info);
	copy_exe_info = store->exe_info;
	while(args[i])
	{
		index_oper = -1;
		init_exec_func(&copy_exe_info, store->support, args[i]);
		while(args[i])
		{
			i++;
			if (!args[i])
				break ;
			if ((index_oper = init_oper_exec_func(&copy_exe_info, store->support, args[i])) >= 0)
			{
				i++;
				break ;
			}
			else
				concat_arg(&copy_exe_info, args[i]);
		}
		i++;
	}
	return (1);
}

int main()
{
	t_exe_info *test;
	t_exe_info *fucking_test;
	char *str = "  echo 111'111' | cd papka > echo \"222\"222 >> 'echo' \"333333\" ;    echo    '' |  echo 444444";
	char **splited_str;
	t_store *store;

	if (!(store = (t_store *)malloc(sizeof(t_store))))
		return (0);
	init_support_parsing_arr(&store->support);
	splited_str = split(str);
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



















//
//t_exe_info	parser(char **args, t_support_parsing_data support)
//{
//	t_exe_info		info;
//	int				i;
//
//	i = 0;
//	info.exe_function = NULL;
//	info.operator_exe_function = NULL;
//	info.args = args;
//	while (i < sizeof(support.exe_str_arr) / sizeof(char *))
//	{
//		if (!ft_strcmp(args[0], support.exe_str_arr[i]))
//			info.exe_function = support.exe_func_arr[i];
//		i++;
//	}
//	if (!info.exe_function)
//		info.exe_function = unknown_command;
//	info.oper = "";
//	return (info);
//}