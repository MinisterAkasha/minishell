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

static int		return_line(char **str_stat, char **line)
{
	char		*tmp;

	if ((tmp = ft_strchr(*str_stat, '\n')))
		return (find_nl(str_stat, line, tmp));
	return (2);
}

static int		read_or_ending(char **str_stat, char **line)
{
	char		*buff;
	char		*joined_str;
	int			buffer_size;
	ssize_t		bsize;

	buffer_size = 2048;
	if (!(buff = (char *)malloc(buffer_size + 1 * sizeof(char))))
		return (-1);
	if ((bsize = read(0, buff, buffer_size)) == -1)
		return (-1);
	buff[bsize] = 0;
	if (bsize == 0 && !(ft_strchr(*str_stat, '\n')))
	{
		if (!(*line = ft_strdup(*str_stat)))
			return (-1);
		free(buff);
		return (0);
	}
	if (!(ft_strcmp(buff, "\e[A")))
		get_next_hist_str();
	else if (!(ft_strcmp(buff, "\e[B")))
		get_previos_hist_str();
	if (!(ft_strcmp(buff, "\177")))
		delete_char(str_stat);
	else if (!ft_strcmp(buff, "\4"))
		return (0);
	else
		write(1, buff, bsize);
	joined_str = ft_strjoin(*str_stat, buff);//TODO Защити это дерьмо
	free(*str_stat);
	if (!(*str_stat = ft_strdup(joined_str)))
		return (-1);
	free(joined_str);
	free(buff);
	return (2);
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
		state = return_line(&str_stat, line);
		if (state != 2)
			break ;
		state = read_or_ending(&str_stat, line);
		if (state != 2)
		{
			free(str_stat);
			str_stat = 0;
			break;//return (state);
		}
	}
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	return (state);
}
