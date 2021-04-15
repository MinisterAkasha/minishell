/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:04:36 by tilda             #+#    #+#             */
/*   Updated: 2021/04/12 13:51:46 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function with &buff it is signals
*/

static void		exe_key(char **str_stat, t_history *history)
{
	char		*buff;
	int			buffer_size;

	buffer_size = 2048;
	buff = (char *)ft_calloc(buffer_size + 1, sizeof(char));
	if ((read(0, buff, buffer_size)) <= 0)
	{
		ft_putendl_fd("Couldn't read from terminal", 1);
		exit(1);
	}
	if (buff[0] == 4)
		ctrl_d(&buff, str_stat);
	else if (buff[0] == 3)
		ctrl_c(&buff, str_stat);
	else if (buff[0] == 28)
		ctrl_slash(&buff);
	if (!(ft_strcmp(buff, "\177")))
		delete_char(str_stat);
	else if (!(ft_strcmp(buff, "\e[A")))
		set_str_key_up(str_stat, history);
	else if (!(ft_strcmp(buff, "\e[B")))
		set_str_key_down(str_stat, history);
	else
		set_alpha(str_stat, buff, history);
	free(buff);
}

static int		find_nl(char **str_stat, char **line, t_history *history)
{
	char	*tmp;

	if ((tmp = ft_strchr(*str_stat, '\n')))
	{
		*line = ft_substr(*str_stat, 0, tmp - *str_stat);
		tmp = ft_strdup(tmp + 1);
		free(*str_stat);
		*str_stat = ft_strdup(tmp);
		free(tmp);
		create_new_history(history, *line);
		return (1);
	}
	return (0);
}

void			gnl(char **line, t_history *history)
{
	static char		*str_stat = NULL;
	struct termios	term_default;

	term_default = init_term_history(history);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		if (find_nl(&str_stat, line, history))
		{
			free(history->first_str);
			tcsetattr(0, TCSANOW, &term_default);
			break ;
		}
		exe_key(&str_stat, history);
	}
}
