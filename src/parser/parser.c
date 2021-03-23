/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:05:53 by akasha            #+#    #+#             */
/*   Updated: 2021/03/23 14:59:04 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_create_env(t_exe_args *exe_args)
{
	return (1);
}


static	int		init_redirection(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	if ((*tmp_lst)->operator_exe_function != NULL
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[0]
		 && (*tmp_lst)->operator_exe_function != support.operators_exe_func_arr[1])
	{
		(*tmp_lst)->exe_function = NULL;
		return (1);
	}
	else if (!(*tmp_lst)->exe_function)
		return (1);
	return (0);
}

static	void	init_exec_func(t_exe_info **exe_info,
								t_support_parsing_data support, char **args, int *i)
{
	int				j;
	t_exe_info		*tmp_lst;
	char			*str_to_compare;

	tmp_lst = *exe_info;
	if (args[*i] && !ft_strcmp(args[*i], " "))
		*i += 1;
	str_to_compare = get_str_to_compare(args, i);
	j = 0;
	while (j < sizeof(support.exe_str_arr) / sizeof(char *))
	{
		if (!ft_strcmp(str_to_compare, support.exe_str_arr[j]))
			tmp_lst->exe_function = support.exe_func_arr[j];
		j++;
	}
	if (init_redirection(&tmp_lst, support, i, str_to_compare))
		init_arg(&tmp_lst, str_to_compare, i);
	else if (args[*i] && !ft_strcmp(args[*i], " "))
		*i += 1;
	free(str_to_compare);
}

static	int	init_operator(t_exe_info **tmp_lst, int i,
								t_support_parsing_data support, char **args)
{
	int		j;

	j = 0;
	while (j < sizeof(support.operators_arr) / sizeof(char *))
	{
		if (!ft_strcmp(args[i], support.operators_arr[j]))
		{
			(*tmp_lst)->operator_exe_function = support.operators_exe_func_arr[j];
			if (!args[i + 1])
				return (0);
			if (!((*tmp_lst)->next = (t_exe_info *)malloc(sizeof(t_exe_info))))
				error_malloc();
			(*tmp_lst) = (*tmp_lst)->next;
			set_default_new_lst(tmp_lst);
			return (0);
		}
		j++;
	}
	return (1);
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
		while (args[i] && init_operator(&tmp_lst, i, store->support, args))
		{
			concat_arg(&tmp_lst, store->support, args[i]);
			i++;
		}
		if (!args[i])
			break ;
		i++;
	}
	return (1);
}

//int main()
//{
//	char *str = "echo ch'l'en;bin;ls ;'e'c'h'o pam> ty't'y ;e'ch'o 111'111'| cd papka ; echo \"222\"222 >> 'echo' \"333333\" ;    echo    '' | echo 44'44'44 ; echo some_word > test.txt test test ; echo next_word > extra_test.txt extra extra ";
//	t_exe_info *test;
//	t_exe_info *fucking_test;
//	//"name= fsd" -> OK
//	//"na'me'=fasdf" -> OK
//	//"name'='dsaf" -> OK
//	//"'na'me=fasdf" -> OK
//	//"name==kklkf" -> OK
//	//"name===fdsa" -> OK
//	//"na'm'e=test" -> OK
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