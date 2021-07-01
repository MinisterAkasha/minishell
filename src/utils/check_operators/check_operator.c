#include "minishell.h"

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
			if (j == -1 && ft_strcmp(ft_strchr(input, input[i]),
				ft_strrchr(input, input[i])))
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
