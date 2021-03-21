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
	tgetent(0, getenv("TERM"));
	write(1, save_cursor, strlen(save_cursor));

	return	(term);
}

static int		return_line(char **str_stat, char **line)
{
	char		*tmp;

	if ((tmp = ft_strchr(*str_stat, '\n')))
		return (find_nl(str_stat, line, tmp));
	else if (!(ft_strcmp(*str_stat, "\e[A")))
		get_next_hist_str();
	else if (!(ft_strcmp(*str_stat, "\e[A")))
		get_previos_hist_str();
	else if (!(ft_strcmp(*str_stat, "\177")))
		delete_char(str_stat);
	return (2);
}

static int		read_or_ending(int fd, char **str_stat, char **line)
{
	char		*buff;
	char		*joined_str;
	int			buffer_size;
	ssize_t		bsize;

	buffer_size = 1;
	if (!(buff = (char *)malloc(buffer_size + 1 * sizeof(char))))
		return (-1);
	if ((bsize = read(fd, buff, buffer_size)) == -1)
		return (-1);
	buff[bsize] = 0;
	if (bsize == 0 && !(ft_strchr(*str_stat, '\n')))
	{
		if (!(*line = ft_strdup(*str_stat)))
			return (-1);
		free(buff);
		return (0);
	}
	joined_str = ft_strjoin(*str_stat, buff);
	free(*str_stat);
	free(buff);
	if (!(*str_stat = ft_strdup(joined_str)))
		return (-1);
	free(joined_str);
	return (2);
}

int		gnl(int fd, char **line)
{
	static char		*str_stat = NULL;
	int				state;
	struct	termios	term;

	term = init_term();
	if (fd < 0 || !line)
		return (-1);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		state = return_line(&str_stat, line);
		if (state != 2)
			break ;//return (state); TODO Проверить на соответсвтие цикла с history.c
		state = read_or_ending(fd, &str_stat, line);
		if (state != 2)
		{
			free(str_stat);
			str_stat = 0;
			break;//return (state);
		}
	}
	term.c_lflag |= ~(ECHO);
	term.c_lflag |= ~(ICANON);
	return (state);
}
