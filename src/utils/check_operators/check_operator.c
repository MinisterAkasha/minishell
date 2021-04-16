/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:41:24 by akasha            #+#    #+#             */
/*   Updated: 2021/04/16 19:10:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_and_write_error(char *token, t_exe_args *exec_args)
{
	char	*error_str;

	error_str = triple_str_join("syntax error near unexpected token `", token, "'");
	write_error("minihsell", "",error_str);
	free(error_str);
	add_variable(&exec_args->variables, create_var("?", "258", 0, 0));
}

int	compare_with_redirect(char c)
{
	char	*char_str;
	int		i;

	i = 0;
	if (c == '>' || c == '<')
		i = 1;
	return (i);
}

int	compare_with_non_redirect(char c)
{
	char	*char_str;
	int		i;

	i = 0;
	if (c == '|' || c == ';')
		i = 1;
	return (i);
}

int	find_closest_redirect_index(char *input, int end)
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

int	check_spaces_between(char *input, int end, int start)
{
	char	*sub_str;
	int		i;
	int		redirect_index;

	i = 0;
	if (end == start)
		start = 0;
	if (input[end + 1] == input[end] && end != start)
		end++;
	redirect_index = find_closest_redirect_index(input, end);
	if (redirect_index != -1 && input[end] != input[start])
		start = redirect_index;
	sub_str = ft_substr(input, start + 1, end - (start + 1));
	while (sub_str[i])
	{
		if (sub_str[i] == ' ')
			i++;
		else
		{
			free(sub_str);
			return (0);
		}
	}
	free(sub_str);
	return (1);
}

int		find_index_prev_semicolon(char *input, int current_index)
{
	int	prev_index;
	int	i;

	i = current_index - 1;
	while (i >= 0)
	{
		if (input[i] == ';')
			return(i);
		i--;
	}
	return (i);
}

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
			if (!check_spaces_between(input, start, find_index_prev_semicolon(input, start)))
				return ("|");
			return (";");
		}
		else if (input[end] == ';' && input[start] == '|')
			return ("|");
	}
	return ("");
}

int	make_currect_error(int i, int j, char *input, t_exe_args *exe_args)
{
	if (i == j + 1)
		create_and_write_error(get_double_token(input, i, j), exe_args);
	else if (input[i] == '|')
		create_and_write_error("|", exe_args);
	else if (input[i] == ';')
		create_and_write_error(";", exe_args);
	return (0);
}

int	check_input_without_redirect(char *input, t_exe_args *exe_args)
{
	char	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (compare_with_non_redirect(input[i]))
		{
			if (j == -1 && ft_strcmp(ft_strchr(input, input[i]), ft_strrchr(input, input[i])))
				j = i;
			else if (check_spaces_between(input, i, j))
				return (make_currect_error(i, j, input, exe_args));
			else
				j = i;
		}
		i++;
	}
	return (1);
}

int	check_input_with_redirect(char *input, t_exe_args *exe_args)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i - 1] != '>' && input[i + 1] == '|'
			&& input[i + 2] == '|' && input[i + 3] == '|')
		{
			create_and_write_error("||", exe_args);
			return (0);
		}
		else if (input[i] == '>' && input[i - 1] != '>'
			&& input[i + 1] == '|' && input[i + 2] == '|')
		{
			create_and_write_error("|", exe_args);
			return (0);
		}
		else if (input[i] == '>' && input[i - 1] != '>' && input[i + 1] == '|')
		{
			create_and_write_error("newline", exe_args);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_valid_operator(char *input, t_exe_args *exe_args)
{
	if (!check_input_with_redirect(input, exe_args))
		return (0);
	if (!check_input_without_redirect(input, exe_args))
		return (0);
	return (1);
}
