/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:50:17 by tilda             #+#    #+#             */
/*   Updated: 2021/04/05 15:50:19 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*curly_brackets(char *arr_str, int *i)
{
	int		start;
	char	*str_dollar;

	*i += 1;
	start = *i;
	while(arr_str[*i] && arr_str[*i] != '}')
		*i += 1;
	str_dollar = ft_substr(arr_str, start, *i - start);
	if (arr_str[*i] == '}')
		*i += 1;
	return (str_dollar);
}

char			*get_str_dollar(t_exe_args exe_args, char *arr_str, int *i)
{
	char	*str_dollar;
	char	*env;
	int		start;

	*i += 1;
	start = *i;
	if (arr_str[*i] && arr_str[*i] == '?')
	{
		str_dollar = ft_strdup("?");
		*i += 1;
	}
	else if (arr_str[*i] && arr_str[*i] == '{')
		str_dollar = curly_brackets(arr_str, i);
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

char			*get_tail(char *arr_str, int *i)
{
	int		start;
	char	*tail_str;

	if (arr_str[*i] && arr_str[*i] != '$')
	{
		start = *i;
		while (arr_str[*i] && arr_str[*i] != '$')
			*i += 1;
		tail_str = ft_substr(arr_str, start, *i - start);
	}
	else
		tail_str = ft_strdup("");
	return (tail_str);
}
