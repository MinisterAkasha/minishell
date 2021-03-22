/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/20 21:25:19 by akasha           ###   ########.fr       */
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

static	void	init_redirection(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	if ((*tmp_lst)->operator_exe_function != NULL
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[0]
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[1])
	{
		(*tmp_lst)->exe_function = NULL;
		init_arg(tmp_lst, str, decrement);
	}
	else if (!(*tmp_lst)->exe_function)
		init_arg(tmp_lst, str, decrement);
	return ;
}

static	void	init_exe_env(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	char	**splited_str;
	int		result;
	int		i;

	result = 1;
	i = 0;
	splited_str = protect_ft_split(ft_split(str, '='));
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
		(*tmp_lst)->exe_function = support.exe_func_arr[7];
		init_arg(tmp_lst, str, decrement);
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
//	if (!tmp_lst->exe_function && state_env == 4)
//		init_exe_env(&tmp_lst, support, i, str_to_compare);
//	if (!tmp_lst->exe_function)
//	{
//		init_arg(&tmp_lst, str_to_compare, i);
//	}
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
		error_malloc();
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
				concat_arg(&tmp_lst, store->support, args[i]);
		}
		if (!args[i])
			break ;
		i++;
	}
	return (1);
}

//int main()
//{
//	t_exe_info *test;
//	t_exe_info *fucking_test;
//	//"name= fsd" -> OK
//	//"na'me'=fasdf" -> OK
//	//"name'='dsaf" -> OK
//	//"'na'me=fasdf" -> OK
//	//"name==kklkf" -> OK
//	//"name===fdsa" -> OK
//	//"na'm'e=test" -> OK
//	char *str = "echo ch'l'en ; bin ; ls ; 'e'c'h'o pam > ty't'y ; e'ch'o 111'111' | cd papka ; echo \"222\"222 >> 'echo' \"333333\" ;    echo    '' | echo 44'44'44 ; echo some_word > test.txt test test ; echo next_word > extra_test.txt extra extra ";
//	//char *str = "name==kklkf ; name=fasdf'fasdf' ; name='fdsa'sfda ;  name=ppp'fds'=mmmm";
////	char *str = "  ";
//	char **splited_str;
//	t_store *store;
//	int i;
//
//	i = 0;
//	if (!(store = (t_store *) malloc(sizeof(t_store))))
//		return (0);
//	init_support_parsing_arr(&store->support);
//	splited_str = split(str);
//	if (!(get_exe_info(splited_str, store)))
//		return (0);
//
////      while (1)
////      {
////
////      }
//	while (store->exe_info)
//	{
//		printf("\n====$$$$====\n");
//		printf("store->exe_info->arg: %s\n", store->exe_info->args);
//		printf("store->exe_info->exe_function: %p\n",
//			   store->exe_info->exe_function);
//		printf("store->exe_info->operator_exe_function: %p\n",
//			   store->exe_info->operator_exe_function);
//		printf("\n");
//		store->exe_info = store->exe_info->next;
//	}
//	return (0);
//}