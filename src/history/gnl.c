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

static	void	exe_key(char **str_stat, char *buff, ssize_t bsize)
{
	char	*joined_str;

	if (!(ft_strcmp(buff, "\e[A")))
		get_next_hist_str();
	else if (!(ft_strcmp(buff, "\e[B")))
		get_previos_hist_str();
	else if (!(ft_strcmp(buff, "\177")))
	{
		delete_char(str_stat);
		return ;
	}
	else
		write(1, buff, bsize);
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

static int		read_or_ending(char **str_stat, char **line)
{
	char		*buff;
	int			buffer_size;
	ssize_t		bsize;

	buffer_size = 2048;
	buff = protect_malloc((char *)malloc(buffer_size + 1 * sizeof(char)));
	if ((bsize = read(0, buff, buffer_size)) == -1)
		return (-1);//TODO сделать ошибку не считанного файла
	buff[bsize] = 0;
	if (!ft_strcmp(buff, "\4") || (bsize == 0 && !(ft_strchr(*str_stat, '\n'))))
	{
		protect_malloc(*line = ft_strdup(*str_stat));
		free(buff);
		return (1);
	}
	exe_key(str_stat, buff, bsize);
	free(buff);
	return (0);
}

int gnl(char **line, char ***history)
{
	static char		*str_stat = NULL;
	int				state;
	struct	termios	term;

	history = 0;
	term = init_term();
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	if (!line)
		return (-1);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		state = find_nl(&str_stat, line);
		if (state)
			break ;
		state = read_or_ending(&str_stat, line);
		if (state)
		{
			free(str_stat);
			str_stat = 0;
			break ;
		}
	}
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	return (state);
}
