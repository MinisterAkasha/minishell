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

//check string ""
static	char *cut_seporator(char *arg, char separator)
{
	int		i;
	int		len;
	char	*first;
	char	*second;
	int		start_index;

	i = 0;
	len = 0;
	first = 0;
	second = 0;
	if (separator == arg[0])
		i++;
	start_index = i;
	while (arg[i] != separator && arg[i])
	{
		len++;
		i++;
	}
	first = ft_substr(arg, start_index, len);
	len = -1;
	i++;
	start_index = i;
	while(arg[i])
	{
		len++;
		i++;
	}
	second = ft_substr(arg, start_index, len);
	return (ft_strjoin(first, second));
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
		ft_putendl_fd("Cutted str:", 1);
		ft_putendl_fd(cut_seporator(arg, separator), 1);
		copy_exe_info->arg = ft_strjoin(copy_exe_arg, cut_seporator(arg, separator));
	}
	free(copy_exe_arg);
	//clean ' " in str
	//concatenate with str
}

static	int init_exec_func(t_exe_info	**exe_info, t_support_parsing_data support, char *arg)
{
	int				i;
	char	*str;
	t_exe_info	*copy_exe_info;

	copy_exe_info = *exe_info;
	str = cut_seporator(arg, get_separator(arg));
	i = 0;
	while (i < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(str, support.exe_str_arr[i]))
		{
			ft_putstr_fd("\nThe added func -> : ", 1);
			ft_putendl_fd(support.exe_str_arr[i], 1);
			copy_exe_info->exe_function = support.exe_func_arr[i];
		}
		i++;
	}
	free(str);
	if (!copy_exe_info->exe_function)
		return (0);
	return 1;
}

static	int init_oper_exec_func(t_exe_info	**exe_info, t_support_parsing_data support, char *arg)
{
	int		i;
	t_exe_info	*copy_exe_info;

	copy_exe_info = *exe_info;
	i = 0;
	while (i < sizeof(support.operators_arr) / sizeof(char *))
	{
		if (!ft_strcmp(arg, support.operators_arr[i]))
			return (i);
		i++;
	}
//	if (!copy_exe_info->operator_exe_function)
//		return (-1);
	return (-2);
}

void		get_exe_info(char **args, t_store *store, t_exe_info **exe_info)
{
	t_exe_info	*copy_exe_info;
	size_t		i;
	int			index_oper;

	i = 0;
	copy_exe_info = *exe_info;
	while(args[i])
	{
		ft_putstr_fd("i : ", 1);
		ft_putnbr_fd(i,1);
		ft_putendl_fd("", 1);
		ft_putstr_fd("args[i] ", 1);
		ft_putendl_fd(args[i], 1);
		index_oper = -1;
		if (!init_exec_func(&copy_exe_info, store->support, args[i]))
			copy_exe_info->exe_function = NULL;
		while(args[i] && index_oper < 0)
		{
			i++;
			if (!args[i])
			{
				ft_putstr_fd("Аргумент: ", 1);
				ft_putendl_fd(copy_exe_info->arg, 1);
				break ;
			}
			if ((index_oper = init_oper_exec_func(&copy_exe_info, store->support, args[i])) >= 0)//TODO -1 or -2
			{
				ft_putstr_fd("Аргумент: ", 1);
				ft_putendl_fd(copy_exe_info->arg, 1);
				if (!(copy_exe_info->next = (t_exe_info *)malloc(sizeof(t_exe_info))))
					return ;
				copy_exe_info = copy_exe_info->next;
				copy_exe_info->next = NULL;
				copy_exe_info->exe_function = NULL;
				copy_exe_info->operator_exe_function = NULL;
				copy_exe_info->arg = ft_strdup("");
				ft_putstr_fd("The operator for next command: ", 1);
				ft_putendl_fd(args[i], 1);
				copy_exe_info->operator_exe_function = store->support.operators_exe_func_arr[index_oper];
				i++;
			}
			else
				concat_arg(&copy_exe_info, args[i]);
		}
		i++;
	}
}

int main()
{
	t_exe_info *test;
	t_exe_info *fucking_test;
	char *str = "  echo 111'111' | cd papka > echo \"222\"222 >> 'echo' \"333333\" ;    echo '' |  echo 444444 ";
	char **splited_str;
	t_store *store;

	store = (t_store *)malloc(sizeof(t_store));
	init_support_parsing_arr(&store->support);
	splited_str = split(str);

	store->exe_info = (t_exe_info *)malloc(sizeof (t_exe_info));
	store->exe_info->next = NULL;
	store->exe_info->exe_function = NULL;
	store->exe_info->operator_exe_function = NULL;
	store->exe_info->arg = ft_strdup("");
	get_exe_info(splited_str, store, &store->exe_info);

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