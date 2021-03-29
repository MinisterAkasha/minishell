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

static void		exe_key(char **str_stat, char *buff, t_history *history)
{
	if (!(ft_strcmp(buff, "\177")))
		delete_char(str_stat);
	else if (!(ft_strcmp(buff, "\e[A")))
		set_str_key_up(str_stat, history);
	else if (!(ft_strcmp(buff, "\e[B")))
		set_str_key_down(str_stat, history);
	else
		set_alpha(str_stat, buff, history);
}

static int find_nl(char **str_stat, char **line, t_history *history)
{
	char	*tmp;

	if ((tmp = ft_strchr(*str_stat, '\n')))
	{
		*line = protect_malloc(ft_substr(*str_stat, 0, tmp - *str_stat));
		tmp = protect_malloc(ft_strdup(tmp + 1));
		free(*str_stat);
		*str_stat = protect_malloc(ft_strdup(tmp));
		free(tmp);
		create_new_history(history, *line);
		return (1);
	}
	return (0);
}

static char		*get_buff(char **str_stat, char **line)
{
	char		*buff;
	int			buffer_size;
	ssize_t		bsize;

	buffer_size = 2048;
	buff = protect_malloc((char *)malloc(buffer_size + 1 * sizeof(char)));
	if ((bsize = read(0, buff, buffer_size)) == -1)
		return (0);//TODO сделать ошибку не считанного файла
	buff[bsize] = 0;
	if (!ft_strcmp(buff, "\4"))
	{
		protect_malloc(*line = ft_strdup(*str_stat));
		free(buff);
		free(*str_stat);
		str_stat = 0;
		return (0);
	}
	return (buff);
}

int		gnl(char **line, t_history *history, char **env)
{
	static char		*str_stat = NULL;
	char			*buff;
	struct	termios	term;

	term = init_term_history(history, env);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		if (find_nl(&str_stat, line, history))
		{
			return (exit_gnl(history, term, 1));

		}
		buff = get_buff(&str_stat, line);
		if (!buff)
		{
			return (exit_gnl(history, term, 0));

		}
		exe_key(&str_stat, buff, history);
		free(buff);
	}
}
