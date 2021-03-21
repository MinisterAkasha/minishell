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

int find_nl(char **str_stat, char **line, char *tmp)
{
	if (!(*line = ft_substr(*str_stat, 0, tmp - *str_stat)))
		return (-1);
	if (!(tmp = ft_strdup(tmp + 1)))
		return (-1);
	free(*str_stat);
	if (!(*str_stat = ft_strdup(tmp)))
		return (-1);
	free(tmp);
	return (1);
}

int		get_next_hist_str()
{
	write(1, restore_cursor, strlen(restore_cursor));
	write(1, delete_line, strlen(delete_line));
	write(1, "up", 2);
	return (1);
}

int		get_previos_hist_str()
{
	write(1, restore_cursor, strlen(restore_cursor));
	write(1, delete_line, strlen(delete_line));
	write(1, "down", 4);
	return (1);
}

int		delete_char(char **str_stat)
{
	int		len;

	write(1, cursor_left, strlen(cursor_left));
	write(1, delete_character, strlen(delete_character));
	len = ft_strlen(*str_stat);
	*str_stat[len] = 0;
	return (1);
}