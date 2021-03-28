/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:32:06 by tilda             #+#    #+#             */
/*   Updated: 2021/03/21 20:32:07 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putchar(int c)
{
	 return (write(1, &c, 1));
}


void get_str_key_up(t_history *history, char **str_stat)
{
	if (history->cur > 0 && history->cur == history->total && !history->is_new_str)
	{
//		printf("1\n");
		free(*str_stat);
		(*str_stat) = protect_malloc(ft_strdup(history->arr[history->cur]));
//		printf("2\n");
		create_new_history(history, *str_stat);
		history->is_new_str = 1;
		history->cur--;
	}
	else if (history->cur > 0 && history->arr[history->cur - 1])
	{
//		printf("2\n");
		free(history->arr[history->cur]);
		history->arr[history->cur] = protect_malloc(ft_strdup(*str_stat));
		free(*str_stat);
//		printf("3\n");
		(*str_stat) = protect_malloc(ft_strdup(history->arr[history->cur - 1]));
		history->cur--;
	}
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	ft_putstr_fd(*str_stat, 1);
}

void get_str_key_down(t_history *history, char **str_stat)
{
	if (history->cur == history->total && !history->is_new_str)
	{
		create_new_history(history, *str_stat);
		history->is_new_str = 1;
	}
	else if (history->arr[history->cur] && history->arr[history->cur + 1])
	{
		free(history->arr[history->cur]);
		history->arr[history->cur] = protect_malloc(ft_strdup(*str_stat));
		free(*str_stat);
		(*str_stat) = protect_malloc(ft_strdup(history->arr[history->cur + 1]));
		history->cur++;
	}
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	ft_putstr_fd(*str_stat, 1);
}

int		delete_char(char **buff)
{
	int		len;

	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	len = ft_strlen((*buff));
	(*buff)[len - 1] = 0;
	return (1);
}