/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:30:17 by tilda             #+#    #+#             */
/*   Updated: 2021/03/18 15:55:22 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//void			dollar_sign(char **arg, t_exe_args exe_args)
//{
//	char	*tmp_str;
//	char	*env;
//	char	*str_dollar;
//	char	*third_part;
//	char	*first_part;
//	int		i;
//	int		j;
//	t_variable *tmp;
//
//	ft_putendl_fd("Default_str", 1);
//	ft_putendl_fd(*arg, 1);
//	tmp_str = 0;
//	i = 0;
//	j = 0;
//	while ((*arg)[j] && (*arg)[j] != '$')
//		j++;
//	first_part = protect_malloc(ft_substr((*arg), 0, j));
//	if ((str_dollar = ft_strchr((*arg), '$')))
//	{
//		str_dollar++;
//		while (str_dollar[i] && str_dollar[i] != '"' && str_dollar[i] != ' ' && str_dollar[i] != '$')
//			i++;
//		tmp_str = protect_malloc(ft_substr(str_dollar, 0, i));
//		third_part = protect_malloc(ft_strdup(str_dollar + i));
//		if (!(str_dollar = get_env_param(tmp_str, exe_args.env)))
//		{
//			tmp = find_variable(exe_args.variables, tmp_str);
//			if (tmp)
//				str_dollar = tmp->value;
//		}
//		if (!str_dollar)
//			str_dollar = protect_malloc(ft_strdup(""));
//		env = protect_malloc(ft_strdup(str_dollar));
//		tmp_str = protect_malloc(ft_strjoin(env, third_part));
//		(*arg) = ft_strjoin(first_part, tmp_str);
//	}
//	ft_putendl_fd("After change $", 1);
//	ft_putendl_fd(*arg, 1);
//	ft_putendl_fd("", 1);
//	free(first_part);
//}

char			*get_str_to_compare(char **args, t_exe_args exe_args, int *i)
{
	char			*str_to_compare;

	str_to_compare = protect_malloc(ft_strdup(""));
	while (args[*i] && ft_strcmp(args[*i], " ")
			&& ft_strcmp(args[*i], "|")
			&& ft_strcmp(args[*i], ";")
			&& ft_strcmp(args[*i], ">")
			&& ft_strcmp(args[*i], "<")
			&& ft_strcmp(args[*i], ">>"))
	{
		concat_exe_arg(exe_args, &str_to_compare, args[*i]);
		*i += 1;
	}
	return (str_to_compare);
}

void			set_default_new_lst(t_exe_info **lst)
{
	(*lst)->next = NULL;
	(*lst)->exe_function = NULL;
	(*lst)->operator_exe_function = NULL;
	(*lst)->args = protect_malloc(ft_strdup(""));
}

void			init_arg(t_exe_info **tmp_lst, char *str)
{
	free((*tmp_lst)->args);
	(*tmp_lst)->args = protect_malloc(ft_strdup(str));
}

int				is_word_to_cont(char *str, char sep, int i)
{
	int		cur_operands;
	int		next_operands;
	int		is_separator;
	int		is_space;

	is_separator = (str[i] == '"' || str[i] == '\'');
	next_operands = (str[i + 1] == ';' || str[i + 1] == '|' ||
						str[i + 1] == '>' || str[i + 1] == '<');
	cur_operands = (str[i] == ';' || str[i] == '|' ||
						str[i] == '>' || str[i] == '<');
	is_space = ((str[i] == ' ' && sep == 'f') ||
				(str[i + 1] == ' ' && sep == 'f'));

	if (str[i + 1] == '\0' || is_space
		|| (sep == str[i] && is_separator)
		|| (sep == 'f' && next_operands)
		|| (sep == 'f' && cur_operands))
	{
		return (1);
	}
	return (0);
}