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

static void		exe_key(char **str_stat, char *buff, t_history *history)
{
	char	*joined_str;

	if (!(ft_strcmp(buff, "\177")))
	{
		delete_char(str_stat);	//TODO если переместить коретку а потом удалить
		return ;				//TODO пофиксить удалеие значка минишела и т.д
	}
	if (!(ft_strcmp(buff, "\e[A")))
		get_str_key_up(history, str_stat);
	else if (!(ft_strcmp(buff, "\e[B")))
		get_str_key_down(history, str_stat);
	else
	{
		write(1, buff, ft_strlen(buff));
		joined_str = protect_malloc(ft_strjoin((*str_stat), buff));
		free((*str_stat));
		(*str_stat) = protect_malloc(ft_strdup(joined_str));
		free(joined_str);
		if (history->total == history->cur)
		{
			free(history->first_str);
			history->first_str = protect_malloc(ft_strdup((*str_stat)));
		}
	}
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
		free(*str_stat);
		str_stat = 0;
		return (0);
	}
	return (buff);
}

void	create_new_history(t_history *history, char *line)
{
	char	**copy_history_arr;
	int		arr_len;

	arr_len = get_arr_length(history->arr);
	copy_history_arr = copy_2d_arr(history->arr);
	free_2d_arr(history->arr);
	history->arr = add_param_to_2d_arr(copy_history_arr, line);
	history->total = arr_len;
	history->cur = history->total;
}

int		gnl(char **line, t_history *history)
{
	static char		*str_stat = NULL;
	char			*buff;
	struct	termios	term;
	int				exit;

	exit = 1;
	history->first_str = protect_malloc(ft_strdup(""));
	history->is_new_str = 0;
	term = init_term();
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	if (!line)
		return (-1);
	if (!str_stat)
		str_stat = ft_strdup("");
	while (1)
	{
		if (find_nl(&str_stat, line))
		{
			create_new_history(history, *line);
			exit = 1;
			break ;
		}
		buff = get_buff(&str_stat, line);
		if (!buff)
		{
			exit = 0;
			break ;//Ctrl-D
		}
		exe_key(&str_stat, buff, history);
		free(buff);
	}
	printf("%d - %d\n", history->cur, history->total);
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	return (exit);
}
