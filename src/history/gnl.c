/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:04:36 by tilda             #+#    #+#             */
/*   Updated: 2021/03/21 20:04:37 by tilda            ###   ########.fr       */
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
	ssize_t		bsize;

	buffer_size = 2048;
	buff = (char *)ft_calloc(buffer_size + 1, sizeof(char));
	bsize = read(0, buff, buffer_size);
	if (bsize <= 0)
		return ;//TODO сделать ошибку не считанного файла
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

void			gnl(char **line, t_history *history, char **env)
{
	static char		*str_stat = NULL;
	struct termios	term_default;

	term_default = init_term_history(history, env);
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
