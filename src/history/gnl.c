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

struct	termios		init_term()
{
	struct	termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, getenv("TERM"));//TODO брать у Илюхи с ENV
	tputs(save_cursor, 1, ft_putchar);

	return	(term);
}

static void		exe_key(char **str_stat, char *buff, char ***history)
{
	char	*joined_str;

	if (!(ft_strcmp(buff, "\e[A")))
		get_next_hist_str();
	else if (!(ft_strcmp(buff, "\e[B")))
		get_previos_hist_str();
	else if (!(ft_strcmp(buff, "\177")))
	{
		delete_char(str_stat);//TODO если переместить коретку а потом удалить
		return ;
	}
	else
		write(1, buff, ft_strlen(buff));
	joined_str = protect_malloc(ft_strjoin(*str_stat, buff));
	free(*str_stat);
	*str_stat = protect_malloc(ft_strdup(joined_str));
	free(joined_str);
}

static int		find_nl(char **str_stat, char **line)
{
	char	*tmp;

	if ((tmp = ft_strchr(*str_stat, '\n')))
	{
		*line = protect_malloc(ft_substr(*str_stat, 0, tmp - *str_stat));
		tmp = protect_malloc(ft_strdup(tmp + 1));
		free(*str_stat);
		*str_stat = protect_malloc(ft_strdup(tmp));
		free(tmp);
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
	if (!ft_strcmp(buff, "\4") || (bsize == 0 && !(ft_strchr(*str_stat, '\n'))))
	{
		protect_malloc(*line = ft_strdup(*str_stat));
		free(buff);
		free(str_stat);
		str_stat = 0;
		return (0);
	}
	return (buff);
}

int		gnl(char **line, char ***history)
{
	static char		*str_stat = NULL;
	char			*buff;
	struct	termios	term;

	history = 0;
	term = init_term();
	if (!line)
		return (-1);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		if (find_nl(&str_stat, line))
			break ;
		buff = get_buff(&str_stat, line);
		if (!buff)
			return (0);//Ctrl-D
		exe_key(&str_stat, buff, history);
		free(buff);
	}
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	return (1);
}
