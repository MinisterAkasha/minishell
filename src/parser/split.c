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

static t_list *word_count(char const *s, char **str)
{
	t_list	*head;
	t_list	*tmp;
	int		i;
	int		len;
	char	separator;
	int		start_index;
	int		space;
	char	*tmp_str;

	if (!(head = (t_list *)malloc(sizeof(t_list))))
		return (0);
	head = NULL;
	i = 0;
	len = 0;
	separator = 'f';
	start_index = -1;
	*str = ft_strtrim(s, " ");
	tmp_str = *str;
	while(tmp_str[i])
	{
		if(len == 0)
			start_index = i;
		if (tmp_str[i] == ' ' && space == 0 && separator == 'f')
			space = 1;
		if (start_index != -1)
		{
//			ft_putendl_fd("Add index:", 1);
//			ft_putchar_fd(tmp_str[i], 1);
//			ft_putchar_fd('\n', 1);
//			ft_putendl_fd("Add value index:", 1);
//			ft_putnbr_fd(start_index, 1);
//			ft_putchar_fd('\n', 1);
			ft_lstadd_back(&head, ft_lstnew(start_index));
			start_index = -1;
		}
		len++;
		if (separator == 'f' && (tmp_str[i] == '"' || tmp_str[i] == '\''))
			separator = tmp_str[i];
		else if (separator == tmp_str[i] || space == 1 || tmp_str[i + 1] == '\0' ||
				(tmp_str[i + 1] == ' ' && separator == 'f'))
		{
//			ft_putendl_fd("Add len:", 1);
//			ft_putnbr_fd(len, 1);
//			ft_putchar_fd('\n', 1);
			ft_lstadd_back(&head, ft_lstnew(len));
			len = 0;
			separator = 'f';
		}
		if (space != 0)
		{
			while(tmp_str[i] == ' ' && tmp_str[i])
				i++;
			space = 0;
		}
		else
			i++;
	}
	return head;
}

char	**split(char const *s)
{
	t_list	*data_words;
	t_list	*copy_data_words;
	char **splited_str;
	int		len_arr;
	char	*str;
	int		start;
	int		len_str;
	int		i;

	i = 0;
	data_words = word_count(s, &str);
	copy_data_words = data_words;
//	ft_putendl_fd(str, 1);
	len_arr = ft_lstsize(data_words) / 2;
//	ft_putnbr_fd((int)len_arr, 1);
	if (!(splited_str = (char **)ft_calloc( len_arr + 1, sizeof (char *))))
		return (0);
	while (i < len_arr)
	{
		start = copy_data_words->content;
		copy_data_words = copy_data_words->next;
		len_str = copy_data_words->content;
		copy_data_words = copy_data_words->next;
		splited_str[i] = ft_substr(str, start, len_str);
		i++;
	}
	return (splited_str);
}

void print_2d_arr(char **arr)
{
	size_t i;
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("|->|", 1);
		i++;
	}
}

int main(void){

	char	**tmp;
	char	*tests []= {"echo 'hello world'",
						"echo hello world     ",
						"echo  hel   lo world   ",
						"echo \"hello world\"",
						"echo 1\"2\"3\"4\"5\"6\"7",
						"echo \"1\"2\"3\"4\"5\"6\"7\"",
						"echo \"hello          world\"",
						"echo \"first      word\" '   second  \"  \"   word' '|' | pwd",
						"echo 123\"'1''2'\"3\"\"",
						"echo 123             \"1  23\"",
						"echo '123'\"456\"",
						"echo '123''456'",
						"echo 123\"456\"",
						"echo '|'",
						"echo |",
						"      echo 'pam' ",
						};
	int	i;
	i = 0;
	while (i < 16)
	{
		ft_putendl_fd("\n", 1);
		tmp = split(tests[i]);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(')', 1);
		ft_putendl_fd(tests[i], 1);
		print_2d_arr(tmp);
		free_2d_arr(tmp);
		i++;
	}

	return (0);
}