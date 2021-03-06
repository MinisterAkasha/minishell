#include "minishell.h"

/*
** Function with &buff it is signals
*/

static void		exe_key(char **str_stat, t_history *history)
{
	char		*buff;

	buff = get_buff();
	if (buff[0] == 4)
		ctrl_d(&buff, str_stat);
	else if (buff[0] == 3)
		ctrl_c(&buff, str_stat);
	else if (buff[0] == 28)
		ctrl_slash(&buff);
	else if (!ft_strcmp(buff, "\e[D") || !ft_strcmp(buff, "\e[C")
				|| !ft_strcmp(buff, "\t"))
	{
		free(buff);
		buff = ft_strdup("");
	}
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
