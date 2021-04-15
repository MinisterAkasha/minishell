/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:32:06 by tilda             #+#    #+#             */
/*   Updated: 2021/04/12 13:51:16 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void			create_new_history(t_history *history, char *line)
{
	char	**copy_history_arr;
	int		arr_len;

	if (ft_strcmp(line, ""))
	{
		arr_len = get_arr_length(history->arr);
		copy_history_arr = copy_2d_arr(history->arr);
		free_2d_arr(history->arr);
		history->arr = add_param_to_2d_arr(copy_history_arr, line);
		history->total = arr_len;
		history->cur = history->total;
		free_2d_arr(copy_history_arr);
	}
}

struct termios	init_term_history(t_history *history)
{
	struct termios	term;
	struct termios	term_def;
	char			*term_env;

	term_env = ft_strchr("TERM=xterm-256color", '=') + 1;
	if (!term_env)
	{
		ft_putendl_fd("Could't get a TERM", 1);
		exit(0);
	}
	history->first_str = ft_strdup("");
	history->is_new_str = 0;
	tcgetattr(0, &term);
	term_def = term;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_env);
	tputs(save_cursor, 1, ft_putchar);
	ft_putstr_fd("(╯✧▽✧)╯ -> ", 1);
	return (term_def);
}

void			clean_old_line(char *str_stat)
{
	size_t i;

	i = 0;
	while (i != ft_strlen(str_stat))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		i++;
	}
}
