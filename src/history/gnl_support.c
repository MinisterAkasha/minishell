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
	if (history->cur > 0 && history->arr[history->cur - 1])
	{
		free(history->arr[history->cur]);
		history->arr[history->cur] = protect_malloc(ft_strdup(*str_stat));
		free(*str_stat);
		(*str_stat) = protect_malloc(ft_strdup(history->arr[history->cur - 1]));
		history->cur--;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(delete_line, 1, ft_putchar);
		ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	}
//	write(1, "up", 2);
}

void get_str_key_down(t_history *history, char **str_stat)
{
	if (history->cur == history->total && !history->is_new_str)
	{
		history->is_new_str = 1;
		add_param_to_2d_arr(history->arr, *str_stat);
		history->total++;
		history->cur = history->total;
	}
	else if (history->arr[history->cur] && history->arr[history->cur + 1] && history->total > history->cur)
	{
		free(history->arr[history->cur]);
		history->arr[history->cur] = protect_malloc(ft_strdup(*str_stat));
		free(*str_stat);
		(*str_stat) = protect_malloc(ft_strdup(history->arr[history->cur + 1]));
		history->cur++;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(delete_line, 1, ft_putchar);
		ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	}
//	write(1, "down", 4);
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