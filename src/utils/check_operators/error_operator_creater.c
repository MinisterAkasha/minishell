/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_operator_creater.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:18:14 by akasha            #+#    #+#             */
/*   Updated: 2021/04/16 19:18:39 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_double_token(char *input, int end, int start)
{
	if (input[end] == input[start])
	{
		if (input[end] == '|')
			return ("||");
		else if (input[end] == ';')
			return (";;");
	}
	else
	{
		if (input[end] == '|' && input[start] == ';')
		{
			if (!check_spaces_between(input, start,
				find_index_prev_semicolon(input, start)))
				return ("|");
			return (";");
		}
		else if (input[end] == ';' && input[start] == '|')
			return ("|");
	}
	return ("");
}

int		make_currect_error(int i, int j, char *input, t_exe_args *exe_args)
{
	if (i == j + 1)
		create_and_write_error(get_double_token(input, i, j), exe_args);
	else if (input[i] == '|')
		create_and_write_error("|", exe_args);
	else if (input[i] == ';')
		create_and_write_error(";", exe_args);
	return (0);
}
