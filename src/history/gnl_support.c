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


int		get_next_hist_str()
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);

	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	write(1, "up", 2);
	return (1);
}

int		get_previos_hist_str()
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	write(1, "down", 4);
	return (1);
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