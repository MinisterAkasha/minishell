/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:51:44 by tilda             #+#    #+#             */
/*   Updated: 2021/03/18 15:56:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static	int		init_data_word_count(char *sep, int **info_arr, t_list **head)
{
	(*info_arr) = (int *)ft_calloc(2, sizeof(int));
	*sep = 'f';
	ft_lstadd_back(head, ft_lstnew(*info_arr));
	return (1);
}

/*
** Create a linked list 'head'
** Which has data to cut the 'str' by quotes and spaces
** Structure of the linked:
** start_index -> len -> start_index -> len -> ...
*/

static	int		word_count(char *str, t_list **head)
{
	int			i;
	char		sep;
	int			*info_arr;

	i = 0;
	init_data_word_count(&sep, &info_arr, head);
	while (str[i])
	{
		info_arr[1]++;
		if (sep == 'f' && (str[i] == '"' || str[i] == '\'' || str[i] == '\\'))
			sep = str[i];
		else if (sep == 'f' && str[i] == '>' && str[i + 1] == '>')
		{
			info_arr[1]++;
			i++;
			init_data_word_count(&sep, &info_arr, head);
		}
		else if (is_word_to_cont(str, sep, i))
			init_data_word_count(&sep, &info_arr, head);
		i = skip_spaces(str, sep, i);
		if (info_arr[1] == 0)
			info_arr[0] = i;
	}
	return (1);
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
//
//int main()
//{
//      char *str = " echo \\> 213 ; echo \\\\fads ; echo \\$; echo ch'l'en;bin;ls ;'e'c'h'o pam> ty't'y ;e'ch'o 111'111'| cd papka ; echo \"222\"222 >> 'echo' \"333333\" ;    echo    '' | echo 44'44'44 ; echo some_word > test.txt test test ; echo next_word > extra_test.txt extra extra ";
//      char **splited_str;
//      int i;
//
//      i = 0;
//      splited_str = split(str);
//      while (splited_str[i])
//      {
//              ft_putnbr_fd(i, 1);
//              ft_putchar_fd(')', 1);
//              ft_putendl_fd(splited_str[i], 1);
//              i++;
//      }
//      return (0);
//}
