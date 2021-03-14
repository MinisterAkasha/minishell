/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:51:44 by tilda             #+#    #+#             */
/*   Updated: 2021/03/10 12:51:45 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		skip_spaces(char *str, char separator, int i)
{
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
	if (!(*info_arr = (int *)ft_calloc(2, sizeof(int))))
		return (0);
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

static	int		word_count(char **str, t_list **head)
{
	int			i;
	char		sep;
	int			*info_arr;

	i = 0;
	if (!(init_data_word_count(&sep, &info_arr, head)))
		return (0);
	while ((*str)[i])
	{
		info_arr[1]++;
		if (sep == 'f' && ((*str)[i] == '"' || (*str)[i] == '\''))
			sep = (*str)[i];
		else if (((*str)[i] == ' ' && sep == 'f') || (*str)[i + 1] == '\0' ||
			((*str)[i + 1] == ' ' && sep == 'f') || sep == (*str)[i])
		{
			if (!(init_data_word_count(&sep, &info_arr, head)))
				return (0);
		}
		i = skip_spaces((*str), sep, i);
		if (info_arr[1] == 0)
			info_arr[0] = i;
	}
	return (1);
}

static	char	**init_arr_2d(char *str, t_list *copy_dw)
{
	int			i;
	int			len_arr;
	char		**arr_2d;
	int			*info_arr;

	len_arr = ft_lstsize(copy_dw) - 1;
	if (!(arr_2d = (char **)ft_calloc(len_arr + 1, sizeof(char *))))
		return (0);
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

void			del(void *value)
{
	free(value);
	value = NULL;
}

char			**split(char const *s)
{
	t_list	*data_words;
	t_list	*copy_data_words;
	char	**arr_2d;
	char	*str;

	str = ft_strtrim(s, " ");
	data_words = NULL;
	if (!(word_count(&str, &data_words)))
		return (0);
	copy_data_words = data_words;
	arr_2d = init_arr_2d(str, copy_data_words);
	ft_lstclear(&data_words, &del);
	free(str);
	return (arr_2d);
}

//TEST
//void print_2d_arr(char **arr)
//{
//	size_t i;
//	i = 0;
//	while (arr[i])
//	{
//		ft_putstr_fd(arr[i], 1);
//		ft_putstr_fd("|->|", 1);
//		i++;
//	}
//}

//int main(void){
//
//	char	**tmp;
//
//	char	*tests []= {"echo hello world     ",
//						"echo 'hello world'",
//						"echo  hel   lo world   ",
//						"echo \"hello world\"",
//						"echo 1\"2\"3\"4\"5\"6\"7",
//						"echo \"1\"2\"3\"4\"5\"6\"7\"",
//						"echo \"hello          world\"",
//						"echo \"first      word\" '   second  \"  \"   word' '|' | pwd",
//						"echo 123\"'1''2'\"3\"\"",
//						"echo 123             \"1  23\"",
//						"echo '123'\"456\"",
//						"echo '123''456'",
//						"echo 123\"456\"",
//						"echo '|'",
//						"echo |",
//						"      echo 'pam' ",
//						};
//	int	i;
//	i = 0;
//	while (i < 16)
//	{
//		ft_putendl_fd("\n", 1);
//		tmp = split(tests[i]);
//		ft_putnbr_fd(i, 1);
//		ft_putchar_fd(')', 1);
//		ft_putendl_fd(tests[i], 1);
//		print_2d_arr(tmp);
//		free_2d_arr(tmp);
//		i++;
//	}
//	return (0);
//}