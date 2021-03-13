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

/*
** Create a linked list 'head'
** Which has data to cut the 'str' by quotes and spaces
** Structure of the linked:
** start_index -> len -> start_index -> len -> ...
*/

static	void	word_count(char **str, t_list **head)
{
	int		i;
	int		len;
	char	sep;

	i = 0;
	len = 0;
	sep = 'f';
	ft_lstadd_back(head, ft_lstnew(i));
	while ((*str)[i])
	{
		len++;
		if (sep == 'f' && ((*str)[i] == '"' || (*str)[i] == '\''))
			sep = (*str)[i];
		else if (((*str)[i] == ' ' && sep == 'f') || (*str)[i + 1] == '\0' ||
			((*str)[i + 1] == ' ' && sep == 'f') || sep == (*str)[i])
		{
			ft_lstadd_back(head, ft_lstnew(len));
			len = 0;
			sep = 'f';
		}
		i = skip_spaces((*str), sep, i);
		if (len == 0)
			ft_lstadd_back(head, ft_lstnew(i));
	}
}

static	char	**init_arr_2d(char *str, t_list *copy_dw)
{
	int		i;
	int		len_arr;
	char	**arr_2d;

	len_arr = ft_lstsize(copy_dw) / 2;
	if (!(arr_2d = (char **)ft_calloc(len_arr + 1, sizeof(char *))))
		return (0);
	i = 0;
	while (i < len_arr)
	{
		arr_2d[i] = ft_substr(str, copy_dw->content, copy_dw->next->content);
		copy_dw = copy_dw->next->next;
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
	word_count(&str, &data_words);
	copy_data_words = data_words;
	arr_2d = init_arr_2d(str, copy_data_words);
	lstclear(&data_words);
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
//	tmp = split(tests[3]);
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