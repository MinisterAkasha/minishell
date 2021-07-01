#include "minishell.h"

static	int		skip_spaces(char *str, char separator, int i)
{
	if (!str[i])
		return (i);
	if ((str[i] == ' ' && separator == 'f'))
	{
		while (str[i] == ' ' && str[i])
			i++;
	}
	else
		i++;
	return (i);
}

/*
** Create a linked list 'head'
** Which has data to cut the 'str' by quotes and spaces
** Structure of the linked:
** start_index -> len -> start_index -> len -> ...
*/

static void		word_count(char *str, t_list **head)
{
	int			i;
	char		sep;
	int			*info_arr;

	i = 0;
	init_data_word_count(&sep, &info_arr, head);
	while (str[i])
	{
		info_arr[1]++;
		if (sep == 'f' && (str[i] == '"' || str[i] == '\''))
			sep = str[i];
		else if ((sep == 'f' && str[i] == '>' && str[i + 1] == '>'))
		{
			info_arr[1]++;
			i++;
			init_data_word_count(&sep, &info_arr, head);
		}
		else if ((sep == 'f' && str[i] == '\\'))
			init_escape_symbol(&sep, &info_arr, head, &i);
		else if (is_word_to_cont(str, sep, i))
			init_data_word_count(&sep, &info_arr, head);
		i = skip_spaces(str, sep, i);
		if (info_arr[1] == 0)
			info_arr[0] = i;
	}
}

char			**init_arr_2d(char *str, t_list *copy_dw)
{
	int			i;
	int			len_arr;
	char		**arr_2d;
	int			*info_arr;

	len_arr = ft_lstsize(copy_dw) - 1;
	arr_2d = (char **)ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		info_arr = copy_dw->content;
		arr_2d[i] = ft_substr(str, info_arr[0], info_arr[1]);
		copy_dw = copy_dw->next;
		i++;
	}
	return (arr_2d);
}

char			**split(char const *s)
{
	t_list	*data_words;
	t_list	*copy_data_words;
	char	**arr_2d;
	char	*str;

	str = ft_strtrim(s, " ");
	data_words = NULL;
	word_count(str, &data_words);
	copy_data_words = data_words;
	arr_2d = init_arr_2d(str, copy_data_words);
	ft_lstclear(&data_words, &del_item_libft_lst);
	free(str);
	return (arr_2d);
}
