/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:14:49 by akasha            #+#    #+#             */
/*   Updated: 2021/04/16 19:18:48 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		compare_with_redirect(char c)
{
	char	*char_str;
	int		i;

	i = 0;
	if (c == '>' || c == '<')
		i = 1;
	return (i);
}

int		compare_with_non_redirect(char c)
{
	char	*char_str;
	int		i;

	i = 0;
	if (c == '|' || c == ';')
		i = 1;
	return (i);
}

int		find_closest_redirect_index(char *input, int end)
{
	int i;

	i = end;
	while (i >= 0)
	{
		if (input[i] == '>' || input[i] == '<')
			return (i);
		i--;
	}
	return (-1);
}

int		find_index_prev_semicolon(char *input, int current_index)
{
	int	prev_index;
	int	i;

	i = current_index - 1;
	while (i >= 0)
	{
		if (input[i] == ';')
			return (i);
		i--;
	}
	return (i);
}

void	create_and_write_error(char *token, t_exe_args *exec_args)
{
	char	*err;

	err = triple_str_join("syntax error near unexpected token `", token, "'");
	write_error("minihsell", "", err);
	free(err);
	add_variable(&exec_args->variables, create_var("?", "258", 0, 0));
}
