#include "minishell.h"

int		is_word_to_cont(char *str, char sep, int i)
{
	int		cur_operands;
	int		next_operands;
	int		is_separator;
	int		is_space;

	is_separator = (str[i] == '"' || str[i] == '\'') && i != 0
				&& !(str[i] == '"' && str[i - 1] == '\\');
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

int		init_data_word_count(char *sep, int **info_arr, t_list **head)
{
	(*info_arr) = (int *)ft_calloc(2, sizeof(int));
	*sep = 'f';
	ft_lstadd_back(head, ft_lstnew(*info_arr));
	return (1);
}

void	init_escape_symbol(char *sep, int **info_arr, t_list **head, int *i)
{
	(*info_arr)[1] -= 1;
	init_data_word_count(sep, info_arr, head);
	(*info_arr)[1] = 2;
	(*info_arr)[0] = *i;
	init_data_word_count(sep, info_arr, head);
	*i += 1;
}
